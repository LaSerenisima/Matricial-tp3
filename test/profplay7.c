#include "stdbool.h"
#include "stm32f103xb.h"

bool fisico[7][14]={

{1, 1, 1, 1, 1, 1, 0},//0
{0, 1, 1, 0, 0, 0, 0},//1
{1, 1, 0, 1, 1, 0, 1},//2
{1, 1, 1, 1, 0, 0, 1},//3
{0, 1, 1, 0, 0, 1, 1},//4
{1, 0, 1, 1, 0, 1, 1},//5
{1, 0, 1, 1, 1, 1, 1},//6
{1, 1, 1, 0, 0, 0, 0},//7
{1, 1, 1, 1, 1, 1, 1},//8
{1, 1, 1, 1, 1, 0, 1},//9
{1, 1, 1, 0, 1, 1, 1},//A
{0, 0, 1, 1, 1, 1, 1},//B
{1, 0, 0, 1, 1, 1, 0},//C
{0, 1, 1, 1, 1, 0, 1},//D

};


void di7conf(int a, int b, int c, int d, int e, int f, int g){
int pines [7]={a,b,c,d,e,f,g};
RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
for (int i=0; i=7; i++){
    if(pines[i]<8){
GPIOB ->CRL &=~ (0Xf<<(pines[i]*4));
GPIOB ->CRL |= (0X1<<(pines[i]*4));
    }else{

        GPIOB -> CRH &=~(0Xf<<((pines[i]%8)*4));
        GPIOB -> CRH |= (0x1<<((pines[i]%8)*4));
    }
    
}
}

void di7L(int a, int b, int c, int d, int e, int f, int g, char l){
    
    int dis[7]={a,b,c,d,e,f,g};
    //traduccion
    int trans;
    if (l == "0") trans=0;
    if (l == "1") trans=1;
    if (l == "2") trans=2;
    if (l == "3") trans=3;
    if (l == "4") trans=4;
    if (l == "5") trans=5;
    if (l == "6") trans=6;
    if (l == "7") trans=7;
    if (l == "8") trans=8;
    if (l == "9") trans=9;
    if (l == "A" || (l == "a")) trans=10;
    if (l == "B" || (l == "b")) trans=11;
    if (l == "C" || (l == "c")) trans=12;
    if (l == "D" || (l == "d")) trans=13;
    
    for (int i=0; i<7; i++){
     if (fisico[l][i]) GPIOB -> BSRR|= (1<<dis[i]);
     else GPIOB -> BSRR |= (1<<(dis[i]+16));
    }
}
//aprende a castear