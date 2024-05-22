#ifndef _MAP_H_
#define _MAP_H_

#define mapX 13
#define mapY 13
#define M_index 4
//0· 1ǽ 2��� 3���� 4���� 5���� 
// 6��ͷ�� 7��ͷ�� 8������ 9����ʦ 10������ 11��ͷ�� 12������
// 13��Կ�� 14��Կ�� 15��Կ��
// 16Ѫ 17Ǯ 18��¥ 19��¥ 20�� 21�̵�
int g_mapIndex = 0;

int Maps[M_index][mapX][mapY];

void fillArrayFromFile(const char* filename, int index) {
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

//int Maps[M_index][mapX][mapY] = {
//    {
//        {1,1,1,1,1,1,1,1,1,1,1,1,1},
//        {1,1,1,1,1,1,18,1,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,3,1,1,1,1,1,1},
//        {1,1,1,1,1,3,0,21,1,1,1,1,1},
//        {1,1,1,1,1,1,0,1,1,1,1,1,1},
//        {1,1,1,1,1,1,2,1,1,1,1,1,1},
//        {1,1,1,1,1,1,1,1,1,1,1,1,1}
//    },
//    {
//    {1,1,1,1,1,1,1,1,1,1,1,1,1},
//    {1,18,0,13,6,7,6,0,0,0,0,0,1},
//    {1,1,1,1,1,1,1,1,1,1,1,0,1},
//    {1,16,0,10,3,0,1,16,13,16,1,0,1},
//    {1,13,10,17,1,0,1,16,13,16,1,0,1},
//    {1,1,3,1,1,0,1,1,1,11,1,0,1},
//    {1,13,10,0,1,0,3,9,6,8,1,0,1},
//    {1,17,0,14,1,0,1,1,1,1,1,0,1},
//    {1,1,3,1,1,0,0,0,0,0,0,0,1},
//    {1,0,10,0,1,1,5,1,1,1,3,1,1},
//    {1,16,16,13,1,15,0,0,1,13,10,14,1},
//    {1,16,0,13,1,0,19,0,1,13,13,13,1},
//    {1,1,1,1,1,1,1,1,1,1,1,1,1}
//    },
//    {
//        {1,1,1,1,1,1,1,1,1,1,1,1,1},
//        {1,19,1,0,10,0,1,0,0,13,15,1,1},
//        {1,0,1,17,1,16,1,0,0,13,14,1,1},
//        {1,0,1,13,1,13,1,0,0,13,10,1,1},
//        {1,0,1,13,1,13,1,1,1,1,3,1,1},
//        {1,0,1,0,1,0,0,0,3,0,0,1,1},
//        {1,0,1,3,1,1,3,1,1,3,1,1,1},
//        {1,0,5,0,0,0,0,1,0,10,0,1,1},
//        {1,0,1,3,1,1,4,1,3,1,3,1,1},
//        {1,0,1,13,1,16,17,1,0,1,0,1,1},
//        {1,0,1,13,1,16,16,1,0,1,0,1,1},
//        {1,18,1,17,1,17,16,1,0,1,0,1,1},
//        {1,1,1,1,1,1,1,1,1,1,1,1,1}
//    },
//    {
//        {1,1,1,1,1,1,1,1,1,1,1,1,1},
//        {1,20,7,13,1,0,21,0,1,1,1,1,1},
//        {1,7,13,0,1,0,0,0,1,0,8,0,1},
//        {1,13,10,0,1,1,3,1,1,0,1,0,1},
//        {1,1,3,1,1,1,0,10,1,13,1,7,1},
//        {1,0,0,0,1,1,1,0,1,13,1,8,1},
//        {1,6,1,0,8,7,8,0,1,13,1,7,1},
//        {1,6,1,1,1,1,1,0,0,0,1,0,1},
//        {1,0,0,0,0,0,1,1,3,1,1,0,1},
//        {1,1,1,1,1,8,1,7,0,7,1,0,1},
//        {1,1,0,0,0,0,1,17,8,13,1,0,1},
//        {1,19,0,1,1,1,1,0,0,0,1,0,1},
//        {1,1,1,1,1,1,1,1,1,1,1,1,1}
//    }
//};
#endif