#include "robot.h"
#include "workbench.h"
#include "cfg.h"
#include "strategy.h"
#include <stdlib.h>

/**
 * @brief 读取下一帧的输入
 * @birth: Created by LGD on 2023-3-20
*/
size_t workbenchNumber;
size_t order;
//缓冲区下标计数器
size_t buf_cnt = 0;
char endSig[4];
char line[1024];

/**
 * @brief 初始帧
*/
bool readUntilOK() {
    while (fgets(&line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        //do something
    }
    return false;
}

/**
 * @brief 每一行输入
*/
void readALine()
{
    fgets(&line, sizeof line, stdin);
    buf_cnt = 0;
}

/**
 * @brief 字符串特定字符替换
*/
void switch_char(char* str,char old,char new)
{
    int cnt = 0;
    while(str[cnt]!='\n')
    {
        if(str[cnt] == old)
            str[cnt] == new;
        cnt++;
    }
}

/**
 * @brief 从当前下标位置提出整数
*/
int get_a_interger(char* str,int i)
{
    return atoi(&str[i]);
}

/**
 * @brief 从当前下标提出浮点数
*/
float get_a_float(char* str,int i)
{
    return atof(&str[i]);
}

/**
 * @brief 获取当前指定字符的下标
*/
size_t get_next_char_order(char* str,char spe)
{
    size_t cnt=0;
    for(;str[cnt]!=spe;cnt++);
    return buf_cnt+cnt;
}

/**
 * @brief 绕过当前指定字符
*/
size_t pass_next_char_order(char* str,char spe)
{
    return get_next_char_order(str,spe) +1;
}


void read_next_frame()
{
#ifdef READ_FRAME_IN_BUFFER
    //从金钱数开始全部存储在数组中
    readALine();
    size_t money;
    //金钱
    money = get_a_interger(line,buf_cnt);
    //buf_cnt = pass_next_char_order(&line[buf_cnt],'\n');
    //工作台数量
    readALine();
    workbenchNumber = get_a_interger(line,buf_cnt);
    //buf_cnt = pass_next_char_order(&line[buf_cnt],'\n');
    //每一个工作台的数据
    for(int i=0;i<workbenchNumber;i++)
    {
        workbench_read_status(&wbList[i]);
    }
    //每一个机器人的数据
    for(int i=0;i<ROBOT_NUMBER;i++)
    {
        robot_read_status(&botList[i]);
    }
    readUntilOK();

#elif define READ_FRAME_SCAN_FORMAT 
    //第一行 帧序号 和 金钱数
    size_t money;
    scanf("%d\n",&money);
    //第二行 工作台的数量

    scanf("%d\n",&workbenchNumber);
    //每一个工作台的数据
    for(int i=0;i<workbenchNumber;i++)
    {
        workbench_read_status(&wbList[i]);
    }
    //每一个机器人的数据
    for(int i=0;i<ROBOT_NUMBER;i++)
    {
        robot_read_status(&botList[i]);
    }
    scanf("%s\n",endSig);
#endif
}

/**
 * @brief 输出当前帧决策
 * @birth: Created by LGD on 2023-3-21
*/
void output_arbitration()
{
    printf("%d\n",order);
    for(int i=0;i<ROBOT_NUMBER;i++)
    {
        if(botList[i].botStatus == PERFORMING)
        {
            printf("forward %d %f\n",i,botList[i].forward);
            printf("rotate %d %f\n",i,botList[i].rotate);
        }
        robot_set_purchase_sell(&botList[i]);
    }
}

