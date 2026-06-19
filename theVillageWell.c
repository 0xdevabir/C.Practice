// #include<stdio.h>
// int main(){


//     int days, totalWater=500;

//     scanf("%d", &days);

//     int waterConsume = days*20;

//     totalWater = totalWater-waterConsume;

//     if(waterConsume>400){
//         printf("WATER SHORTAGE\n");
//     }
//     else{
//         printf("%dL remain\n", totalWater);
//     }


//     return 0;
// }

#include<stdio.h>
int main(){
int days,totalWater=500;
scanf("%d",&days);
int waterConsume = days*20;
totalWater =totalWater-waterConsume;
if(waterConsume>400){
    printf("Water storeage\n");
}
else{
printf("%d\n",totalWater);
}


return 0;



};