#ifndef _PUBLIC_H_2024_5_13_
#define _PUBLIC_H_2024_5_13_

// ������Ҫ�ı�׼��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>

// ����һ��ָ��sBase�ṹ���ָ������TBase
typedef struct sBase TBase;

// ����һ������ָ������PBase����ָ��һ������һ��ָ��sBase�ṹ���ָ����Ϊ����������һ��ָ��sBase�ṹ���ָ��ĺ���
typedef struct sBase(*PBase);

// ����FPrint����ָ������
typedef int (*FPrint)(PBase  self); 

// ����һ������ָ������FPrint����ָ��һ������һ��ָ��sBase�ṹ���ָ����Ϊ����������һ�������ĺ���
typedef int (*FCollion)(PBase  self, void* hero);
typedef void (*FRelese)(void* that);

// ����sBase�ṹ�壬����������Ϸ����Ļ������ԣ���λ��(x, y)������(type)�������ĳ���(scene)���Լ�һЩ��Ϊ����ָ��
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

// ����һ������ָ������FCreateMaster����ָ��һ����������������Ϊ����������һ��ָ��sBase�ṹ���ָ��ĺ���
typedef PBase(*FCreateMaster)(int x, int y, int type);

// ����һ������RegCreateMaster��������һ������������һ���������ǵĻص�������Ϊ����
void RegCreateMaster(int index, FCreateMaster cb);

// ����һ������RegCreateMasterAll����û�в�������������ע�����еĴ������ǵĻص�����
void RegCreateMasterAll();

// ����һ��ָ��sScene�ṹ���ָ������TScene��һ������ָ������PScene
typedef struct sScene
{
    PBase bases[1024];
    int index;
    int indexScene;
}TScene, (*PScene);

// ����һ������CreateScene��������һ���������顢��Ⱥ͸߶���Ϊ������������һ��ָ��sScene�ṹ���ָ��
PScene CreateScene(int* maps, int w, int h);

// ����һ������PrintScene��������һ��ָ��sScene�ṹ���ָ����Ϊ����
void PrintScene(PScene scene);

// ����һ������UpdateScene��������һ��ָ��sScene�ṹ���ָ����Ϊ����
void UpdateScene(PScene scene);

// ����һϵ�д�����ͬ������Ϸ����ĺ��������Ƕ�����λ��(x, y)������(type)��Ϊ������������һ��ָ��sBase�ṹ���ָ��
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
