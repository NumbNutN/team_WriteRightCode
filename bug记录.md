2023-3-21
selectorMininumArrivedTime找不到有效的工作台并返回null
原因：其中调用了calculate_angle计算角度，而其中使用了abs只适用于整数取绝对值，对弧度制浮点数使用导致未定义结果

2023-3-22
无法和输入有效交互
原因：工作台不只9个，工作台的类型只有9个，接收输入小于判题器输出

2023-3-22
致命错误，可能是从非法的指针中取数
calculate_arrive_time()没有被声明导致返回值默认为整数
导致selectorMininumArrivedPurchase找不到目标

2023-3-22
致命错误，可能是从非法的指针中取数
selectWorkBench()返回nuLL的情况没有特殊处理

2023-3-22
filterIfSpecifiedItem() 判断当前机器人是否拥有当前工作台需要的物品
最后一个或改为了与
因为应当是判断工作台需要的和机器人拥有是否同时成立
return ((wb->neededItem & ~(wb->ownItem)) & bot->carry_item)!=0;

2023-3-23
robot_set_purchase_sell() 当前机器人是否应当有销售行为 基于当前机器人是否在一个工作台附近
0改为-1  因为-1为无工作台 工作台从0开始计数
    size_t carryItem;
    //携带物品
    if(bot->localtion_wb_id != -1)

2023-3-23
size_t botCarryItemOrder(struct _Robot* bot) 返回当前机器人携带的物品
最后一位置0
工作台以 000110表示拥有1、2物品 物品从1开始计数
carry_item = 0为无物品 
    return (bot->carry_item & ~(0x1));