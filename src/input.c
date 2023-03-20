#include "robot.h"
#include "workbench.h"
#include "cfg.h"
/**
 * @brief 读取下一帧的输入
 * @birth: Created by LGD on 2023-3-20
*/
size_t workbenchNumber;
void read_next_frame()
{
    //第一行 帧序号 和 金钱数
    size_t order,money;
    scanf("%d %d\n",order,money);
    //第二行 工作台的数量

    scanf("%d\n",workbenchNumber);
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
    char* endSig;
    scanf("%s\n",endSig);
}