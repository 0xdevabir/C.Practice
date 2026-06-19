#include<stdio.h>
int main(){

//     int a, b, sum, minus, multiplication, divide,reminder;
//     printf("Give me two int value");
//     scanf("%d %d",&a,&b);
//     sum=a+b;
//     minus=a-b;
//     multiplication=a*b;
//     divide=a/b;
//     reminder=a%b;

//     printf("summation of a and b = %d \n", sum);
//     printf("minus of a and b = %d \n", minus);
//     printf("multiplication of a and b=%d \n",multiplication);
//   printf("divide of a and b=%d \n",divide);
//   printf("reminder of a and b=%d",reminder);

int eng;

scanf("%d",&eng);

if(eng<100){

    if(eng>=80)
    {printf("you got A+");}
    else if(eng>=60)
        {printf("You get B");}
    else if(eng>=40)
        {printf("You pass");}
    else{printf("Tumi fail");}
    }
else{printf("Tui osikhito thik number de");}

};