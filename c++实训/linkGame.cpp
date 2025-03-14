#include "linkGame.h"
#include<fstream>
#include<random>
#include<sysinfoapi.h>
#include<iostream>

std::random_device rd;
std::mt19937 gen(rd());
const int LEVEL[5] = { 50, 100, 200, 350, 600 };
const int DELAY = 30;


linkGame::linkGame(int rows, int cols, int width, int height, int blockSize, int leftBound, int topBound)
{
	this->rows = rows;
	this->cols = cols;
	this->width = width;
	this->height = height;
	this->blockSize = blockSize;
	this->leftBound = leftBound;
	this->topBound = topBound;
	delay = DELAY;
	whetherUpdate = false;
	std::ifstream file("maxscore.txt");
	if (!file.is_open()) {
		minTime = 0;
	}
	else {
		file >> minTime;
	}
	file.close();
	
	mp.resize(rows, std::vector<int>(cols));
	nums.resize(rows, std::vector<int>(cols));
	choose.resize(rows, std::vector<int>(cols));
}

void linkGame::init()
{
	level = 1;
	whetherOver = 0;
	curTime = 0;
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			mp[i][j] = 0;
			nums[i][j] = 0;
			choose[i][j] = 0;
		}
	biuldMap();

	initgraph(width, height, 1);
	loadimage(&background, "res/back.png");
	loadimage(&block, "res/block.png");
	loadimage(&block_choose, "res/block_choose.png");
}

void linkGame::play()
{
	init();
	
	//渲染	
	
	int timer = 0;
	while (true) {
		click();
		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			whetherUpdate = true;
		}
		if (whetherUpdate) {
			whetherUpdate = false;
			updateWindow();
			checkOver();
			saveDate();
			if (whetherOver) {
				saveScore();
				displayOver();
			}
		}
	}
}

void linkGame::biuldMap()
{
	std::uniform_int_distribution<> dis(2, LEVEL[level - 1]);
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			nums[i][j] = dis(gen);
		}
}

void linkGame::clear(Point a, Point b)
{	
	int num1 = nums[a.x][a.y];
	int num2 = nums[b.x][b.y];
	int t = findGcd(num1, num2);
	if (t != 1) {
		num1 /= t;
		num2 /= t;
		if (num1 == 1) {
			nums[a.x][a.y] = 1;
			mp[a.x][a.y] = 1;
		}
		else {
			nums[a.x][a.y] = num1;
		}
		if (num2 == 1) {
			nums[b.x][b.y] = 1;
			mp[b.x][b.y] = 1;
		}
		else {
			nums[b.x][b.y] = num2;
		}
	}
}

void linkGame::updateNums()
{
	BeginBatchDraw();

	setcolor(RGB(0, 0, 0));				//设置字体颜色
	LOGFONT	f;							//字体变量
	gettextstyle(&f);					//获取字体类型
	f.lfHeight = 20;
	f.lfWidth = 12;
	f.lfQuality = ANTIALIASED_QUALITY;	//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black")); //设置字体类型
	settextstyle(&f);

	setbkmode(TRANSPARENT);				//透明背景

	char numText[30];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (nums[i][j] == 1)continue;
			int x = j * blockSize + leftBound;
			int y = i * blockSize + topBound;
			sprintf_s(numText, sizeof(numText), "% d", nums[i][j]);
			int len = strlen(numText);
			if(len == 2)
				outtextxy(x + 7, y + 12, numText);
			else if(len == 3)
				outtextxy(x + 3, y + 12, numText);
			else 
				outtextxy(x , y + 12, numText);
		}
	}

	gettextstyle(&f);					
	f.lfHeight = 50;
	f.lfWidth = 20;
	settextstyle(&f);
	sprintf_s(numText, sizeof(numText), "% d", curTime);
	outtextxy(778, 690, numText);
	EndBatchDraw();
}

int linkGame::findGcd(int a, int b)
{
	return b == 0 ? a : findGcd(b , a % b);
}

void linkGame::updateWindow()
{
	BeginBatchDraw();
	putimage(0, 0, &background);

	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			if (mp[i][j])continue;
			else {
				int x = j * blockSize + leftBound;
				int y = i * blockSize + topBound;
				if (choose[i][j] == 1)
					putimage(x, y, &block_choose);
				else putimage(x, y, &block);
			}
		}
	updateNums();
	EndBatchDraw();
}


void linkGame::checkOver()
{
}

void linkGame::click()
{
	

	static bool whetherChoose = false;
	static Point lastChoose;
	ExMessage msg;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {	//鼠标左键
			if (msg.x > leftBound && msg.x < leftBound + cols * blockSize &&
				msg.y > topBound && msg.y < topBound + rows * blockSize) {
				int col = (msg.x - leftBound) / blockSize;
				int row = (msg.y - topBound) / blockSize;
				if (whetherChoose) {
					Point cur = { row, col };
					if (cur != lastChoose) {
						whetherChoose = false;
						choose[lastChoose.x][lastChoose.y] = 0;
						clear(cur, lastChoose);
					}
				}
				else {
					lastChoose = { row, col };
					choose[row][col] = 1;
					whetherChoose = true;
				}
				whetherUpdate = true;
			}
			
		}
	}
}

void linkGame::displayOver()
{
}

void linkGame::saveScore()
{
	if (curTime < minTime) {
		std::ofstream file("maxscore.txt");
		if (file.is_open()) {
			file << minTime;	
		}
		file.close();
	}
}

void linkGame::saveDate()
{
}

int linkGame::getDelay()
{
	static unsigned long long lasTime = 0;
	unsigned long long current = GetTickCount();
	if (lasTime == 0) {
		lasTime = current;
		return 0;
	}
	else {
		int res = current - lasTime;
		lasTime = current;
		curTime += res;
		return res;
	}
}
