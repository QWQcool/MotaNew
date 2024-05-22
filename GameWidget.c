#include<Windows.h>
#include<stdio.h>
#include<conio.h>

int g_isLoad = 0;
int g_SaveIndex = 0;
int Game_Init();
int Load_Init();

int Show_Widget()
{
    static int s_selectPos = 1;
    int IndexItem = 4;
    int isExit = 0;  //0继续循环，1退出循环
    int isSelect = 0;
    char* shopItem[1024] =
    {
        "",
        "开始游戏",
        "读取存档",
        "关于游戏",
        "退出游戏"
    };
    printf("\033[2J\033[1;1H");
    for (int i = 1; i <= IndexItem; i++)
    {
        if (i == s_selectPos)printf(">\033[91m%s\n\n\033[0m", shopItem[i]);
        else printf("%s\n\n", shopItem[i]);
    }
    printf("Q退出 B进入 WS挑选\n");
    switch (_getch())
    {
    case 'W':
    case'w':
        s_selectPos--;
        if (s_selectPos <= 0)
        {
            s_selectPos = IndexItem - 1;
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
            Load_Init(g_SaveIndex);

            isExit = 1;
            //TODO
            //存档
            break;
        case 3:
            //TODO
            //自己的感悟与缘由
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

int LoadSaveOp()
{

}