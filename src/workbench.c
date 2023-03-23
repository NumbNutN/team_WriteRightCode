#include "cfg.h"
#include "workbench.h"
#include "robot.h"
#include "io.h"


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
int workbench_ready_time(struct _WorkBench* wb)
{
    if(wb->wbRemainTime!=-1)
        return wb->wbRemainTime;
    else
        return INFINITY;
}

/**
 * @brief 读取工作台的状态
*/
void workbench_read_status(struct _WorkBench* wb)
{
#ifdef READ_FRAME_IN_BUFFER
    readALine();
    size_t type;
    //工作台类型
    type = get_a_interger(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    wb->positionX = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    wb->positionY = get_a_float(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    wb->wbRemainTime = get_a_interger(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    wb->ownItem = get_a_interger(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],' ');
    wb->hasOutItem = get_a_interger(line,buf_cnt);
    buf_cnt = pass_next_char_order(&line[buf_cnt],'\n');
#elif defined READ_FRAME_SCAN_FORMAT
    size_t type;
    scanf("%d %f %f %d %d %d\n",
            &type,
            &wb->positionX,
            &wb->positionY,
            &wb->wbRemainTime,
            &wb->ownItem,
            &wb->hasOutItem);
#endif
    workbench_initialize(wb,type);
}

/**
 * @brief 设置工作台的状态为被机器人选中
 * @birth: Created by LGD on 2023-3-21
*/
void workbench_target_set_status(struct _WorkBench* wb,enum _ROBOT_MARCO value)
{
    wb->beenTargeted = value;
}

/**
 * @brief 初始化工作台信息
 * @birth: Created by LGD on 2023-3-20
 * @update: 工作台的类型不应依下标
*/
void workbench_initialize(struct _WorkBench* wb,size_t type)
{
#ifdef MAP1
    switch(type)
    {
        case 1:
            wb->produceItem = 1u <<1;
        break;
        case 2:
            wb->produceItem = 1u <<2;
        break;
        case 3:
            wb->produceItem = 1u <<3;
        break;
        case 4:
            wb->neededItem = (1u << 1) || (1u << 2);
            wb->produceItem = 1u <<4;
        break;
        case 5:
            wb->neededItem = (1u << 1) || (1u << 3);
            wb->produceItem = 1u <<5;
        break;
        case 6:
            wb->neededItem = (1u << 2) || (1u << 3);
            wb->produceItem = 1u <<6;
        break;
        case 7:
            wb->neededItem = (1u << 4) || (1u <<5) || (1u << 6);
            wb->produceItem = 1u <<7;
        break;
        case 8:
            wb->neededItem = (1u << 7);
        break;
        case 9:
            wb->neededItem = (0x7F << 1);
        break;
    }   
#endif
}





