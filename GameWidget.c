#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include "public.h"

int Show_Widget()
{
    static int s_selectPos = 1;
    int IndexItem = 4;
    int isExit = 0;  //0����ѭ����1�˳�ѭ��
    int isSelect = 0;
    char* shopItem[1024] =
    {
        "",
        "��ʼ��Ϸ",
        "��ȡ�浵",
        "������Ϸ",
        "�˳���Ϸ"
    };
    printf("\033[2J\033[1;1H");
    printf("\033[%d;35H------------------------------", 10);
    for (int i = 1; i <= IndexItem; i++)
    {
        if (i == s_selectPos)printf("\033[%d;35H>\033[91m%s\n\n\033[0m",10+i*2, shopItem[i]);
        else printf("\033[%d;35H%s\n\n", 10+i*2,shopItem[i]);
    }
    printf("\033[%d;35HQ�˳� B���� WS��ѡ\n", 10+(IndexItem+1)*2);
    printf("\033[%d;35H------------------------------", 10 + (IndexItem + 2) * 2);
    printf("\033[?25l");
    switch (_getch())
    {
    case 'W':
    case'w':
        s_selectPos--;
        if (s_selectPos <= 0)
        {
            s_selectPos = IndexItem;
        }
        break;
    case'S':
    case's':
        s_selectPos++;
        if (s_selectPos > IndexItem)
        {
            s_selectPos = 1;
        }
        break;
    case'Q':
    case'q':
        exit(1);
        break;
    case'B':
    case'b':
        isSelect = 1;
        break;
    default:
        break;
    }
    if (isSelect)
    {
        switch (s_selectPos)
        {
        case 1:
            Game_Init();
            isExit = 1;
            break;
        case 2:
            Load_Init();

            isExit = 1;
            //TODO
            //�浵ѡ�񣬶���浵
            break;
        case 3:
            //TODO
            //�Լ��ĸ�����Ե��
            break;
        case 4:
            exit(1);
            break;
        default:
            break;
        }
        isSelect = 0;
    }
    return isExit;
}
