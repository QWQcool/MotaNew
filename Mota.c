
#include <stdio.h>
#include "public.h"
#include "Map.h"

PScene* g_scene;

int main()
{
    RegCreateMasterAll();
    g_scene = (PScene*)malloc(sizeof(PScene) * M_index);
    for (int i = g_mapIndex; i < M_index; i++)
    {
        g_scene[i] = CreateScene(Maps[i], mapX, mapY);
    } 
    while (1)
    {
        PrintScene(g_scene[g_mapIndex]);
        UpdateScene(g_scene[g_mapIndex]);
    }
    free(g_scene);
    return 0;
}