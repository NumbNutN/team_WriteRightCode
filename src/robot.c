#include "robot.h"

struct _Robot botList[ROBOT_NUMBER];
/**
 * @brief 读取机器人的状态
*/
void robot_read_status(struct _Robot* bot)
{
    size_t carry_item;
    scanf("%d %d %f %f %f %f %f %f %f %f\n",
            &bot->localtion_wb_id,
            &carry_item,
            &bot->time_k,
            &bot->crash_k,
            &bot->palstance,
            &bot->linear_X,
            &bot->linear_Y,
            &bot->toWard,
            &bot->LocationX,
            &bot->LocationY);

    bot->carry_item = 1u << carry_item;
}

/**
 * @brief 获取机器人搬运的内容
*/
size_t botCarryItemOrder(struct _Robot* bot)
{
    return bot->carry_item;
}
/**
 * @brief 设置机器人任务
*/
void robot_set_task(struct _Robot* bot,struct _WorkBench* tarWb)
{
    //目标状态更新
    workbench_target_set_status(tarWb,SET);
    //机器人目标
    bot->targetWb = tarWb;
    //机器人状态
    bot->botStatus = PERFORMING;
}

/**
 * @brief 设置机器人角速度
 * @birth: Created by LGD on 2023-3-21
*/
void robot_set_rotate(struct _Robot* bot,float angle)
{
#ifdef LOW_LEVEL_KINESIOLOGY
    if(angle > 0)
        bot->rotate = angle > ROBOT_MAX_PALSTANCE? ROBOT_MAX_PALSTANCE : angle;
    else
        bot->rotate = angle < -ROBOT_MAX_PALSTANCE? -ROBOT_MAX_PALSTANCE : -angle;
#endif
}

/**
 * @brief 设置机器人线速度
 * @birth: Created by LGD on 2023-3-21
*/
void robot_set_toWardSpeed(struct _Robot* bot,float distance)
{
#ifdef LOW_LEVEL_KINESIOLOGY
    bot->forward = distance > ROBOT_MAX_LINEAR_VELOCITY_FORWARD ? ROBOT_MAX_LINEAR_VELOCITY_FORWARD : distance;
#endif    
}