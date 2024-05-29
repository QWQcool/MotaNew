#include "public.h"

// ����һ����̬����s_creates�����ڴ洢��ͬ���͵���Ϸ���󴴽�����
static FCreateMaster  s_creates[1024] = { 0 };

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
    //6��ͷ�� 7��ͷ�� 8��ͷ�� 9������ 10������ 11����ʦ 12������
    RegCreateMaster(6, CreateGreenSlime);
    RegCreateMaster(7, CreateRedSlime);
    RegCreateMaster(8, CreateBlackSlime);
    RegCreateMaster(9, CreateBlueBat);
    RegCreateMaster(10, CreateBigBat);
    RegCreateMaster(11, CreateBlueMagic);
    RegCreateMaster(12, CreateSkeleton);

    RegCreateMaster(13, CreateYellowKey);
    RegCreateMaster(14, CreateBlueKey);
    RegCreateMaster(15, CreateRedKey);
    RegCreateMaster(16, CreateHpPick);
    RegCreateMaster(17, CreateMoneyPick);
    RegCreateMaster(18, CreateUpStairFloor); // ע�ᴴ����¥�ݵĵذ�ĺ���
    RegCreateMaster(19, CreateDownStairFloor); // ע�ᴴ����¥�ݵĵذ�ĺ���
    RegCreateMaster(20, CreateSwordPick);
    RegCreateMaster(21, CreateShop); 
}

static int sg_Sceneindex = 0;


PScene CreateScene(int* maps, int w, int h)
{
    // �����ڴ����ڴ洢������Ϣ
    PScene scene = (PScene)malloc(sizeof(TScene));
    scene->index = 0;
    scene->indexScene = sg_Sceneindex;
    sg_Sceneindex++;
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
            PBase base = f(x, y, type,NULL);
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

//�¼��ط�ʽ
int LoadSceneFile()
{
    const char filename[1024];
    for (int i = 0; i < g_ShareMemory; i++)
    {
        int sX = 0;
        int sY = 0;
        int sType = 0;
        sprintf(filename, ".\\scenes\\%d.scene.txt", i);
        FILE* file = fopen(filename, "r");
        if (file == NULL) 
        {
            printf("Failed to open file %s\n", filename);
            exit(1);
        }
        g_scene[i] = (PScene)malloc(sizeof(TScene));

        g_scene[i]->index = 0;
        int indexLast = 0;
        do
        {
            char buf[1024] = { 0 };
            fgets(buf, 1024, file);
            sscanf(buf, "%d %d", &g_scene[i]->indexScene, &indexLast);
        } while (0);
        for (int j = 0; j < indexLast; j++)
        {
            char buf[1024] = { 0 };
            fgets(buf, 1024, file);
            int sType, sX, sY;
            sscanf(buf, "%d %d %d", &sType, &sX, &sY);
            if (sType == 2)
            {
                g_mapIndex = g_scene[i]->indexScene;
            }
            FCreateMaster f = s_creates[sType];
            if (f == NULL)continue;

            PBase base = f(sX, sY, sType, buf);
            if (base == NULL)continue;
            base->scene = g_scene[i];
            g_scene[i]->bases[g_scene[i]->index++] = base;
        }
        fclose(file);
    }
    return 1;
}

//��ʼ��Ϸ������ͼ��ʼ����
void fillArrayFromFile(const char* filename, int index) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return;
    }

    int row, col;
    for (row = 0; row < mapX; row++) {
        for (col = 0; col < mapY; col++) {
            if (fscanf(file, "%d", &Maps[index][row][col]) != 1) {
                printf("Failed to read data from file %s\n", filename);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
}

int Map_Init()
{
    char mapSourceFile[256];
    for (int i = 0; i < M_index; i++)
    {
        sprintf(mapSourceFile, ".\\map\\map%d.txt", i);
        fillArrayFromFile(mapSourceFile, i);
    }
}

//�ϼ��ط�ʽ
//int LoadScene()
//{
//    const char* filename = ".\\save\\SaveScene.txt";
//    FILE* file = fopen(filename, "r");
//    if (file == NULL) {
//        printf("Failed to open file %s\n", filename);
//        exit(1);
//    }
//    int indexLast = 0;
//    int sX = 0;
//    int sY = 0;
//    int sType = 0;
//    fscanf(file, "%d", &g_mapIndex);
//    for (int i = 0; i < g_ShareMemory; i++)
//    {
//        int FileIndexLast = fscanf(file, "%d", &indexLast);
//        g_scene[i] = (PScene)malloc(sizeof(TScene));
//        g_scene[i]->indexScene = i;
//        g_scene[i]->index = 0;
//        if (FileIndexLast != 1) {
//            printf("Error reading FileIndexLast from file.\n");
//            fclose(file);
//            Sleep(1000);
//            return 0; // Indicate failure
//        }
//        for (int j = 0; j < indexLast; j++)
//        {
//            int FileX = fscanf(file, "%d", &sX);
//            int FileY = fscanf(file, "%d", &sY);
//            int FileT = fscanf(file, "%d", &sType);
//            if (FileT != 1 && FileX != 1 && FileY != 1) {
//                printf("Error reading xyType from file.\n");
//                fclose(file);
//                Sleep(1000);
//                return 0; // Indicate failure
//            }
//            // �������ʹ�s_creates�����л�ȡ��Ӧ�Ĵ�������
//            FCreateMaster f = s_creates[sType];
//            if (f == NULL) continue; // ���û���ҵ���Ӧ�Ĵ��������������˴�ѭ��
//
//            // ���ô�������������Ϸ����
//            PBase base = f(sX, sY, sType);
//            if (base == NULL) continue; // �������ʧ�ܣ������˴�ѭ��
//
//            // ���´�������Ϸ������ӵ�������
//            base->scene = g_scene[i];
//            g_scene[i]->bases[g_scene[i]->index] = base;
//            g_scene[i]->index++;
//        }
//    }
//    fclose(file);
//    return 1;
//}
