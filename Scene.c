#define _CRT_SECURE_NO_WARNINGS
#include "public.h"
#include "hero.h"
#include <conio.h>

//PScene s_scene[1024] = { 0 };
extern int g_ShareMemory;  //给g_scene分配了几个scene
static PBase s_removeBase = 0;
static int s_chanageScene = 0;

void RemoveSceneItem(PBase base);

int LoadGame();

int SaveAllScene()
{
    for (int i = 0; i<g_ShareMemory; ++i)
    {
        //PScene scene = g_scene[i];
        char scenebuf[1024];
        sprintf(scenebuf, ".\\scenes\\%d.scene.txt", i);
        FILE* pFile = fopen(scenebuf, "w");
        fprintf(pFile, "%d %d\n", i, g_scene[i]->index);
        for (int j = 0; j < g_scene[i]->index; j++)
        {
            PBase base = g_scene[i]->bases[j];
            char buf[1024] = { 0 };
            int size = base->Save(base, buf, sizeof(buf));
            fprintf(pFile, "%s\n", buf);
        }
        fclose(pFile);
    }
    printf("\033[15;1H SceneStyle存档成功!");
    Sleep(1000);

    return 1;
}


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
    case 'k':
        SaveAllScene();
        return;
    case 'l':
        Load_Init();
        break;
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
    //可以包装成函数在MoveFloor里调用优化，而不是放在Scene里判断
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
        int dirS[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
        if (downPos != NULL)  //上楼梯，找下一层下楼的位置，把英雄放过去
        {
            for (int i = 0; i < 4; i++)
            {
                int xx = dirS[i][0] + downPos->x;
                int yy = dirS[i][1] + downPos->y;
                int bFind = 1;
                for (int j = 0; j < g_scene[nowIndex]->index; j++)
                {
                    if (g_scene[nowIndex]->bases[j]->x == xx && g_scene[nowIndex]->bases[j]->y == yy)
                    {
                        bFind = 0;
                        break;
                    }
                }
                if (bFind)
                {
                    hero->base.x = xx;
                    hero->base.y = yy;
                    break;
                }
            }
        }
        if (upPos!= NULL)
        {
            for (int i = 0; i < 4; i++)
            {
                int xx = dirS[i][0] + upPos->x;
                int yy = dirS[i][1] + upPos->y;
                int bFind = 1;
                for (int j = 0; j < g_scene[nowIndex]->index; j++)
                {
                    if (g_scene[nowIndex]->bases[j]->x == xx && g_scene[nowIndex]->bases[j]->y == yy)
                    {
                        bFind = 0;
                        break;
                    }
                }
                if (bFind)
                {
                    hero->base.x = xx;
                    hero->base.y = yy;
                    break;
                }
            }
        }
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
    ShowHero();
    //隐藏光标
    printf("\033[?25l");
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
    s_removeBase->release(s_removeBase);
}
//

int LoadGame()
{
    for (int i = 0; i < g_scene[g_mapIndex]->index; i++)
    {
        if (g_scene[g_mapIndex]->bases[i] == GetHero())
        {
            g_scene[g_mapIndex]->bases[i] = g_scene[g_mapIndex]->bases[g_scene[g_mapIndex]->index - 1];
            g_scene[g_mapIndex]->index--;
            break;
        }
    }
    for (int i = 0; i < g_ShareMemory; i++)
    {
        free(g_scene[i]);
    }
    free(g_scene);
    free(GetHero());
    //重新加载当前场景
    //Load_Init(0);
    LoadSceneFile(g_scene);
}

//老的存档方式
//int SaveScene()
//{
//    const char* SceneFilePath[1024];
//    sprintf(SceneFilePath, ".\\save\\SaveScene.txt");
//    FILE* file = fopen(SceneFilePath, "w");
//    if (file == NULL) {
//        printf("Failed to open file %s\n", SceneFilePath);
//        return 0;
//    }
//    int SceneSize = g_ShareMemory;
//    fprintf(file, "%d\n", g_mapIndex);
//    for (int i = 0; i < SceneSize; i++)
//    {
//        fprintf(file, "%d\n", g_scene[i]->index);
//        for (int j = 0; j < g_scene[i]->index; j++)
//        {
//            //写入g_scene里base的x,y,type每写入一个换一次行
//            fprintf(file, "%d %d %d\n", g_scene[i]->bases[j]->x, g_scene[i]->bases[j]->y, g_scene[i]->bases[j]->type);
//        }
//    }
//    fclose(file);
//    return 1;
//}
