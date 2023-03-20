#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include "cfg.h"

enum _BotStatus
{
    WAITING_NO_CARGO,
    WAITING_WITH_CARGO,
    PERFORMING,
    CRASHED
};

typedef struct _Robot
{
    //所处工作台ID
    size_t localtion_wb_id;
    //携带物品类型
    size_t carry_item;

    //*时间价值系数
    float time_k;
    //*碰撞价值系数
    float crash_k;

    //角速度
    float palstance;
    //线速度X
    float linear_X;
    //线速度Y
    float linear_Y;

    //朝向
    float toWard;

    //坐标X
    float LocationX;
    //坐标Y
    float LocationY;

    //状态
    enum _BotStatus botStatus;
    //目标位置X
    float targetLocationX;
    //目标位置Y
    float targetLocationY;

} Robot;

extern struct _Robot botList[ROBOT_NUMBER];

/**
 * @brief 读取机器人的状态
*/
void robot_read_status(struct _Robot* bot);
/**
 * @brief 返回机器人拿的物品
*/
botCarryItemOrder(struct _Robot* bot);
#endif /*ROBOT_H*/