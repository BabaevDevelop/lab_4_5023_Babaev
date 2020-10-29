#include <stdio.h>
#include <malloc.h>

enum nodeColor {
    RED,
    BLACK
};

struct Node{
    int data, color;
    struct Node *next[2];
};

struct Node *root = NULL;

//Init Tree
struct Node *createNode(int data){
    struct Node *newnode;
    newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode -> data = data;
    newnode -> color = RED;
    newnode -> next[0] = newnode -> next[1] = NULL;
    return newnode;
}

//Insert
void Insert(int data){
    struct Node *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root){
        root = createNode(data);
        return;
    }
    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL){
        if (ptr -> data == data){
            printf("Can't Duplicate\n");
            return;
        }
        index = (data - ptr -> data) > 0 ? 1:0;
        stack[ht] = ptr;
        ptr = ptr -> next[index];
        dir[ht++] = index;
    }
    stack[ht - 1] -> next[index] = newnode = createNode(data);
    while((ht >= 3) && (stack[ht - 1] -> color == RED)){
        if (dir[ht - 2] == 0){
            yPtr = stack[ht - 2] -> next[1];
            if (yPtr != NULL && yPtr -> color == RED){
                stack[ht - 2] -> color = RED;
                stack[ht - 1] -> color = yPtr -> color = BLACK;
                ht -= 2;
            }else{
                if (dir[ht - 1] == 0){
                    yPtr = stack[ht -1];
                }else{
                    xPtr = stack[ht - 1];
                    yPtr = xPtr -> next[1];
                    xPtr -> next[1] = yPtr -> next[0];
                    yPtr -> next[0] = xPtr;
                    stack[ht - 2] -> next[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr -> color = RED;
                yPtr -> color = BLACK;
                xPtr -> next[0] = yPtr -> next[1];
                yPtr -> next[1] = xPtr;
                if (xPtr == root){
                    root = xPtr;
                }else{
                    stack[ht - 3] -> next[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }else{
            yPtr = stack[ht - 2] -> next[0];
            if ((yPtr != NULL) && (yPtr -> color == RED)){
                stack[ht - 2] -> color = RED;
                stack[ht - 1] -> color =  yPtr -> color = BLACK;
                ht = ht - 2;
            }else{
                if (dir[ht - 1] == 1){
                    yPtr = stack[ht - 1];
                }else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr -> next[0];
                    xPtr -> next[0] = yPtr -> next[1];
                    yPtr -> next[1] = xPtr;
                    stack[ht - 2] -> next[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr -> color = BLACK;
                xPtr -> color = RED;
                xPtr -> next[1] = yPtr -> next[0];
                yPtr -> next[0] = xPtr;
                if (xPtr == root){
                    root = yPtr;
                }else{
                    stack[ht - 3] -> next[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root -> color = BLACK;
}

// Delete
void deletion(int data) {
    struct Node *stack[98], *ptr, *xPtr, *yPtr;
    struct Node *pPtr, *qPtr, *rPtr;
    int dir[98], ht = 0, diff, i;
    enum nodeColor color;

    if (!root) {
        printf("Tree not available\n");
        return;
    }

    ptr = root;
    while (ptr != NULL) {
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->next[diff];
    }

    if (ptr->next[1] == NULL) {
        if ((ptr == root) && (ptr->next[0] == NULL)) {
            free(ptr);
            root = NULL;
        } else if (ptr == root) {
            root = ptr->next[0];
            free(ptr);
        } else {
            stack[ht - 1]->next[dir[ht - 1]] = ptr->next[0];
        }
    } else {
        xPtr = ptr->next[1];
        if (xPtr->next[0] == NULL) {
            xPtr->next[0] = ptr->next[0];
            color = xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = color;

            if (ptr == root) {
                root = xPtr;
            } else {
                stack[ht - 1]->next[dir[ht - 1]] = xPtr;
            }

            dir[ht] = 1;
            stack[ht++] = xPtr;
        } else {
            i = ht++;
            while (1) {
                dir[ht] = 0;
                stack[ht++] = xPtr;
                yPtr = xPtr->next[0];
                if (!yPtr->next[0])
                    break;
                xPtr = yPtr;
            }

            dir[i] = 1;
            stack[i] = yPtr;
            if (i > 0)
                stack[i - 1]->next[dir[i - 1]] = yPtr;

            yPtr->next[0] = ptr->next[0];

            xPtr->next[0] = yPtr->next[1];
            yPtr->next[1] = ptr->next[1];

            if (ptr == root) {
                root = yPtr;
            }

            color = yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = color;
        }
    }

    if (ht < 1)
        return;

    if (ptr->color == BLACK) {
        while (1) {
            pPtr = stack[ht - 1]->next[dir[ht - 1]];
            if (pPtr && pPtr->color == RED) {
                pPtr->color = BLACK;
                break;
            }

            if (ht < 2)
                break;

            if (dir[ht - 2] == 0) {
                rPtr = stack[ht - 1]->next[1];

                if (!rPtr)
                    break;

                if (rPtr->color == RED) {
                    stack[ht - 1]->color = RED;
                    rPtr->color = BLACK;
                    stack[ht - 1]->next[1] = rPtr->next[0];
                    rPtr->next[0] = stack[ht - 1];

                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->next[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 0;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->next[1];
                }

                if ((!rPtr->next[0] || rPtr->next[0]->color == BLACK) &&
                    (!rPtr->next[1] || rPtr->next[1]->color == BLACK)) {
                    rPtr->color = RED;
                } else {
                    if (!rPtr->next[1] || rPtr->next[1]->color == BLACK) {
                        qPtr = rPtr->next[0];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->next[0] = qPtr->next[1];
                        qPtr->next[1] = rPtr;
                        rPtr = stack[ht - 1]->next[1] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    rPtr->next[1]->color = BLACK;
                    stack[ht - 1]->next[1] = rPtr->next[0];
                    rPtr->next[0] = stack[ht - 1];
                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->next[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            } else {
                rPtr = stack[ht - 1]->next[0];
                if (!rPtr)
                    break;

                if (rPtr->color == RED) {
                    stack[ht - 1]->color = RED;
                    rPtr->color = BLACK;
                    stack[ht - 1]->next[0] = rPtr->next[1];
                    rPtr->next[1] = stack[ht - 1];

                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->next[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 1;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->next[0];
                }
                if ((!rPtr->next[0] || rPtr->next[0]->color == BLACK) &&
                    (!rPtr->next[1] || rPtr->next[1]->color == BLACK)) {
                    rPtr->color = RED;
                } else {
                    if (!rPtr->next[0] || rPtr->next[0]->color == BLACK) {
                        qPtr = rPtr->next[1];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->next[1] = qPtr->next[0];
                        qPtr->next[0] = rPtr;
                        rPtr = stack[ht - 1]->next[0] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    rPtr->next[0]->color = BLACK;
                    stack[ht - 1]->next[0] = rPtr->next[1];
                    rPtr->next[1] = stack[ht - 1];
                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->next[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}


void inorderTraversal(struct Node *node) {
    if (node) {
        inorderTraversal(node->next[0]);
        printf("%d  ", node->data);
        inorderTraversal(node->next[1]);
    }
    return;
}

// Driver code
int main() {
    int ch, data;
    while (1) {
        printf("1. Insertion\t2. Deletion\n");
        printf("3. Traverse\t4. Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the element to insert:");
                scanf("%d", &data);
                Insert(data);
                break;
            case 2:
                printf("Enter the element to delete:");
                scanf("%d", &data);
                deletion(data);
                break;
            case 3:
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                return 0;
            default:
                printf("Not available\n");
                break;
        }
        printf("\n");
    }
    return 0;
}
