#include "robot.h"

struct _Robot botList[ROBOT_NUMBER];
/**
 * @brief 读取机器人的状态
*/
void robot_read_status(struct _Robot* bot)
{
    size_t carry_item;
    scanf("%d %d %f %f %f %f %f %f %f %f\n",
            bot->localtion_wb_id,
            carry_item,
            bot->time_k,
            bot->crash_k,
            bot->palstance,
            bot->linear_X,
            bot->linear_Y,
            bot->toWard,
            bot->LocationX,
            bot->LocationY);

    bot->carry_item = 1u << carry_item;
}

botCarryItemOrder(struct _Robot* bot)
{
    return bot->carry_item;
}