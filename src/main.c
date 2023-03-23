#include "io.h"

int main()
{
    //机器人初始化
    botInit();
    //初始帧
    readUntilOK();
    //printf("OK\n");
    puts("OK");
    fflush(stdout);
    while(scanf("%d ", &order) != EOF)
    {
        //读取当前帧信息
        read_next_frame();
        //readUntilOK();
        //进行机器人目标决策
        arbitrate_robot_behavior_frame();
        //输出当前帧指令
        output_arbitration();
        printf("OK\n",order);
        fflush(stdout);
    }
    
}