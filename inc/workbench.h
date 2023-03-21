#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <stdio.h>
#include <stdbool.h>

enum _ItemOrder
{
    ITEM1 = 1,
    ITEM2 = 2,
    ITEM3 = 4,
    ITEM4 = 8,
    ITEM5 = 16,
    ITEM6 = 32,
    ITEM7 = 64
};

enum _WBStatus
{
    NO_PRODUCE = -1,
    BLOCKING = 0
};

typedef struct _WorkBench
{
    //坐标
    float positionX;
    float positionY;
    
    //生产剩余时间
    enum _WBStatus wbRemainTime;

    //目前拥有的物品
    size_t ownItem;

    //已产出
    bool hasOutItem;

    //消耗的物品
    size_t neededItem;
    //生产的物品
    size_t produceItem;

    //选中状态
    bool beenTargeted;

} WorkBench;

extern struct _WorkBench wbList[WORKBENCHNUMBER];
extern size_t workbenchNumber;

/**
 * @brief 初始化工作台信息
 * @birth: Created by LGD on 2023-3-20
*/
void workbench_initialize();
/**
 * @brief 读取工作台的状态
*/
void workbench_read_status(struct _WorkBench* wb);

/**
 * @brief 返回工作台物品准备时间
 * @birth: Created by LGD on 2023-3-20
*/
size_t workbench_ready_time(struct _WorkBench* wb);

/**
 * @brief 重设工作台状态
 * @birth: Created by LGD on 2023-3-21
*/
void workbench_target_set_status(struct _WorkBench* wb,enum _ROBOT_MARCO value);


#endif /*#define WORKBENCH_H*/