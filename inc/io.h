#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

extern char line[1024];
extern size_t buf_cnt;
extern size_t order;
/**
 * @brief 从当前下标位置提出整数
*/
int get_a_interger(char* str,int i);
/**
 * @brief 每一行输入
*/
void readALine();

/**
 * @brief 从当前下标提出浮点数
*/
float get_a_float(char* str,int i);
#endif 