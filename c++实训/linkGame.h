#pragma once
#include<graphics.h>
#include<vector>

struct Point {
	int x, y;
	bool operator!=(const Point& other) {
		if (this->x == other.x && this->y == other.y)
			return false;
		return true;
	}
};

class linkGame
{
public:
	linkGame(int rows, int cols, int width, int height, int blockSize, int leftBound, int topBound);
	void init();						//初始化
	void play();						//开始游戏
	void biuldMap();					//创建地图
	void clear(Point a, Point b);		//消除方块
	void updateNums();					//更新数字
	int findGcd(int a, int b);						//寻找最大公约数
	void updateWindow();				//更新窗口
	void checkOver();					//检查游戏是否结束
	void click();						//处理用户输入
	void displayOver();					//展示结算画面
	void saveScore();					//保存最高分
	void saveDate();					//实时保存数据
	int getDelay();						//获取延迟

private:
	int rows, cols, width, height, blockSize, leftBound, topBound;
	int minTime;
	int curTime;
	int delay;
	int whetherOver;
	bool whetherUpdate;
	int level;
	IMAGE background;
	IMAGE block;
	IMAGE block_choose;
	std::vector<std::vector<int>>mp;
	std::vector<std::vector<int>>nums;
	std::vector<std::vector<int>>choose;
};

