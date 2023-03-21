#include "cfg.h"
#include "workbench.h"
#include "robot.h"


struct _WorkBench wbList[WORKBENCHNUMBER];

bool workbench_is_blocking(struct _WorkBench* wb)
{
    return wb->wbRemainTime == BLOCKING;
}

bool workbench_no_procedure(struct _WorkBench* wb)
{
    return wb->wbRemainTime < BLOCKING;
}


size_t workbench_needed_item(struct _WorkBench* wb)
{
    return wb->neededItem - wb->ownItem;
}

/**
 * @brief 返回工作台物品准备时间
 * @birth: Created by LGD on 2023-3-20
*/
size_t workbench_ready_time(struct _WorkBench* wb)
{
    return wb->wbRemainTime;
}

/**
 * @brief 读取工作台的状态
*/
void workbench_read_status(struct _WorkBench* wb)
{
    size_t order;
    scanf("%d %f %f %d %d %d\n",
            order,
            &wb->positionX,
            &wb->positionY,
            &wb->wbRemainTime,
            &wb->ownItem,
            &wb->hasOutItem);
}

/**
 * @brief 重设工作台选中状态
 * @birth: Created by LGD on 2023-3-21
*/
void workbench_target_set_status(struct _WorkBench* wb,enum _ROBOT_MARCO value)
{
    wb->beenTargeted = value;
}

/**
 * @brief 初始化工作台信息
 * @birth: Created by LGD on 2023-3-20
*/
void workbench_initialize()
{
#ifdef MAP1
    wbList[0].produceItem = 1u <<1;

    wbList[1].produceItem = 1u <<2;

    wbList[2].produceItem = 1u <<3;

    wbList[3].neededItem = (1u << 1) || (1u << 2);
    wbList[3].produceItem = 1u <<4;

    wbList[4].neededItem = (1u << 1) || (1u << 3);
    wbList[4].produceItem = 1u <<5;

    wbList[5].neededItem = (1u << 2) || (1u << 3);
    wbList[5].produceItem = 1u <<6;

    wbList[6].neededItem = (1u << 4) || (1u <<5) || (1u << 6);
    wbList[6].produceItem = 1u <<7;

    wbList[7].neededItem = (1u << 7);
    
    wbList[8].neededItem = (0x7F << 1);
#endif
}





