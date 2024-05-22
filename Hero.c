#define _CRT_SECURE_NO_WARNINGS
#include "hero.h"
#include <assert.h>

static PHero s_hero = NULL;
static void Print(PBase self)
{
    PHero hero = (PHero)self;
    printf("\033[%d;%dH人", (hero->base.x + 1), (hero->base.y + 1) * 2);
}

int Hero_Init(PHero hero)
{
    const char* filename = ".\\hero\\Hero_Init.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        exit(1);
    }

    // Ensure fscanf returns the expected number of fields read
    int ReadFile = fscanf(file, "%d", &hero->level); // Note the '&' before hero->level
    if (ReadFile != 1) {
        printf("Error reading level from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->hp);
    if (ReadFile != 1) {
        printf("Error reading hp from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->atk);
    if (ReadFile != 1) {
        printf("Error reading atk from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->def);
    if (ReadFile != 1) {
        printf("Error reading def from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->gold);
    if (ReadFile != 1) {
        printf("Error reading gold from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->exp);
    if (ReadFile != 1) {
        printf("Error reading exp from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->yellow);
    if (ReadFile != 1) {
        printf("Error reading yellow from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->blue);
    if (ReadFile != 1) {
        printf("Error reading blue from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    ReadFile = fscanf(file, "%d", &hero->red);
    if (ReadFile != 1) {
        printf("Error reading red from file.\n");
        fclose(file);
        return -1; // Indicate failure
    }

    fclose(file);
    return 0; // Success
}



PBase CreateHero(int x, int y, int type)
{
    if(s_hero!=NULL)
    {
        assert(s_hero!=NULL);
        //return (PBase)s_hero;
        return NULL;
    }


    PHero hero = malloc(sizeof(THero));
    hero->base.x = x;
    hero->base.y = y;
    hero->base.type = type;
    hero->base.scene = NULL;
    hero->base.Print = Print;
    //1lv 800hp 10atk 10def 0gold 0exp 1yellow 1blue 1red
    //hero->level = 1;
    //hero->hp = 800;
    //hero->atk = 10;
    //hero->def = 10;
    //hero->gold = 20;
    //hero->exp = 0;
    //hero->yellow = 1;
    //hero->blue = 1;
    //hero->red = 1;
        int isInit_Hero = Hero_Init(hero);
        if (isInit_Hero == -1) {
            printf("Init Hero Error");
            exit(1);
        }
    s_hero = hero;
    return (PBase)hero;
}


PHero GetHero()
{
    return s_hero;
}

void ShowHero()
{
    printf("\033[18;1H-----------------------------");
    printf("\033[19;1H英雄:人族大帝");
    printf("\033[20;1H等级:%d",s_hero->level);
    printf("\033[21;1H生命:%d",s_hero->hp);
    printf("\033[22;1H攻击力:%d",s_hero->atk);
    printf("\033[23;1H防御力:%d",s_hero->def);
    printf("\033[24;1H钱:%d",s_hero->gold);
    printf("\033[25;1H经验:%d",s_hero->exp);
    printf("\033[26;1H黄钥匙:%d",s_hero->yellow);
    printf("\033[27;1H蓝钥匙:%d",s_hero->blue);
    printf("\033[28;1H红钥匙:%d",s_hero->red);
    printf("\033[29;1H-----------------------------");
    //printf("\033[10;35H红钥匙:%d", s_hero->red);
}

int SaveHero()
{
    const char* HeroFileName[1024];
    /*sprintf(filename, ".\\save\\SaveHero%d.txt", g_SaveHeroIndex);*/
    sprintf(HeroFileName, ".\\save\\SaveHero.txt");
    FILE* file = fopen(HeroFileName, "w");// 使用"w"模式打开文件，这将清空文件内容

    if (file == NULL) {
        printf("Failed to open file %s\n", HeroFileName);
        return 0;
    }

    // 写入英雄的属性
    fprintf(file, "%d\n", s_hero->level);
    fprintf(file, "%d\n", s_hero->hp);
    fprintf(file, "%d\n", s_hero->atk);
    fprintf(file, "%d\n", s_hero->def);
    fprintf(file, "%d\n", s_hero->gold);
    fprintf(file, "%d\n", s_hero->exp);
    fprintf(file, "%d\n", s_hero->yellow);
    fprintf(file, "%d\n", s_hero->blue);

    fclose(file);
    return 1;
}