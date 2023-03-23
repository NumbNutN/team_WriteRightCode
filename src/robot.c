#include "robot.h"
#include "io.h"

struct _Robot botList[ROBOT_NUMBER];

/**
 * @brief 机器人初始化
*/
void botInit()
{
    for(int i=0;i<ROBOT_NUMBER;i++)
        botList[i].botID = i;
}
/**
 * @brief 读取机器人的状态
*/
void robot_read_status(struct _Robot* bot)
{
#ifdef READ_FRAME_IN_BUFFER
    readALine();
    size_t carry_item;
    bot->localtion_wb_id = get_a_interger(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    carry_item = get_a_interger(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->time_k = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->crash_k = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->palstance = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->linear_X = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->linear_Y = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->toWard = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->LocationX = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    bot->LocationY = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],'\n');
#elif defined READ_FRAME_SCAN_FORMAT
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

#endif
    bot->carry_item = 1u << carry_item;
}

/**
 * @brief 获取机器人搬运的内容
*/
size_t botCarryItemOrder(struct _Robot* bot)
{
    return (bot->carry_item & ~(0x1));
}
/**
 * @brief 设置机器人任务
 * @update: 2023-3-23 当前机器人状态为WAITING_NO_CARGO 或 WAITING_WITH_CARGO时才 设置其任务
*/
void robot_set_task(struct _Robot* bot,struct _WorkBench* tarWb)
{
    if(bot->botStatus == WAITING_NO_CARGO || bot->botStatus == WAITING_WITH_CARGO)
    {
        //目标状态更新
        workbench_target_set_status(tarWb,SET);
        //机器人目标
        bot->targetWb = tarWb;
        //机器人状态
        bot->botStatus = PERFORMING;
    }
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

/**
 * @brief 获取机器人所处的工作台
*/

/**
 * @brief 设置机器人购买/消费行为
 * @birth: Created by LGD on 2023-3-22
*/
void robot_set_purchase_sell(struct _Robot* bot)
{
    size_t carryItem;
    //携带物品
    if(bot->localtion_wb_id != -1)
    {
        if(!(carryItem = botCarryItemOrder(bot)))
            printf("%s %d\n","buy",bot->botID);
        else
            printf("%s %d\n","sell",bot->botID);
    }
}