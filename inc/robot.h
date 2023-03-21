#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include "cfg.h"
#include "workbench.h"

enum _BotStatus
{
    WAITING_NO_CARGO,       //无货 等待接受任务
    WAITING_WITH_CARGO,     //有货 等待接收任务
    PERFORMING,             //执行任务状态
    CRASHED                 //被撞击
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
    
    //目标工作台
    struct _WorkBench* targetWb;

    //旋转速度
    float rotate;
    //前进速度
    float forward;

} Robot;

extern struct _Robot botList[ROBOT_NUMBER];

/**
 * @brief 读取机器人的状态
*/
void robot_read_status(struct _Robot* bot);
/**
 * @brief 获取机器人搬运的内容
*/
size_t botCarryItemOrder(struct _Robot* bot);
/**
 * @brief 设置机器人任务
*/
void robot_set_task(struct _Robot* bot,struct _WorkBench* tarWb);

/**
 * @brief 设置机器人角速度
 * @birth: Created by LGD on 2023-3-21
*/
void robot_set_rotate(struct _Robot* bot,float angle);
/**
 * @brief 设置机器人线速度
 * @birth: Created by LGD on 2023-3-21
*/
void robot_set_toWardSpeed(struct _Robot* bot,float distance);
#endif /*ROBOT_H*/