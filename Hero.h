#ifndef _HERO_H_2024_5_13_
#define _HERO_H_2024_5_13_

#include "public.h"


typedef struct sHero
{
    TBase base;
	int level;
	int hp;
	int atk;
	int def;
	int gold;
	int exp;
	int yellow;
	int blue;
	int red;
}THero, * PHero;

PBase CreateHero(int x, int y, int type);

PHero GetHero();

int Hero_Init(PHero hero);

void ShowHero();

int SaveHero();

#endif
