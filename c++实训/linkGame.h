#pragma once
#include<graphics.h>
#include<vector>
#include<fstream>
#include<random>
#include<queue>
#include<algorithm>
#include<iostream>
#include"tool.h"
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

struct Point {
	int x, y;
	bool operator!=(const Point& other) {
		if (this->x == other.x && this->y == other.y)
			return false;
		return true;
	}
	Point& operator=(const Point& other) {
		if (this == &other)
			return *this;
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
};

class linkGame
{
public:
	linkGame();
	void init();						//新游戏初始化
	void init2();						//继续游戏
	bool play();						//开始游戏
	void biuldMap();					//初始化地图
	void clear(Point a, Point b);		//消除数字
	void updateNums();					//更新数字
	int findGcd(int a, int b);			//寻找最大公约数
	void updateWindow();				//更新窗口
	bool checkWin();					//判断游戏是否胜利
	void displayLevel();				//展示难度选择界面
	void displayOver();					//展示游戏结束界面
	void displayEnter();				//展示进入界面
	void displayRegister();				//展示注册界面
	void displayLogin();				//展示登录界面
	void Descrition();					//展示教程界面
	void showCancel();					//注销界面
	void saveScore();					//保存记录
	void saveDate();					//保存数据
	bool whetcherConnect(Point a, Point b);				//判断两点是否可连接，记录回溯
	bool whetcherConnect2(Point a, Point b);				//判断两点是否可连接，不记录回溯
	void updateShowLines( Point a, Point b);
	void showLines();					//展示连接线条
	void getHint();						//获取提示
	void showBegin();					//展示开始界面
	int checkLose();					//判断游戏是否结束
	void Message(int val);				//展示注册或登录成功或失败的信息
	void showRank(int level);			//排行榜界面
	void getName(char s[12]);		   //获取用户名

	int level;
	unsigned long long curTime;
	bool see;								//密码可见
	bool see2;
	bool musicOpen;
	std::vector<std::vector<int>>mp;		
	std::vector<std::vector<int>>nums;
	std::vector<std::vector<int>>lines;
	std::vector<std::vector<int>>choose;
	std::vector<std::vector<Point>>pre;		//前驱节点
	std::vector<std::vector<int>>dir;		//记录方向

private:		

	int MAX;
	int rows, cols;
	int leftBound, topBound;
	int chance;
	unsigned long long minTime;
	int whetherOver;
	char name[12];
	std::vector<std::pair<int, std::string>>Record;
	
	IMAGE returnBotton;
	IMAGE beginImage;
	IMAGE levelchoose;
	IMAGE beginBotton, beginBotton_choose;
	IMAGE continueBotton, continueBotton_choose;
	IMAGE background;
	IMAGE block;
	IMAGE block_choose;
	IMAGE overLose;
	IMAGE overWin;
	IMAGE line[6];
	IMAGE hint;
	IMAGE noConnect;
	IMAGE intro;
	IMAGE quit;
	IMAGE again;
	IMAGE Register;
	IMAGE Login;
	IMAGE registerBotton;
	IMAGE loginBotton;
	IMAGE keyWrong;
	IMAGE noAcount;
	IMAGE registerSuccess;
	IMAGE keyTypeWrong;
	IMAGE acountTypeWrong;
	IMAGE keyUnmatch;
	IMAGE canSee;
	IMAGE notSee;
	IMAGE acountExist;
	IMAGE logOut;
	IMAGE rank;
	IMAGE rankBotton;
	IMAGE cancel; 
	IMAGE cancelPicture;
	IMAGE cancelSuccess;
	IMAGE teach;
};


