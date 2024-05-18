#include "public.h"
#include "hero.h"
#include <conio.h>

//PScene s_scene[1024] = { 0 };
extern PScene* g_scene;
extern int g_mapIndex;
static PBase s_removeBase = 0;
static int s_chanageScene = 0;
void RemoveSceneItem(PBase base);
void ChanageHeroScene(int index);
void UpdateScene(PScene scene)
{
    char c = _getch();
    PHero hero = GetHero();

    int dirX, dirY;
    dirX = dirY = 0;
    switch (c)
    {
    case 'w':dirX = -1; break;
    case 's':dirX = 1; break;
    case 'a':dirY = -1; break;
    case 'd':dirY = 1; break;
    default:
        break;
    }

    int oldX = hero->base.x;
    int oldY = hero->base.y;

    // 预测移动
    hero->base.x += dirX;
    hero->base.y += dirY;
    int bCollion = 0;
    // 判断是否碰撞
    for (int i = 0; i < scene->index; i++)
    {
        PBase base = scene->bases[i];
        if(base == hero)continue;

        int isCo1lion = base->Collion(base, hero);
        if(isCo1lion == 1)
        {
            bCollion = 1;
            break;
        }
        if (isCo1lion == 2)
        {
            s_removeBase = base;
            break;
        }
        if (g_mapIndex!=scene->indexScene)
        {
            s_chanageScene = 1;
            break;
        }
    }
    //TOOD

    if(bCollion)
    {
        hero->base.x = oldX;
        hero->base.y = oldY;
    }

    if (s_removeBase)
    {
        //RemoveSceneItem(s_removeBase);
        for (int i = 0; i < scene->index; i++)
        {
            if (scene->bases[i] == s_removeBase)
            {
                scene->bases[i] = scene->bases[scene->index - 1];
                scene->index--;
                break;
            }
        }
        s_removeBase = NULL;
    }

    if (s_chanageScene)
    {
        int nowIndex = g_mapIndex;
        s_chanageScene = 0;
        hero->base.scene = g_scene[nowIndex];
        PScene nowScene = scene;
        // TODO　把Hero从当前场景移除
        for (int i = 0; i < scene->index; i++)
        {
            if (scene->bases[i] == hero)
            {
                scene->bases[i] = scene->bases[scene->index - 1];
                scene->index--;
                break;
            }
        }
        // TODO　把Hero添加到新场景
        g_scene[nowIndex]->bases[g_scene[nowIndex]->index++] = hero;
        //上下楼梯定位
        PBase downPos = NULL;
        PBase upPos = NULL;

        // 找到上下楼梯口的位置
        
        for (int i = 0; i < g_scene[nowIndex]->index; i++)
        {
            if (nowIndex< scene->indexScene && g_scene[nowIndex]->bases[i]->type ==18)
            {
                upPos = g_scene[nowIndex]->bases[i];
                break;
            }
            if (nowIndex > scene->indexScene && g_scene[nowIndex]->bases[i]->type == 19)
            {
                downPos = g_scene[nowIndex]->bases[i];
                break;
            }
        }
        //　检查楼梯口附近的空位置
        int xPos = 0;
        int yPos = 0;
        int typePos = 0;
        if (downPos)  //上楼梯，找下一层下楼的位置，把英雄放过去
        {
            //for (int i = 0; i < g_scene[nowIndex]->index; i++)
            //{
            //    xPos = g_scene[nowIndex]->bases[i]->x;
            //    yPos = g_scene[nowIndex]->bases[i]->y;
            //    typePos = g_scene[nowIndex]->bases[i]->type;
            //    if
            //        (
            //            typePos != 1 &&
            //            (xPos - 1 == downPos->x && yPos == downPos->y) ||
            //            (xPos + 1 == downPos->x && yPos == downPos->y) ||
            //            (yPos + 1 == downPos->y && xPos == downPos->x) ||
            //            (yPos - 1 == downPos->y && xPos == downPos->x)
            //         )
            //        {
            //        break;
            //        }
            //}
        }
        if (upPos)
        {
            //for (int i = 0; i < g_scene[nowIndex]->index; i++)
            //{
            //    xPos = g_scene[nowIndex]->bases[i]->x;
            //    yPos = g_scene[nowIndex]->bases[i]->y;
            //    typePos = g_scene[nowIndex]->bases[i]->type;
            //    if
            //        (
            //            typePos != 1 &&
            //            (xPos - 1 == upPos->x && yPos == upPos->y) ||
            //            (xPos + 1 == upPos->x && yPos == upPos->y) ||
            //            (yPos + 1 == upPos->y && xPos == upPos->x) ||
            //            (yPos - 1 == upPos->y && xPos == upPos->x)
            //            )
            //        {
            //        break;
            //        }
            //}
        }
        //hero->base.x = xPos;
        //hero->base.y = yPos;
        downPos = NULL;
        upPos = NULL;
        xPos = 0;
        yPos = 0;
    }

}


void PrintScene(PScene scene)
{
    printf("\033[2J");
    for (int i = 0; i < scene->index; i++)
    {
        PBase base = scene->bases[i];
        base->Print(base);
    }
}

void RemoveSceneItem(PBase base)
{
    s_removeBase = base;
    for (int i = 0; i < g_scene[g_mapIndex]->index; i++)
    {
        if (g_scene[g_mapIndex]->bases[i] == s_removeBase)
        {
            g_scene[g_mapIndex]->bases[i] = g_scene[g_mapIndex]->bases[g_scene[g_mapIndex]->index - 1];
            g_scene[g_mapIndex]->index--;
            break;
        }
    }
}
//
void ChanageHeroScene(int index)
{
    s_chanageScene = index;
}
