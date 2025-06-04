#pragma once
#include"linkGame.h"
#include"User.h"

enum PICTURE {
	Enter = 1,
	begin,
	playgame,
	gameover,
	description,
	Register,
	Login,
	message,
	rank,
	cancel,
	levelchoose
};

class Click
{
public:
	Click();
	void update();							//更新游戏
	void show();							//展示画面
	void click();							//处理点击事件
	void enterPicture(ExMessage& msg);					//进入游戏界面
	void beginPicture(ExMessage& msg);		//开始界面
	void playPicture(ExMessage& msg);		//游戏界面
	void overPicture(ExMessage& msg);		//结束界面
	void levelPicture(ExMessage& msg);		//难度选择界面
	void registerPicture(ExMessage& msg);	//注册页面
	void loginPicture(ExMessage& msg);		//登录界面
	void messagePicture(ExMessage& msg);							//注册和登录失败或成功的信息
	void rankPicture(ExMessage& msg);					//排行榜
	void introPicture(ExMessage& msg);		//教程界面
	void cancelPicture();
	int getDelay();
	

private:
	int leftBound, topBound;
	int cols, rows;
	bool whetherUpdate;
	int delay;
	Point lastchoose;
	enum PICTURE picture = Enter;
	linkGame game;
	User user;
	bool input_key;					//是否有输入
	bool input_acount;
	bool input_key2;
	int messageVal;					//错误信息
	int rankLevel;					//当前展示的排行榜对于的难度
};

