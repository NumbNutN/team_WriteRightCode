#include "myFilter.h"
#include "strategy.h"

/************************************************************************************************************/
/* 过滤器和选择器都是函数，可以作为函数指针传递到方法                                                           */
/*          selectWorkBench()中选择出唯一的工作台                                                           */
/*从某种意义山讲，过滤器和选择器都是对工作台列表的筛选，只不过一个筛选出的数量不定，一个只确保能筛选一个最XX的工作台*/
/*您可以简单理解为两级过滤系统，两者皆启用时，过滤器先于选择器生效                                              */
/***********************************************************************************************************/


/*********************************************************/
/*                       过滤器                           */
/* 从当前工作台列表中依据指定条件筛选之用，只会返回true和false*/
/*********************************************************/
/**
 * @brief filter:过滤出需要当前机器人手持物品的工作台    
*/
bool filterIfSpecifiedItem(struct _WorkBench* wb,struct _Robot* bot)
{
    return ((wb->neededItem & ~(wb->ownItem)) & bot->carry_item)!=0;
}

/**
 * @brief filter:过滤出当前未被选中的工作台
*/
bool filterIfNotTargeted(struct _WorkBench* wb,struct _Robot* bot)
{
    return !wb->beenTargeted;
}


/*****************************************************************/
/*                             选择器                             */
/*  从当前工作台列表中选择出唯一的符合条件的工作台，只会返回true和false*/
/******************************************************************/
/**
 * @brief selector:选择出机器人到达具有最小正时间的工作台
 * @param reset:int 置0时对记录进行重设
 * @birth: Created by LGD on 2023-3-20
*/
bool selectorMininumArrivedTime(struct _WorkBench* wb,struct _Robot* bot,int reset)
{
    static int smallestTimeDifference = INFINITY;
    int newTimeDifference;

    if(!reset)
        smallestTimeDifference = INFINITY;

    newTimeDifference = calculate_arrive_time(bot,wb);
        smallestTimeDifference = \
                        (newTimeDifference > 0) && \
                        (newTimeDifference < smallestTimeDifference)? \
                        newTimeDifference : smallestTimeDifference;
    if(smallestTimeDifference == newTimeDifference)
        return true;
    
    return false;
}
/**
 * @brief selector:选择出机器人到达工作台且工作台在此之前生产好物品具有最小时间差的工作台
 * @param reset:int 置0时对记录进行重设
 * @birth: Created by LGD on 2023-3-20
*/
bool selectorMininumArrivedPurchase(struct _WorkBench* wb,struct _Robot* bot,int reset)
{
    static int smallestTimeDifference = INFINITY;
    int newTimeDifference;

    if(!reset)
        smallestTimeDifference = INFINITY;

    newTimeDifference = calculate_arrive_time(bot,wb) - workbench_ready_time(wb);
        smallestTimeDifference = \
                        (newTimeDifference > 0) && \
                        (newTimeDifference < smallestTimeDifference)? \
                        newTimeDifference : smallestTimeDifference;
    if(smallestTimeDifference == newTimeDifference)
        return true;
    
    return false;
}


