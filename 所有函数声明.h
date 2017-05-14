#pragma once

/*图形初始化*/
int initwindow();

/*播放BGM*/
int _playmusic(LPSTR music);
int _playsound(LPSTR wav);//播放音效

/*开始选项*/
int start();
int _change_picture(IMAGE* img/*图片指针*/, int x_start, int y_start, int x_end,
	int y_end/*分别是开始的坐标，与结束时的坐标*/, int dir/*图片移动的方向，一个角度值*/);
int _get_mouse_msg(MOUSECLICK* eventarray/*一个结构体数组，每个数组元素存放事件具体的参数，即点击区域的坐标*/, int length/*数组长度*/);
int shezhi();//修改游戏设置;
int paihangbang();//提取排行榜文件，显示;
int rule();//提取规则图片，显示
int zairucundang();//载入存档
int _read_memory(MEMORY* memo);//读取存档
int _display_text(MEMORY* memo, int num,MOUSECLICK*events);//显示与存档对应的文字信息
int _delete_memory(MEMORY*memo, int select_memory,int num);//删除存档							   
int _load_memory(MEMORY*memo);//把存档信息加载到全局变量中

/*难度和地图选择*/
int _map_degree();
int mode1();//战役模式界面
int mode2();//生存模式界面
int load_map(int select_map);//将指定的地图数据加载到地图数组中
int set_speed(int select_degree);	         //设置速度大小
int initdata();											 //游戏数据初始化

/*游戏界面初始化*/
int initgame();

/*屏幕刷新*/
int paint();
int paint_food(int *food,int food_r,int color);//画食物

/*食物判断*/
int _food_judge();
int* _meet_circle(int *food, float x, float y, int food_r, int snake_r);
															//判断x，y处半径为snake_r的圆是否与food数组里的半径为food_r的圆发生碰撞
int _food_create(int * meet,int r);//再生食物，存在meet后面的两个数组元素内
int addsnake();		//蛇长一节
int _half();		//蛇炸一半
int _herb();		//开启ai觉醒模式
int _poison();		//控制毒草的形状和有无

/*死亡判断*/
int _death_judge();
int _meet_line(int circlex, int circley, int r, int x1, int y1, int x2, int y2);//检测一个圆是否与一个直线相交
int _duang(int *p, int circle_x, int circle_y, int r);							//检测圆是否与一个多边形发生碰撞
int wall_check(int circle_x, int circle_y, int r);								//检测一个圆是否与障碍物发生碰撞

/*速度递增*/
int addspeed();



/*关卡判断*/
int _level();

/*清理屏幕*/
int clear();

/*移动*/
int move();
int _up();//向上走
int _down();//向下走
int _left();//向左走
int _right();//向右走

/*暂停*/
int pause();
int _get_name(char*name, int *signal);//得到输入的字符串
int _set_memory(char*name, int *signal);//若*signal为真,建立名为name的存档

/*游戏结束*/
int end();
int end_select();
int setrecord();
int loadpaihang();//加载排行版文件