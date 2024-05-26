#define _CRT_SECURE_NO_WARNINGS
#include "hero.h"
#include <assert.h>

static PHero s_hero = NULL;
static void Print(PBase self)
{
    PHero hero = (PHero)self;
    printf("\033[%d;%dH��", (hero->base.x + 1), (hero->base.y + 1) * 2);
}

static int HeroSave(PBase self, const char* buf, int size)
{
    PHero hero = (PHero)self;
    int nret = sprintf(buf, "%d %d %d %s %d %d %d %d %d %d %d %d %d",
        hero->base.type, hero->base.x, hero->base.y, 
        hero->name, hero->level,hero->hp, hero->atk, hero->def, hero->gold, hero->exp,hero->yellow,hero->blue,hero->red
    );
    if (nret == -1)
    {
        printf("Error in save %d", self->type);
        exit(1);
    }
    return nret;
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

        ReadFile = fscanf(file, "%s", hero->name);
        if (ReadFile != 1 || hero->name[0] == '\0') {
            printf("Error reading Heroname from file.\n");
            fclose(file);
            return -1; // Indicate failure
        }

        //fgets(hero->name, sizeof(hero->name), file);
        //hero->name[strcspn(hero->name, "\n")] = 0; // �Ƴ����з�

        fclose(file);


    return 0; // Success
}

PBase CreateHero(int x, int y, int type)
{
    if(s_hero!=NULL)
    {
        //assert(s_hero!=NULL);
        return (PBase)s_hero;
        return NULL;
    }


    PHero hero = malloc(sizeof(THero));
    hero->base.x = x;
    hero->base.y = y;
    hero->base.type = type;
    hero->base.scene = NULL;
    hero->base.Print = Print;
    hero->base.Save = HeroSave;
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
    printf("\033[19;1HӢ��:%s",s_hero->name);
    printf("\033[20;1H�ȼ�:%d",s_hero->level);
    printf("\033[21;1H����:%d",s_hero->hp);
    printf("\033[22;1H������:%d",s_hero->atk);
    printf("\033[23;1H������:%d",s_hero->def);
    printf("\033[24;1HǮ:%d",s_hero->gold);
    printf("\033[25;1H����:%d",s_hero->exp);
    printf("\033[26;1H��Կ��:%d",s_hero->yellow);
    printf("\033[27;1H��Կ��:%d",s_hero->blue);
    printf("\033[28;1H��Կ��:%d",s_hero->red);
    printf("\033[29;1HWASD���ߣ�K������Ϸ��L������Ϸ");
    printf("\033[30;1H-----------------------------");
    //printf("\033[10;35H��Կ��:%d", s_hero->red);
}

int Save_Hero()
{
    const char* HeroFileName[1024];
    /*sprintf(filename, ".\\save\\SaveHero%d.txt", g_SaveHeroIndex);*/
    sprintf(HeroFileName, ".\\save\\SaveHero.txt");
    FILE* file = fopen(HeroFileName, "w");// ʹ��"w"ģʽ���ļ����⽫����ļ�����

    if (file == NULL) {
        //printf("Failed to open file %s\n", *HeroFileName);
        return 0;
    }

    // д��Ӣ�۵�����
    fprintf(file, "%d\n", s_hero->level);
    fprintf(file, "%d\n", s_hero->hp);
    fprintf(file, "%d\n", s_hero->atk);
    fprintf(file, "%d\n", s_hero->def);
    fprintf(file, "%d\n", s_hero->gold);
    fprintf(file, "%d\n", s_hero->exp);
    fprintf(file, "%d\n", s_hero->yellow);
    fprintf(file, "%d\n", s_hero->blue);
    fprintf(file, "%d\n", s_hero->red);
    fprintf(file, "%s\n", s_hero->name);

    fclose(file);
    return 1;
}


int LoadHero(char* HeroName,int level,int hp,int atk,int def, int gold, int exp , int yellow , int blue,int red)
{
    //s_hero->name = HeroName;
    strncpy(s_hero->name, HeroName, sizeof(s_hero->name));
    s_hero->level = level;
    s_hero->hp = hp;
    s_hero->atk = atk;
    s_hero->def = def;
    s_hero->gold = gold;
    s_hero->exp = exp;
    s_hero->yellow = yellow;
    s_hero->blue = blue;
    s_hero->red = red;
}