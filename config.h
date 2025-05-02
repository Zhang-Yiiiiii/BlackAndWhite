#ifndef CONFIG_H
#define CONFIG_H

/************主场景资源配置数据******************/
#define BACKGROUDWIDTH 1500   //背景宽
#define BACKGROUDHEIGHT 800   //背景高
#define BACKGROUDPATH ":/image/mainScene.jpg"  //背景图片
#define MYTITLE "非黑即白"  //窗口标题
#define MYICON ":/icon/debug1.png"  //窗口图标
#define SELECTBTNNUMBER 47  //选关按钮数量
#define ANTGAMENUMBER 37    //兰顿蚂蚁的关卡数
#define LIGHTGAMEBUMBER 10  //熄灯游戏的关卡数
#define RULEPATH "D:/QtProjects/BlackAndWhiteBlock/rule.txt" //说明文件的路径

/************六边形按钮配置数据******************/
#define HEXAGONPATH ":/icon/hexagon.png"  //六边形图片

/************黑白格子配置数据******************/
#define GRIDPATH1 ":/icon/white.png"  //白色格子
#define GRIDPATH2 ":/icon/black.png"  //黑色格子
#define GRIDSIZE 35  //格子的边长
#define TIPPATH ":/icon/click.png"  //提示点击图片

/************游戏场景配置数据******************/
#define GRIDNUMBER 400  //格子总数
#define BOARDSIDELENGTH 20  //棋盘边长
#define BUGPATH ":/icon/debug%1.png" //虫子路径
#define BOARDPOSX BACKGROUDWIDTH/2 - GRIDSIZE * 10 //棋盘左上角的X
#define BOARDPOSY 50  //棋盘左上角的Y

/************游戏数据配置数据******************/
#define ANTDATAPATH  "D:/QtProjects/BlackOrWhite/data.txt" //ant游戏数据
#define LIGHTDATAPATH  "D:/QtProjects/BlackOrWhite/lightData.txt" //light游戏数据
/************用户管理配置数据******************/
#define USERDATAPATH  "D:/QtProjects/BlackOrWhite/userData.txt" //用户数据

/************登录界面配置数据******************/
#define USERACCOUNTICON ":/icon/userAccountIcon.png"      //用户账户图标
#define PASSWORDICON ":/icon/passwordIcon.png"            //用户密码图标
#define LOGINROBOT ":/image/loginRobot.jpg"               //机器人图片
#define LOGINBACKGROUND ":/image/loginBackground.jpg"     //登录背景图
#define LOGINWIHTEBACKGROUND ":image/loginWhitePic.png"   //登录白色背景图

#endif // CONFIG_H
