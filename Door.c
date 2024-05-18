#include "public.h"
#include "hero.h"

static PBase s_removeBase = 0;

typedef struct sDoor
{
    TBase base;
}TDoor, *PDoor;


static void Print(PBase self)
{
    PDoor door = (PDoor)self;
    switch (self->type)
    {
    case 3:
        printf("\033[33m\033[%d;%dH门\033[0m", (door->base.x + 1), (door->base.y + 1) * 2);
        break;
    case 4:
        printf("\033[34m\033[%d;%dH门\033[0m", (door->base.x + 1), (door->base.y + 1) * 2);
        break;
    case 5:
        printf("\033[31m\033[%d;%dH门\033[0m", (door->base.x + 1), (door->base.y + 1) * 2);
        break;
    default:
        break;
    }
}

static int Collion(PBase self, void* herov)
{
    PDoor door = (PDoor)self;
    PHero hero = (PHero)herov;
    if (door->base.x == hero->base.x && door->base.y == hero->base.y)
    {
        switch (self->type)
        {
        case 3:
            if (hero->yellow > 0)
            {
                hero->yellow--; //黄钥匙减少
                return 2;
            }
            break;
        case 4:
            if (hero->blue > 0)
            {
                hero->blue--;
                return 2;
            }
            break;
        case 5:
            if (hero->red > 0)
            {
                hero->red--;
                return 2;
            }
            break;
        default:
            break;
        }
        printf("\nneed key!\n");
        return 1;
    }
    return 0;
}

PBase CreateYellowDoor(int x, int y, int type)
{
    PDoor door = malloc(sizeof(TDoor));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    return (PBase)door;
}

PBase CreateBlueDoor(int x, int y, int type)
{
    PDoor door = malloc(sizeof(TDoor));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    return (PBase)door;
}

PBase CreateRedDoor(int x, int y, int type)
{
    PDoor door = malloc(sizeof(TDoor));
    door->base.x = x;
    door->base.y = y;
    door->base.type = type;
    door->base.scene = NULL;
    door->base.Print = Print;
    door->base.Collion = Collion;
    return (PBase)door;
}