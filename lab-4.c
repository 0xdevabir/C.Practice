#include<stdio.h>
int main(){
  int T, tamim[999], a, b;

  scanf("%d", &T);

  for(int i=0;i<T;i++){
    scanf("%d", &tamim[i]);
  }

  for(int i=0;i<T;i++){


    int bAge = tamim[i]-10;

    
    printf("%d\n", bAge);
  }

    return 0;
}