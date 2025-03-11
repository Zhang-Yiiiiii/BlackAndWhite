#ifndef CONFIG_H
#define CONFIG_H

#include <QSize>

/************主场景资源配置数据******************/
#define BACKGROUDWIDTH 1500   //背景大小
#define BACKGROUDHEIGHT 800

#define BACKGROUDPATH ":/image/mainScene.jpg"  //背景图片路径

#define MYTITLE "黑白格"  //窗口标题

#define MYICON ":/icon/debug1.png"  //窗口图标

#define SELECTBTNNUMBER 37  //选关按钮数量



/************六边形按钮配置数据******************/
#define HEXAGONPATH ":/icon/hexagon.png"



/************黑白格配置数据******************/
#define GRIDPATH1 ":/icon/white.png"
#define GRIDPATH2 ":/icon/black.png"
#define GRIDSIZE 35


/************游戏场景配置数据******************/
#define GRIDNUMBER 400
#define BOARDWIDTH 20
#define BUGPATH ":/icon/debug%1.png" //虫子路径
#define BOARDPOSX BACKGROUDWIDTH/2 - GRIDSIZE * 10 //棋盘左上角的X
#define BOARDPOSY 50  //棋盘左上角的Y


/************游戏数据配置数据******************/
#define DATAPATH "D:/data.txt"

#endif // CONFIG_H
