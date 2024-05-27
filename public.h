#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#define _CRT_SECURE_NO_WARNINGS
// ������Ҫ�ı�׼��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

typedef struct sBase TBase;

typedef struct sBase(*PBase);

typedef int (*FPrint)(PBase  self); 

typedef int (*FCollion)(PBase  self, void* hero);
typedef void (*FRelese)(void* that);
typedef int (*FSave)(PBase  self, const char* buf, int size);

typedef struct sBase
{
    int x;
    int y;
    int type;
    struct sScene* scene;
    FPrint Print;
    FCollion Collion;
    FRelese release;
    FSave  Save;
};

typedef PBase(*FCreateMaster)(int x, int y, int type);

void RegCreateMaster(int index, FCreateMaster cb);

void RegCreateMasterAll();

// ����һ��ָ��sScene�ṹ���ָ������TScene��һ������ָ������PScene
typedef struct sScene
{
    PBase bases[1024];
    int index;
    int indexScene;
}TScene, (*PScene);

int g_ShareMemory;  //��g_scene�����˼���scene
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

//��Ϸ�д����¼�
//������Ϸ
int LoadGame();
//�Ƴ�Ԫ��
void RemoveSceneItem(PBase base);
//Ӣ����¥���ƶ�
void SetHeroMoveFloorXY(int x, int y);
int HeroMoveFloor(int beforeIndex);

// ����һϵ�д�����ͬ������Ϸ����ĺ��������Ƕ�����λ��(x, y)������(type)��Ϊ������������һ��ָ��sBase�ṹ���ָ��
PBase CreateWall(int x, int y, int type);
PBase CreateHero(int x, int y, int type);
PBase CreateYellowDoor(int x, int y, int type);
PBase CreateBlueDoor(int x, int y, int type);
PBase CreateRedDoor(int x, int y, int type);

PBase CreateGreenSlime(int x, int y, int type);
PBase CreateRedSlime(int x, int y, int type);
PBase CreateBlackSlime(int x, int y, int type);
PBase CreateBlueBat(int x, int y, int type);
PBase CreateBigBat(int x, int y, int type);
PBase CreateBlueMagic(int x, int y, int type);
PBase CreateSkeleton(int x, int y, int type);

PBase CreateYellowKey(int x, int y, int type);
PBase CreateBlueKey(int x, int y, int type);
PBase CreateRedKey(int x, int y, int type);
PBase CreateHpPick(int x, int y, int type);
PBase CreateMoneyPick(int x, int y, int type);
PBase CreateUpStairFloor(int x, int y, int type);
PBase CreateDownStairFloor(int x, int y, int type);
PBase CreateSwordPick(int x, int y, int type);
PBase CreateShop(int x, int y, int type);
#endif
