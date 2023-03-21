#ifndef CFG_H
#define CFG_H

//一些宏
enum _ROBOT_MARCO
{
    RESET = 0,
    SET = 1
};

//定义工作台数量
#define WORKBENCHNUMBER 9

//设置地图
#define MAP1

//设置运动学

#define PI 3.14159265

//低级运动学，较简单的决策算法
#define LOW_LEVEL_KINESIOLOGY

//机器人数量
#define ROBOT_NUMBER 4

//机器人物理参数
#define ROBOT_MAX_LINEAR_VELOCITY_FORWARD 6
#define  ROBOT_MAX_LINEAR_VELOCITY_BACKWARD -2
#define ROBOT_MAX_PALSTANCE PI

#endif