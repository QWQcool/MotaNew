#include "public.h"
#include "hero.h"

typedef struct sWall
{
    TBase base;
}TWall,*PWall;


static void Print(PBase self)
{
    //ǽ 墙
    PWall wall = (PWall)self;
    //printf("\033[47;37m\033[%d;%dH ǽ\033[0m", (wall->base.x+1), (wall->base.y+1) * 2); //占两个位的版本
    printf("\033[47;37m\033[%d;%dHǽ\033[0m", (wall->base.x + 1), (wall->base.y + 1) * 2); //占一个位 测试
}

static int Collion(PBase self,void* herov)
{
    PWall wall = (PWall)self;
    PHero hero = (PHero)herov;
    if (wall->base.x == hero->base.x && wall->base.y == hero->base.y)
    {
        return 1;
    }
    return 0;
}

PBase CreateWall(int x, int y, int type)
{
    PWall wall = malloc(sizeof(TWall));
    wall->base.x = x;
    wall->base.y = y;
    wall->base.type = type;
    wall->base.scene = NULL;
    wall->base.Print = Print;
    wall->base.Collion = Collion;
    return (PBase)wall;
}