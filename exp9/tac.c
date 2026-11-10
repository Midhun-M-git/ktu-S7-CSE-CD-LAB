#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * readline(){
    size_t size = 128,len = 0;
    char *line = malloc(size);
    if(line == NULL){
        return NULL;
    }
    int ch =0;

    while((ch = getchar())!= EOF && ch != '\0'){

if(len+1 >= size){
    size*=2;
    char *temp = realloc(line,size);;
    if (temp == NULL){
        return NULL;
    }
    line = temp;
}

        line[len++] = ch;
    }
    line[len] = '\0';
    if(ch == EOF && len ==0){
        free(line);
        return NULL;

    }
    return line;
}

int main(){
char *line;
char *lines[100];
int count =0;
char lhs[100],a[50],op,b[50];

while((line = readline())!= NULL){
    if(strcmp(line,"END")==0){
        free(line);
        break;
    }
    if(count < 99){
  lines[count++]= line;
    }
}

for(int i =0;i<count;i++){
    line = lines[i];
    if(sscanf(line,"%[^=]=%[^+/-*]%c %s",lhs,a,&op,b)==4){
        printf("MOv AX,%s",a);
    }
}


    return 0;
}