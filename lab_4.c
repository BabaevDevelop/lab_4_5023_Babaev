#include<stdio.h>
 
int StrCmp(const char* a, const char* b){
    for(; *a&&*b; ++a, ++b){
        if(*a-*b) return *a-*b;
    }
    return *a-*b;
}
 
int main(){
    char* array[100]={NULL}, *tmp=NULL, text[500]={'\0'};
    int i, j, size;
    fgets(text, 255, stdin);
    for(i=0; i<sizeof(text); ++i){
        if(text[i]==' ')text[i]='\0';
    }
    for(i=0, size=0; i<sizeof(text); ++i){
        if(text[i]!='\0'){
            array[size++]=&text[i];
            while(text[i]!='\0')++i;
        }
    }
    for(i=0; i<size; i++){
        tmp=array[i];
        for(j=i-1; j>=0&&StrCmp(tmp, array[j])<0; --j){
            array[j+1]=array[j];
        }
        array[j+1]=tmp;
    }
    for(i=0; i<size; ++i){
        puts(array[i]);
    }
    return 0;
}