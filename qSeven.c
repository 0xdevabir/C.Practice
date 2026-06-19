#include<stdio.h>
int main(){


int a,b;
char ope;

scanf("%d %c %d", &a, &ope, &b);

if(ope == '+'){
    int sum=a+b;
    printf("%d",sum);
}
else if(ope == '-'){
    int minues =a-b;
    printf("%d",minues);
}
else if(ope == '/'){
    int devide =a/b;
    printf("%d",devide);
}
else if(ope == '*'){
    int multi =a*b;
    printf("%d",multi);
}
else{
    printf("operator error");
}





};