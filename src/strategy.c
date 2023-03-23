#include "cfg.h"
#include "robot.h"
#include "workbench.h"
#include <math.h>
#include "myFilter.h"

/**
 * @brief 判断浮点数是否同号
*/
bool is_same_sybol(float a,float b)
{
    return a*b >0;
}
/**
 * @brief 计算机器人和工作台的距离
*/
float calculate_distance(struct _Robot* bot,struct _WorkBench* wb)
{
    float distance = pow(pow(bot->LocationX - wb->positionX,2) + pow(bot->LocationY - wb->positionY,2),0.5);
    return distance;
}

/**
 * @brief 计算机器人和工作台的夹角 逆时针为负值 右方向为0
*/
float calculate_angle(struct _Robot* bot,struct _WorkBench* wb)
{   
    float tan_value = (wb->positionY - bot->LocationY) / (wb->positionX - bot->LocationX); 
    //计算反正切
    float workBenchDirection = atan(tan_value);

#ifdef CALCULATE_ANGLE_STRATEGY_1
    if(is_same_sybol(bot->toWard,workBenchDirection))
    {
        return bot->toWard - workBenchDirection;
    }
    else{
        if(fabs((workBenchDirection)/(bot->toWard - PI)) < 1)
            return bot->toWard - workBenchDirection;
        else   
        {
            float result = 2*PI - fabs(bot->toWard) - fabs(workBenchDirection);
            return 2*PI - fabs(bot->toWard) - fabs(workBenchDirection);
        }
            
    }
#endif
#ifdef CALCULATE_ANGLE_STRATEGY_2
    float botToWord = bot->toWard;
    if(bot->toWard <0)
        botToWord = 2*PI + bot->toWard;

    if(botToWord - workBenchDirection < PI)
        return -(botToWord - workBenchDirection);
    else
        return 2*PI - (botToWord - workBenchDirection);
#endif
}

/**
 * @brief 转换 秒和帧两种单位
*/
size_t convertSec2Frame(float sec)
{
    return (size_t)(sec*50);
}
/**
 * @brief 计算机器人到达工作台的时间
*/
size_t calculate_arrive_time(struct _Robot* bot,struct _WorkBench* wb)
{
#ifdef LOW_LEVEL_KINESIOLOGY
    float veerTimeSec = calculate_angle(bot,wb)  / ROBOT_MAX_PALSTANCE;
    float driveTimeSec = calculate_distance(bot,wb) / ROBOT_MAX_LINEAR_VELOCITY_FORWARD;
    return convertSec2Frame(veerTimeSec + driveTimeSec);
#endif
}

/**
 * @brief 返回满足选择器要求的工作台
 * @param filter:function 过滤器，只有满足filter要求的序号会被选择器考虑
 * @param selector:function 选择器，遍历所有工作台选择一个满足条件的最优情况
 * @return 0-WORKBENCHNUMBER 如果没有符合条件的，则返回NULL
 * @birth: Created by LGD on 2023-3-20
*/
struct _WorkBench* selectWorkBench(struct _Robot* bot,bool(*filter)(struct _WorkBench*,struct _Robot*),bool(*selector)(struct _WorkBench*,struct _Robot*,int))
{
    int recordOrder = -1;
    for(int i=0;i<workbenchNumber;i++)
    {
        //开过滤器
        if(filter)
        {
            if(!filter(&wbList[i],bot))
                continue;
        }
        if(selector(&wbList[i],bot,i))
            recordOrder = i;
        
    }
    return recordOrder == -1? NULL : &wbList[recordOrder];
}

/**
 * @brief 决策机器人行为
 * @birth: Created by LGD on 2023-3-21
*/
void arbitrate_robot_behavior(struct _Robot* bot)
{
#ifdef LOW_LEVEL_KINESIOLOGY
    size_t carryItem;
    struct _WorkBench* selectedWb;
    if(!(carryItem = botCarryItemOrder(bot)))
        //未拿取物品
        selectedWb = selectWorkBench(bot,filterIfNotTargeted,selectorMininumArrivedPurchase);
    else
        //拿取了物品
        selectedWb = selectWorkBench(bot,filterIfSpecifiedItem,selectorMininumArrivedTime);
    if(selectedWb)
    {
        //设置机器人任务
        robot_set_task(bot,selectedWb);
        //设置机器人运动行为
        robot_set_rotate(bot,calculate_angle(bot,selectedWb));
        robot_set_toWardSpeed(bot,calculate_distance(bot,selectedWb));
        //设置机器人购买行为
    }
#endif
}

/**
 * @brief 当前帧决策
*/
void arbitrate_robot_behavior_frame()
{
    for (int i=0;i<ROBOT_NUMBER;i++)
            arbitrate_robot_behavior(&botList[i]);
}

