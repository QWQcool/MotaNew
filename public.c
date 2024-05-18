#include "public.h"

// 定义一个静态数组s_creates，用于存储不同类型的游戏对象创建函数
static FCreateMaster  s_creates[1024] = { 0 };

// 函数RegCreateMaster用于注册一个新的游戏对象创建函数到s_creates数组中
void RegCreateMaster(int index, FCreateMaster cb)
{
    s_creates[index] = cb;
}

// 函数RegCreateMasterAll用于注册所有预定义的游戏对象创建函数
void RegCreateMasterAll()
{
    RegCreateMaster(1, CreateWall); // 注册创建墙壁的函数
    RegCreateMaster(2, CreateHero); // 注册创建英雄的函数
    RegCreateMaster(3, CreateYellowDoor); // 注册创建黄色门的函数
    RegCreateMaster(4, CreateBlueDoor); // 注册创建蓝色门的函数
    RegCreateMaster(5, CreateRedDoor); // 注册创建红色门的函数
    RegCreateMaster(13, CreateYellowKey);
    RegCreateMaster(14, CreateBlueKey);
    RegCreateMaster(15, CreateRedKey);
    RegCreateMaster(18, CreateUpStairFloor); // 注册创建上楼梯的地板的函数
    RegCreateMaster(19, CreateDownStairFloor); // 注册创建下楼梯的地板的函数
    RegCreateMaster(21, CreateShop); // 注册创建下楼梯的地板的函数
}

static int s_Sceneindex = 0;
// 函数CreateScene用于根据给定的地图数据创建一个场景
PScene CreateScene(int* maps, int w, int h)
{
    // 分配内存用于存储场景信息
    PScene scene = (PScene)malloc(sizeof(TScene));
    scene->index = 0;
    scene->indexScene = s_Sceneindex;
    s_Sceneindex++;
    // 遍历地图数据，对每个位置调用相应的创建函数
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            // 获取当前位置的类型
            int type = maps[x * w + y];

            // 根据类型从s_creates数组中获取相应的创建函数
            FCreateMaster f = s_creates[type];
            if (f == NULL) continue; // 如果没有找到对应的创建函数，跳过此次循环

            // 调用创建函数创建游戏对象
            PBase base = f(x, y, type);
            if (base == NULL) continue; // 如果创建失败，跳过此次循环

            // 将新创建的游戏对象添加到场景中
            base->scene = scene;
            scene->bases[scene->index] = base;
            scene->index++;
        }
    }

    // 返回创建的场景
    return scene;
}
