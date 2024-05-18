#include "public.h"
#include "hero.h"

extern int g_mapIndex;
extern PScene* g_scene;

typedef struct sFloor
{
    TBase base;
}TFloor, * PFloor;


static void Print(PBase self)
{
    PFloor floor = (PFloor)self;
    switch (self->type)
    {
    case 18:
        printf("\033[33m\033[%d;%dH��\033[0m", (floor->base.x + 1), (floor->base.y + 1) * 2);
        break;
    case 19:
        printf("\033[34m\033[%d;%dH��\033[0m", (floor->base.x + 1), (floor->base.y + 1) * 2);
        break;
    default:
        break;
    }
}

static int Collion(PBase self, void* herov)
{
    PFloor floor = (PFloor)self;
    PHero hero = (PHero)herov;
    if (floor->base.x == hero->base.x && floor->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 18:
            //��¥
            g_mapIndex++;
            break;
        case 19:
            //��¥
            g_mapIndex--;
            break;
        default:
            break;
            printf("\nMove Failed!\n");
            return 1;
        }
    }
    return 0;
}

PBase CreateUpStairFloor(int x, int y, int type)
{
    PFloor floor = malloc(sizeof(TFloor));
    floor->base.x = x;
    floor->base.y = y;
    floor->base.type = type;
    floor->base.scene = NULL;
    floor->base.Print = Print;
    floor->base.Collion = Collion;
    return (PBase)floor;
}

PBase CreateDownStairFloor(int x, int y, int type)
{
    PFloor floor = malloc(sizeof(TFloor));
    floor->base.x = x;
    floor->base.y = y;
    floor->base.type = type;
    floor->base.scene = NULL;
    floor->base.Print = Print;
    floor->base.Collion = Collion;
    return (PBase)floor;
}