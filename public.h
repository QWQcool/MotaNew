#ifndef _PUBLIC_H_2024_5_13_
#define _PUBLIC_H_2024_5_13_

// 包含必要的标准库头文件
#include <stdio.h>
#include <stdlib.h>

// 定义一个指向sBase结构体的指针类型TBase
typedef struct sBase TBase;

// 定义一个函数指针类型PBase，它指向一个接受一个指向sBase结构体的指针作为参数并返回一个指向sBase结构体的指针的函数
typedef struct sBase(*PBase);

// 定义FPrint函数指针类型
typedef int (*FPrint)(PBase  self); 

// 定义一个函数指针类型FPrint，它指向一个接受一个指向sBase结构体的指针作为参数并返回一个整数的函数
typedef int (*FCollion)(PBase  self, void* hero);
typedef void (*FRelese)(void* that);

// 定义sBase结构体，它包含了游戏对象的基本属性，如位置(x, y)、类型(type)、关联的场景(scene)、以及一些行为函数指针
typedef struct sBase
{
    int x;
    int y;
    int type;
    struct sScene* scene;
    FPrint Print;
    FCollion Collion;
    FRelese release;
};

// 定义一个函数指针类型FCreateMaster，它指向一个接受三个整数作为参数并返回一个指向sBase结构体的指针的函数
typedef PBase(*FCreateMaster)(int x, int y, int type);

// 声明一个函数RegCreateMaster，它接受一个整数索引和一个创建主角的回调函数作为参数
void RegCreateMaster(int index, FCreateMaster cb);

// 声明一个函数RegCreateMasterAll，它没有参数，可能用于注册所有的创建主角的回调函数
void RegCreateMasterAll();

// 定义一个指向sScene结构体的指针类型TScene和一个函数指针类型PScene
typedef struct sScene
{
    PBase bases[1024];
    int index;
    int indexScene;
}TScene, (*PScene);

// 声明一个函数CreateScene，它接受一个整数数组、宽度和高度作为参数，并返回一个指向sScene结构体的指针
PScene CreateScene(int* maps, int w, int h);

// 声明一个函数PrintScene，它接受一个指向sScene结构体的指针作为参数
void PrintScene(PScene scene);

// 声明一个函数UpdateScene，它接受一个指向sScene结构体的指针作为参数
void UpdateScene(PScene scene);

// 声明一系列创建不同类型游戏对象的函数，它们都接受位置(x, y)和类型(type)作为参数，并返回一个指向sBase结构体的指针
PBase CreateWall(int x, int y, int type);
PBase CreateHero(int x, int y, int type);
PBase CreateYellowDoor(int x, int y, int type);
PBase CreateBlueDoor(int x, int y, int type);
PBase CreateRedDoor(int x, int y, int type);
PBase CreateYellowKey(int x, int y, int type);
PBase CreateBlueKey(int x, int y, int type);
PBase CreateRedKey(int x, int y, int type);
PBase CreateHpPick(int x, int y, int type);
PBase CreateMoneyPick(int x, int y, int type);
PBase CreateUpStairFloor(int x, int y, int type);
PBase CreateDownStairFloor(int x, int y, int type);
PBase CreateShop(int x, int y, int type);
#endif
