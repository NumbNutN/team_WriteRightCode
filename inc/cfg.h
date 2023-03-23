#ifndef CFG_H
#define CFG_H


enum _ROBOT_MARCO
{
    RESET = 0,
    SET = 1
};


//2023-3-22 定义是否从BUFFER中获取数据(ASCII)
/*******************************************************************************/
/*                这是两种从输入文件获取数据的方式                                */
/*     READ_FRAME_IN_BUFFER将整行数据通过fgets()以ASCII格式读入一个BUFFER进行处理 */
/*     READ_FRAME_SCAN_FORMAT将每行数据以scanf()格式化读取                       */
/*      问题是后者会造成判题器的崩溃，原因我暂时没有能力解释                        */
/*******************************************************************************/

#define READ_FRAME_IN_BUFFER
//#define READ_FRAME_SCAN_FORMAT

//定义工作台数量
#define WORKBENCHNUMBER 50 

//定义机器人旋转弧度计算策略
/*******************************************************************************/
/*                计算机器人朝向指定工作台应该旋转的弧度                           */
/*              显然1是错误的而2更有效，将在下一个版本删除1                        */
/*******************************************************************************/
//#define CALCULATE_ANGLE_STRATEGY_1
#define CALCULATE_ANGLE_STRATEGY_2

//设置地图
#define MAP1

//低级运动学，较简单的决策算法
#define LOW_LEVEL_KINESIOLOGY

//机器人数量
#define ROBOT_NUMBER 4

//物理参数
#define PI 3.14159265
#define ROBOT_MAX_LINEAR_VELOCITY_FORWARD 6         /*机器人同方向最大线速度*/
#define  ROBOT_MAX_LINEAR_VELOCITY_BACKWARD -2      /*机器人反方向最大线速度*/
#define ROBOT_MAX_PALSTANCE PI                      /*机器人旋转最大角速度*/

#endif