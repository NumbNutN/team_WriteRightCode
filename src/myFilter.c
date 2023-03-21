#include "myFilter.h"

/****************************************************/
/*                       过滤器                      */
/****************************************************/
/**
 * @brief filter:过滤出需要当前机器人手持物品的工作台    
*/
bool filterIfSpecifiedItem(struct _WorkBench* wb,struct _Robot* bot)
{
    return ((wb->neededItem & ~(wb->ownItem)) | bot->carry_item)!=0;
}



/****************************************************/
/*                       选择器                      */
/****************************************************/
/**
 * @brief selector:选择出机器人到达具有最小正时间的工作台
 * @param reset:int 置0时对记录进行重设
 * @birth: Created by LGD on 2023-3-20
*/
bool selectorMininumArrivedTime(struct _WorkBench* wb,struct _Robot* bot,int reset)
{
    static int smallestTimeDifference = 99999;
    int newTimeDifference;

    if(!reset)
        smallestTimeDifference = 99999;

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
    static int smallestTimeDifference = 99999;
    int newTimeDifference;

    if(!reset)
        smallestTimeDifference = 99999;

    newTimeDifference = calculate_arrive_time(bot,wb) - workbench_ready_time(wb);
        smallestTimeDifference = \
                        (newTimeDifference > 0) && \
                        (newTimeDifference < smallestTimeDifference)? \
                        newTimeDifference : smallestTimeDifference;
    if(smallestTimeDifference == newTimeDifference)
        return true;
    
    return false;
}


