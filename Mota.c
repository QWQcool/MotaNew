#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "public.h"
#include "Map.h"
int Show_Widget();

int g_ShareMemory = M_index;
PScene* g_scene;
extern int g_isLoad;

int Game_Init()
{
        Map_Init();
        RegCreateMasterAll();
        g_scene = (PScene*)malloc(sizeof(PScene) * g_ShareMemory);
        for (int i = g_mapIndex; i < g_ShareMemory; i++)
        {
            g_scene[i] = CreateScene(Maps[i], mapX, mapY);
        }
}

int Load_Init(int saveIndex)
{

}

int main()
{
    while (1)
    {
        if (Show_Widget())break;
    };
    while (1)
    {
        PrintScene(g_scene[g_mapIndex]);
        UpdateScene(g_scene[g_mapIndex]);
    }
    free(g_scene);
    return 0;
}