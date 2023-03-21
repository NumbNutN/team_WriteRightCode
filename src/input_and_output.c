#include "robot.h"
#include "workbench.h"
#include "cfg.h"
#include "strategy.h"
/**
 * @brief 读取下一帧的输入
 * @birth: Created by LGD on 2023-3-20
*/
size_t workbenchNumber;
size_t order;
char endSig[4];

void read_next_frame()
{
    //第一行 帧序号 和 金钱数
    size_t money;
    scanf("%d %d\n",&order,&money);
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
    }
    printf("OK\n");
}

int main()
{
    workbench_initialize();
    while(1)
    {
        //读取当前帧信息
        read_next_frame();
        //进行机器人目标决策
        arbitrate_robot_behavior_frame();
        //输出当前帧指令
        output_arbitration();
    }
        

    
}