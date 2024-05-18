#include "public.h"

// ����һ����̬����s_creates�����ڴ洢��ͬ���͵���Ϸ���󴴽�����
static FCreateMaster  s_creates[1024] = { 0 };

// ����RegCreateMaster����ע��һ���µ���Ϸ���󴴽�������s_creates������
void RegCreateMaster(int index, FCreateMaster cb)
{
    s_creates[index] = cb;
}

// ����RegCreateMasterAll����ע������Ԥ�������Ϸ���󴴽�����
void RegCreateMasterAll()
{
    RegCreateMaster(1, CreateWall); // ע�ᴴ��ǽ�ڵĺ���
    RegCreateMaster(2, CreateHero); // ע�ᴴ��Ӣ�۵ĺ���
    RegCreateMaster(3, CreateYellowDoor); // ע�ᴴ����ɫ�ŵĺ���
    RegCreateMaster(4, CreateBlueDoor); // ע�ᴴ����ɫ�ŵĺ���
    RegCreateMaster(5, CreateRedDoor); // ע�ᴴ����ɫ�ŵĺ���
    RegCreateMaster(13, CreateYellowKey);
    RegCreateMaster(14, CreateBlueKey);
    RegCreateMaster(15, CreateRedKey);
    RegCreateMaster(18, CreateUpStairFloor); // ע�ᴴ����¥�ݵĵذ�ĺ���
    RegCreateMaster(19, CreateDownStairFloor); // ע�ᴴ����¥�ݵĵذ�ĺ���
    RegCreateMaster(21, CreateShop); // ע�ᴴ����¥�ݵĵذ�ĺ���
}

static int s_Sceneindex = 0;
// ����CreateScene���ڸ��ݸ����ĵ�ͼ���ݴ���һ������
PScene CreateScene(int* maps, int w, int h)
{
    // �����ڴ����ڴ洢������Ϣ
    PScene scene = (PScene)malloc(sizeof(TScene));
    scene->index = 0;
    scene->indexScene = s_Sceneindex;
    s_Sceneindex++;
    // ������ͼ���ݣ���ÿ��λ�õ�����Ӧ�Ĵ�������
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            // ��ȡ��ǰλ�õ�����
            int type = maps[x * w + y];

            // �������ʹ�s_creates�����л�ȡ��Ӧ�Ĵ�������
            FCreateMaster f = s_creates[type];
            if (f == NULL) continue; // ���û���ҵ���Ӧ�Ĵ��������������˴�ѭ��

            // ���ô�������������Ϸ����
            PBase base = f(x, y, type);
            if (base == NULL) continue; // �������ʧ�ܣ������˴�ѭ��

            // ���´�������Ϸ������ӵ�������
            base->scene = scene;
            scene->bases[scene->index] = base;
            scene->index++;
        }
    }

    // ���ش����ĳ���
    return scene;
}
