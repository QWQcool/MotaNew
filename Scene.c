#define _CRT_SECURE_NO_WARNINGS
#include "public.h"
#include "hero.h"
#include <conio.h>

//PScene s_scene[1024] = { 0 };
static PBase s_removeBase = 0;
static int S_HeroMoveFloorX = -1;
static int S_HeroMoveFloorY = -1;

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
        return;
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
    }
    //TOOD

    if(bCollion)
    {
        hero->base.x = oldX;
        hero->base.y = oldY;
    }

    if (S_HeroMoveFloorX != -1 && S_HeroMoveFloorY != -1)
    {
        hero->base.x = S_HeroMoveFloorX;
        hero->base.y = S_HeroMoveFloorY;
        S_HeroMoveFloorX = -1;
        S_HeroMoveFloorY = -1;
    }
}

int SaveAllScene()
{
    for (int i = 0; i < g_ShareMemory; ++i)
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

void SetHeroMoveFloorXY(int x, int y)
{
    S_HeroMoveFloorX = x;
    S_HeroMoveFloorY = y;
}

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
