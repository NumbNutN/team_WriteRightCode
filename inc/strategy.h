#ifndef STRATEGY_H
#define STRATEGY_H

/**
 * @brief 决策机器人行为
 * @birth: Created by LGD on 2023-3-21
*/
void arbitrate_robot_behavior(struct _Robot* bot);

/**
 * @brief 当前帧决策
*/
void arbitrate_robot_behavior_frame();

/**
 * @brief 计算机器人到达工作台的时间
*/
size_t calculate_arrive_time(struct _Robot* bot,struct _WorkBench* wb);

#endif 