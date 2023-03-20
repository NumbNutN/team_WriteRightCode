#ifndef FILTER_H
#define FILTER_H

#include "robot.h"
#include "workbench.h"

/**
 * @brief 具体的filter
 *          依据机器人拥有的物品筛选工作台是否需要一个物品
*/
bool filterIfSpecifiedItem(struct _WorkBench* wb,struct _Robot* bot);
/**
 * @brief selector:选择出机器人到达具有最小正时间的工作台
 * @param reset:int 置0时对记录进行重设
 * @birth: Created by LGD on 2023-3-20
*/
bool selectorMininumArrivedTime(struct _WorkBench* wb,struct _Robot* bot,int reset);
/**
 * @brief 返回机器人到达工作台具有最小正时间的工作台
 * @return 0-WORKBENCHNUMBER
 * @birth: Created by LGD on 2023-3-20
*/
bool selectorMininumArrivedPurchase(struct _WorkBench* wb,struct _Robot* bot,int laterOn);

#endif