#include "hero.h"
#include <assert.h>

static PHero s_hero = NULL;
static void Print(PBase self)
{
    PHero hero = (PHero)self;
    printf("\033[%d;%dHÈË", (hero->base.x + 1), (hero->base.y + 1) * 2);
}


PBase CreateHero(int x, int y, int type)
{
    if(s_hero!=NULL)
    {
        assert(s_hero!=NULL);
        //return (PBase)s_hero;
        return NULL;
    }


    PHero hero = malloc(sizeof(THero));
    hero->base.x = x;
    hero->base.y = y;
    hero->base.type = type;
    hero->base.scene = NULL;
    hero->base.Print = Print;
    //1lv 800hp 10atk 10def 0gold 0exp 1yellow 1blue 1red
    hero->level = 1;
    hero->hp = 800;
    hero->atk = 10;
    hero->def = 10;
    hero->gold = 0;
    hero->exp = 0;
    hero->yellow = 1;
    hero->blue = 1;
    hero->red = 1;
    s_hero = hero;
    return (PBase)hero;
}


PHero GetHero()
{
    return s_hero;
}