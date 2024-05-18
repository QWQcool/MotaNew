#include "public.h"
#include "hero.h"
#include <conio.h>

typedef struct sShop
{
    TBase base;
}TShop, * PShop;

int ShopBuy(void* herov)
{
    static int s_buyPos = 0;
    int IndexItem = 6;
    int isExit = 0;  //0����ѭ����1�˳�ѭ��
    int isBuy = 0;
    char* shopItem[1024] =
    {
        "1���:10Ѫ",
        "1���:5��",
        "1���:5��",
        "5���:��Կ��",
        "5���:��Կ��",
        "5���:��Կ��"
    };
    PHero hero = (PHero)herov;
    printf("\033[2J\033[1;1H");
    for (int i = 0; i < IndexItem; i++)
    {
        if(i == s_buyPos)printf("\033[91m%s\n\n\033[0m", shopItem[i]);
        else printf("%s\n\n", shopItem[i]);
    }
    printf("Q�˳� B���� WS��ѡ��Ʒ\n");
    switch (_getch())
    {
    case 'W':
    case'w':
        s_buyPos--;
        if (s_buyPos < 0)
        {
            s_buyPos = IndexItem - 1;
        }
        break;
    case'S':
    case's':
        s_buyPos++;
        if (s_buyPos >= IndexItem)
        {
            s_buyPos = 0;
        }
        break;
    case'Q':
    case'q':
        isExit = 1;
        break;
    case'B':
    case'b':
        isBuy = 1;
        break;
    default:
        break;
    }
    return isExit;
}

static void Print(PBase self)
{
    PShop shop = (PShop)self;
    printf("\033[91m\033[%d;%dH��\033[0m", (shop->base.x + 1), (shop->base.y + 1) * 2);

}

static int Collion(PBase self, void* herov)
{
    PShop shop = (PShop)self;
    PHero hero = (PHero)herov;
    if (shop->base.x == hero->base.x && shop->base.y == hero->base.y)
    {
        while (1)
        {
            if (ShopBuy(herov))break;
        }
        return 1;
    }
    return 0;
}

PBase CreateShop(int x, int y, int type)
{
    PShop shop = malloc(sizeof(TShop));
    shop->base.x = x;
    shop->base.y = y;
    shop->base.type = type;
    shop->base.scene = NULL;
    shop->base.Print = Print;
    shop->base.Collion = Collion;
    return (PBase)shop;
}