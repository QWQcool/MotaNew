#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#define _CRT_SECURE_NO_WARNINGS
// 包含必要的标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

typedef struct sBase TBase;

typedef struct sBase(*PBase);

typedef int (*FPrint)(PBase  self); 

typedef int (*FCollion)(PBase  self, void* hero);
typedef void (*FRelease)(void* that);
typedef int (*FSave)(PBase  self, const char* buf, int size);

typedef struct sBase
{
    int x;
    int y;
    int type;
    struct sScene* scene;
    FPrint Print;
    FCollion Collion;
    FRelease release;
    FSave  Save;
};

typedef PBase(*FCreateMaster)(int x, int y, int type, const char* buf);

void RegCreateMaster(int index, FCreateMaster cb);

void RegCreateMasterAll();

// 定义一个指向sScene结构体的指针类型TScene和一个函数指针类型PScene
typedef struct sScene
{
    PBase bases[1024];
    int index;
    int indexScene;
}TScene, (*PScene);

int g_ShareMemory;  //给g_scene分配了几个scene
int g_mapIndex;
PScene* g_scene;

void fillArrayFromFile(const char* filename, int index);
int Map_Init();

PScene CreateScene(int* maps, int w, int h);

void PrintScene(PScene scene);

void UpdateScene(PScene scene);

//GameWidget
int Game_Init();
int Load_Init();

//old save
//int LoadScene();
//int SaveScene()

//new save
int SaveAllScene();

int LoadSceneFile();

//游戏中触发事件
//加载游戏
int LoadGame();
//移除元素
void RemoveSceneItem(PBase base);
//英雄在楼层移动
void SetHeroMoveFloorXY(int x, int y);
int HeroMoveFloor(int beforeIndex);
//怪兽战斗相关


//加载dll相关

void LoadAllModule();


// 声明一系列创建不同类型游戏对象的函数，它们都接受位置(x, y)和类型(type)作为参数，并返回一个指向sBase结构体的指针
PBase CreateWall(int x, int y, int type,const char* buf);
PBase CreateHero(int x, int y, int type, const char* buf);
PBase CreateYellowDoor(int x, int y, int type, const char* buf);
PBase CreateBlueDoor(int x, int y, int type, const char* buf);
PBase CreateRedDoor(int x, int y, int type, const char* buf);

PBase CreateGreenSlime(int x, int y, int type, const char* buf);
PBase CreateRedSlime(int x, int y, int type, const char* buf);
PBase CreateBlackSlime(int x, int y, int type, const char* buf);
PBase CreateBlueBat(int x, int y, int type, const char* buf);
PBase CreateBigBat(int x, int y, int type, const char* buf);
PBase CreateBlueMagic(int x, int y, int type, const char* buf);
PBase CreateSkeleton(int x, int y, int type, const char* buf);

PBase CreateYellowKey(int x, int y, int type, const char* buf);
PBase CreateBlueKey(int x, int y, int type, const char* buf);
PBase CreateRedKey(int x, int y, int type, const char* buf);
PBase CreateHpPick(int x, int y, int type, const char* buf);
PBase CreateMoneyPick(int x, int y, int type, const char* buf);
PBase CreateUpStairFloor(int x, int y, int type, const char* buf);
PBase CreateDownStairFloor(int x, int y, int type, const char* buf);
PBase CreateSwordPick(int x, int y, int type, const char* buf);
PBase CreateShop(int x, int y, int type, const char* buf);
#endif
