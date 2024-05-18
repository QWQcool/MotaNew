#include "public.h"
#include "hero.h"

typedef struct sShop
{
    TBase base;
}TShop, * PShop;


static void Print(PBase self)
{
    PShop key = (PShop)self;
    printf("\033[33m\033[%d;%dHµê\033[0m", (key->base.x + 1), (key->base.y + 1) * 2);

}

static int Collion(PBase self, void* herov)
{
    PShop key = (PShop)self;
    PHero hero = (PHero)herov;
    if (key->base.x == hero->base.x && key->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 13:
            hero->yellow++; //»ÆÔ¿³×Ôö¼Ó
            break;
        case 14:
            hero->blue++;
            break;
        case 15:
            hero->red++;
            break;
        default:
            printf("BUG£¡\n");
            return 1;
            break;
        }
    }
    return 0;
}

PBase CreateYellowKey(int x, int y, int type)
{
    PShop door = malloc(sizeof(TShop));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    return (PBase)door;
}

PBase CreateBlueKey(int x, int y, int type)
{
    PShop door = malloc(sizeof(TShop));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    return (PBase)door;
}

PBase CreateRedKey(int x, int y, int type)
{
    PShop door = malloc(sizeof(TShop));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    return (PBase)door;
}