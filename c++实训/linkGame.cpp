#include "linkGame.h"

const int prime[] = { 2, 2 ,2 ,2, 2, 2, 3 ,3, 3, 3, 5, 5, 5, 7, 11, 13, 17, 19, 23, 29 };
const int MAXS[4] = { 50, 100, 200, 350 };
const int row[4] = { 4, 6 , 8, 10 }, col[4] = { 4, 6, 8, 10 };
const int width = 800, height = 950, blockSize = 55, LeftBound[4] = { 174,135,99,25 }, TopBound[4] = { 304,284,252,119 };

//贴图坐标
const int DELAY = 30;
const int music_x = 0, music_y = 0;
const int time_x = 625, time_y = 175;
const int over_x = 100, over_y = 330;
const int beginBotton_x = 300, beginBotton_y = 395;
const int continue_x = 300, continue_y = 493;
const int logout_x = 300, logout_y = 591;
const int quit_x = 300, quit_y = 689;
const int rank_x = 300, rank_y = 787;
const int intro_x = 300, intro_y = 885;
const int noConnect_x = 100, noConnect_y = 330;
const int hint_x = 590, hint_y = 440;
const int return_x = 590, return_y = 530;
const int return_x2 = 266, return_y2 = 613;
const int levelup_x = 483, levelup_y = 394;
const int leveldown_x = 246, leveldown_y = 392;
const int input_x = 125, input_y = 190;
const int level_x = 367, level_y = 370;
const int again_x = 300, again_y = 630;
const int register_x = 300, register_y = 556;
const int login_x = 300, login_y = 425;
const int key_x = 313, key_y = 441;
const int acount_x = 313, acount_y = 381;
const int key2_x = 313, key2_y = 501;
const int dx[4] = { 0,0,1,-1 };
const int dy[4] = { 1,-1,0,0 };

std::random_device rd;
std::mt19937 gen(rd());

linkGame::linkGame()
{
	music = true;
	whetherOver = 0;
	level = 1;
	curTime = 0;
	see = 0;
	see2 = 0;
	char record[20];
	sprintf_s(record, sizeof(record), "maxscore%d.txt", level);
	std::ifstream file(record);
	if (!file.is_open()) {
		minTime = 0;
	}
	else {
		file >> minTime;
	}
	file.close();
	initgraph(width, height, 1);

	loadimage(&background, "res/back.png");
	loadimage(&block, "res/block.png");
	loadimage(&block_choose, "res/block_choose.png");
	loadimage(&overLose, "res/overLose.png");
	loadimage(&overWin, "res/overWin.png");
	loadimage(&line[0], "res/line1.png");
	loadimage(&line[1], "res/line2.png");
	loadimage(&line[2], "res/line3.png");
	loadimage(&line[3], "res/line4.png");
	loadimage(&line[4], "res/line5.png");
	loadimage(&line[5], "res/line6.png");
	loadimage(&hint, "res/hint.png");
	loadimage(&noConnect, "res/noConnect.png");
	loadimage(&levelchoose, "res/levelchoose.png");
	loadimage(&beginImage, "res/beginImage.png");
	loadimage(&beginBotton, "res/beginBotton.png");
	loadimage(&beginBotton_choose, "res/beginBotton_choose.png");
	loadimage(&returnBotton, "res/return.png");
	loadimage(&continueBotton, "res/continue.png");
	loadimage(&continueBotton_choose, "res/continue_choose.png");
	loadimage(&intro, "res/intro.png");
	loadimage(&quit, "res/quit.png");
	loadimage(&again, "res/again.png");
	loadimage(&Register, "res/Register.png");
	loadimage(&Login, "res/Login.png");
	loadimage(&registerBotton, "res/registerBotton.png");
	loadimage(&loginBotton, "res/loginBotton.png");
	loadimage(&keyWrong, "res/keyWrong.png");
	loadimage(&noAcount, "res/noAcount.png");
	loadimage(&registerSuccess, "res/registerSuccess.png");
	loadimage(&keyTypeWrong, "res/keyTypeWrong.png");
	loadimage(&acountTypeWrong, "res/acountTypeWrong.png");
	loadimage(&keyUnmatch, "res/keyUnmatch.png");
	loadimage(&canSee, "res/canSee.png");
	loadimage(&notSee, "res/notSee.png");
	loadimage(&acountExist, "res/acountExist.png");
	loadimage(&logOut, "res/logout.png");
	loadimage(&rank, "res/rank.png");
	loadimage(&rankBotton, "res/rankBotton.png");
	//loadimage(&musicBotton, "res/music.png");
}

void linkGame::init()
{
	curTime = 0;
	whetherOver = 0;
	curTime = 0;
	rows = row[level - 1];
	cols = col[level - 1];
	MAX = MAXS[level - 1];
	leftBound = LeftBound[level - 1];
	topBound = TopBound[level - 1];
	mp.clear();
	lines.clear();
	nums.clear();
	choose.clear();
	pre.clear();
	dir.clear();

	mp.resize(rows + 2, std::vector<int>(cols + 2));
	lines.resize(rows + 2, std::vector<int>(cols + 2));
	nums.resize(rows, std::vector<int>(cols));
	choose.resize(rows, std::vector<int>(cols));
	pre.resize(rows + 2, std::vector<Point>(cols + 2));
	dir.resize(rows + 2, std::vector<int>(cols + 2));
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			mp[i + 1][j + 1] = 1;
			nums[i][j] = 1;
			choose[i][j] = 0;
		}
	biuldMap();
	
}
void linkGame::init2()
{
	whetherOver = 0;
	std::ifstream file("data.txt");
	if (file.is_open()) {
		file >> level;
		rows = row[level - 1];
		cols = col[level - 1];
		MAX = MAXS[level - 1];
		leftBound = LeftBound[level - 1];
		topBound = TopBound[level - 1];
		mp.clear();
		lines.clear();
		nums.clear();
		choose.clear();
		pre.clear();
		dir.clear();

		mp.resize(rows + 2, std::vector<int>(cols + 2));
		lines.resize(rows + 2, std::vector<int>(cols + 2));
		nums.resize(rows, std::vector<int>(cols));
		choose.resize(rows, std::vector<int>(cols));
		pre.resize(rows + 2, std::vector<Point>(cols + 2));
		dir.resize(rows + 2, std::vector<int>(cols + 2));
		for (int i = 0; i < rows + 2; i++) {
			for (int j = 0; j < cols + 2; j++) {
				file >> mp[i][j];
			}
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				file >> nums[i][j];
			}
		}
		file >> curTime;
		file.close();
	}

}

bool linkGame::play()
{

	updateWindow();
	if (whetherOver) {
		//游戏结束
		if (whetherOver == 1) {
			saveScore();
		}
		return false;
	}
	return true;
}

void linkGame::biuldMap()
{
	std::uniform_int_distribution<> dis(0, 19), axis(0, rows - 1);
	int last = 0;
	for (int i = 0; i < rows ; i++){
		for (int j = 0; j < cols; j++) {
			if (last) {
				nums[i][j] = last;
				last = 0;
			}
			else {
				last = prime[dis(gen)];
				nums[i][j] = last;
			}
		}
	}

	for (int i = 0; i < 100; i++) {
		int x1 = axis(gen), y1 = axis(gen);
		int x2 = axis(gen), y2 = axis(gen);
		std::swap(nums[x1][y1], nums[x2][y2]);
	}

	for (int i = 0; i < 1000; i++) {
		int x1 = axis(gen), y1 = axis(gen);
		int x2 = axis(gen), y2 = axis(gen);
		while(x1 == x2 && y1 == y2)
			x2 = axis(gen), y2 = axis(gen);
		int p = prime[dis(gen)];
		if (nums[x1][y1] * p > MAX || nums[x2][y2] * p > MAX) {
			continue;
		}
		nums[x1][y1] *= p;
		nums[x2][y2] *= p;
	}
	saveDate();
}
void linkGame::clear(Point a, Point b)
{	
	if (!whetcherConnect(a, b))
		return;
	//找最大公约数
	int num1 = nums[a.x][a.y];
	int num2 = nums[b.x][b.y];
	int t = findGcd(num1, num2);
	if (t != 1) {
		num1 /= t;
		num2 /= t;
		if (num1 == 1) {
			nums[a.x][a.y] = 1;
			mp[a.x + 1][a.y + 1] = 0;
		}
		else {
			nums[a.x][a.y] = num1;
		}
		if (num2 == 1) {
			nums[b.x][b.y] = 1;
			mp[b.x + 1][b.y + 1] = 0;
		}
		else {
			nums[b.x][b.y] = num2;
		}
		updateShowLines(a, b);
	}
	
	if (checkWin()) {
		whetherOver = 1;
		return;
	}
	int status = checkLose();
	if (status == 2) {
		whetherOver = 2;
		return;
	}
	if (status == 1) {
		putimage(noConnect_x, noConnect_y, &noConnect);
		system("pause");
	}
	while (status == 1) {
		//无可连接点
		std::uniform_int_distribution<> axis(0, rows - 1);
		for (int i = 0; i < 100; i++) {
			int x1 = axis(gen), y1 = axis(gen);
			int x2 = axis(gen), y2 = axis(gen);
			if (nums[x1][y1] == 1 || nums[x2][y2] == 1)
				continue;
			std::swap(nums[x1][y1], nums[x2][y2]);
		}
		status = checkLose();
	}
	saveDate();
}

void linkGame::updateNums()
{
	BeginBatchDraw();

	setcolor(RGB(0, 0, 0));				//设置字体颜色
	LOGFONT	f;							//字体变量
	gettextstyle(&f);					//获取
	f.lfHeight = 20;
	f.lfWidth = 12;
	f.lfQuality = ANTIALIASED_QUALITY;	//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("微软雅黑")); //设置字体
	settextstyle(&f);

	setbkmode(TRANSPARENT);				//透明背景

	//展示数字
	char numText[30];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (nums[i][j] == 1)continue;
			int x = j * blockSize + leftBound;
			int y = i * blockSize + topBound;
			sprintf_s(numText, sizeof(numText), "% d", nums[i][j]);
			int len = strlen(numText);
			if(len == 2)
				outtextxy(x + 12, y + 17, numText);
			else if(len == 3)
				outtextxy(x + 8, y + 17, numText);
			else 
				outtextxy(x + 3, y + 17, numText);
		}
	}

	//展示时间
	gettextstyle(&f);					
	f.lfHeight = 50;
	f.lfWidth = 20;
	settextstyle(&f);
	sprintf_s(numText, sizeof(numText), "%.3lf", (double)curTime / 1000);
	outtextxy(time_x, time_y, numText);
	EndBatchDraw();
}

int linkGame::findGcd(int a, int b)
{
	while (b != 0) {
		int t = a;
		a = b;
		b = t % b;
	}
	return a;
}

void linkGame::updateWindow()
{
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(hint_x, hint_y, &hint);
	putimage(return_x, return_y, &returnBotton);
	//方块是否被选中
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			if (mp[i + 1][j + 1] == 0)continue;
			else {
				int x = j * blockSize + leftBound;
				int y = i * blockSize + topBound;
				if (choose[i][j] == 1)
					putimage(x, y, &block_choose);
				else putimage(x, y, &block);
			}
		}
	showLines();
	updateNums();
	
	EndBatchDraw();
}


bool linkGame::checkWin()
{

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (mp[i + 1][j + 1] == 1) {
				return false;;
			}
		}
	}
	return true;
}

void linkGame::displayLevel()
{
	BeginBatchDraw();

	putimage(0, 0, &levelchoose);
	setcolor(RGB(0, 0, 0));				//设置字体颜色
	LOGFONT	f;							//字体变量
	gettextstyle(&f);					//获取
	f.lfHeight = 80;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;	//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("微软雅黑")); //设置字体
	settextstyle(&f);
	setbkmode(TRANSPARENT);				//透明背景
	
	char numText[30]{};
	sprintf_s(numText, sizeof(numText), "%d", level);
	outtextxy(level_x, level_y, numText);

	EndBatchDraw();
}


void linkGame::displayOver()
{
	BeginBatchDraw();

	if (whetherOver == 1) 
	{
		putimage(over_x, over_y, &overWin);
	}
	else if (whetherOver == 2) 
	{
		putimage(over_x, over_y, &overLose);
	}
	putimage(again_x, again_y, &again);
	putimage(quit_x, quit_y, &quit);

	EndBatchDraw();
}

void linkGame::displayEnter()
{
	BeginBatchDraw();
	putimage(0, 0, &beginImage);
	putimage(register_x, register_y, &registerBotton);
	putimage(login_x, login_y, &loginBotton);
	putimage(quit_x, quit_y, &quit);
	EndBatchDraw();
}

void linkGame::displayRegister()
{
	putimage(input_x, input_y, &Register);
	if (see) {
		putimagePNG(key_x + 250, key_y, &canSee);
	}
	else {
		putimagePNG(key_x + 250, key_y, &notSee);
	}
	if (see2) {
		putimagePNG(key2_x + 250, key2_y, &canSee);
	}
	else {
		putimagePNG(key2_x + 250, key2_y, &notSee);
	}
}

void linkGame::displayLogin()
{
	putimage(input_x, input_y, &Login);
	if (see) {
		putimagePNG(key_x + 250, key_y, &canSee);
	}
	else {
		putimagePNG(key_x + 250, key_y, &notSee);
	}

}

void linkGame::Descrition()
{
	BeginBatchDraw();

	

	EndBatchDraw();
}

void linkGame::saveScore()
{
	char record[20];
	sprintf_s(record, sizeof(record), "%smaxscore%d.txt", name, level);
	if (curTime < minTime || minTime == 0) {
		
		std::ofstream file(record);
		if (file.is_open()) {
			file << curTime;	
		}
		file.close();
	}
}

void linkGame::saveDate()
{
	std::ofstream file("data.txt");
	if (file.is_open()) {
		file << level << '\n';
		for (int i = 0; i < rows + 2; i++) {
			for (int j = 0; j < cols + 2; j++) {
				file << mp[i][j] << ' ';
			}
			file << '\n';
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				file << nums[i][j] << ' ';
			}
			file << '\n';
		}
		file << curTime;
		file.close();
	}
}


bool linkGame::whetcherConnect(Point a, Point b)
{
	struct Node {
		int x, y;
		int direct;
		int turnCount;
	};
	bool flag = false;
	//判断两点是否可连接 
	std::vector<std::vector<int>>min_turns(rows + 2, std::vector<int>(cols + 2, 4));
	std::queue<Node>q;
	q.push({ a.x + 1, a.y + 1, -1, 0 });
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			if (nx == b.x + 1 && ny == b.y + 1 && cur.turnCount + (i != cur.direct) <= 2){
				pre[nx][ny] = { cur.x, cur.y };
				dir[nx][ny] = i;
				flag = true;
				break;
			}
			if (nx >= 0 && nx < rows + 2 && ny >= 0 && ny < cols + 2 && !mp[nx][ny]) {
				int new_turns = cur.turnCount;
				if (cur.direct != i && cur.direct != -1) {
					new_turns++;
				}
				if (new_turns > 2)continue;
				if (new_turns < min_turns[nx][ny]) {
					min_turns[nx][ny] = new_turns;
					//前驱点
					pre[nx][ny] = { cur.x, cur.y };
					dir[nx][ny] = i;
					q.push({ nx, ny, i, new_turns });
				}
			}
		}
	}
	return flag;
}

bool linkGame::whetcherConnect2(Point a, Point b)
{
	struct Node {
		int x, y;
		int direct;
		int turnCount;
	};
	bool flag = false;
	std::vector<std::vector<int>>min_turns(rows + 2, std::vector<int>(cols + 2, 4));
	std::queue<Node>q;
	q.push({ a.x + 1, a.y + 1, -1, 0 });
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			if (nx == b.x + 1 && ny == b.y + 1 && cur.turnCount + (i != cur.direct) <= 2) {
				flag = true;
				break;
			}
			if (nx >= 0 && nx < rows + 2 && ny >= 0 && ny < cols + 2 && !mp[nx][ny]) {
				int new_turns = cur.turnCount;
				if (cur.direct != i && cur.direct != -1) {
					new_turns++;
				}
				if (new_turns > 2)continue;
				if (new_turns < min_turns[nx][ny]) {
					min_turns[nx][ny] = new_turns;
					q.push({ nx, ny, i, new_turns });
				}
			}
		}
	}
	return flag;
}

void linkGame::updateShowLines( Point a, Point b)
{
	//展示连接的线
	a = { a.x + 1, a.y + 1 };
	//前一个点
	Point last = pre[b.x + 1][b.y + 1];
	//当前点
	Point cur = { b.x + 1, b.y + 1 };

	while (last != a) {
		int d1 = dir[cur.x][cur.y];
		int d2 = dir[last.x][last.y];
		if (d1 == d2 && (d1 == 2 || d1 == 3)) {
			lines[last.x][last.y] = 2;
		}
		else if (d1 == d2 && (d1 == 1 || d1 == 0)) {
			lines[last.x][last.y] = 1;
		}
		else if ((d1 == 1 && d2 == 2) || (d1 == 3 && d2 == 0)) {
			lines[last.x][last.y] = 6;
		}
		else if ((d1 == 1 && d2 == 3) || (d1 == 2 && d2 == 0)) {
			lines[last.x][last.y] = 5;
		}
		else if ((d1 == 0 && d2 == 2) || (d1 == 3 && d2 == 1)) {
			lines[last.x][last.y] = 3;
		}
		else if ((d1 == 0 && d2 == 3) || (d1 == 2 && d2 == 1)) {
			lines[last.x][last.y] = 4;
		}
		cur = last;
		last = pre[last.x][last.y];
	}
}

void linkGame::showLines()
{
	for(int i = 0; i < rows + 2; i++)
		for (int j = 0; j < cols + 2; j++) {
			int x = (j - 1) * blockSize + leftBound;
			int y = (i - 1) * blockSize + topBound;
			if (lines[i][j] == 0)continue;
			putimagePNG(x, y, &line[lines[i][j] - 1]);
			lines[i][j] = 0;
		}
}

void linkGame::getHint()
{
	for (int i = 0; i < rows * cols; i++) {
		int x1 = i / cols, y1 = i % cols;
		if (mp[x1 + 1][y1 + 1] == 0)
			continue;
		Point a = { x1, y1 };
		for (int j = i + 1; j < rows * cols; j++) {
			int x2 = j / cols, y2 = j % cols;
			if (mp[x2 + 1][y2 + 1] == 0)
				continue;
			Point b = { x2, y2 };
			if (findGcd(nums[x1][y1], nums[x2][y2]) != 1 && whetcherConnect(a, b)) {
				choose[x1][y1] = 1;
				choose[x2][y2] = 1;
				return;
			}
		}
	}
}

void linkGame::showBegin()
{

	int timer = 0;

	BeginBatchDraw();
	putimage(0, 0, &beginImage);
	putimage(beginBotton_x, beginBotton_y, &beginBotton);
	putimage(continue_x, continue_y, &continueBotton);
	putimage(quit_x, quit_y, &quit);
	putimage(logout_x, logout_y, &logOut);
	putimage(rank_x, rank_y, &rankBotton);
	putimage(intro_x, intro_y, &intro);
	//putimage(music_x, music_y, &musicBotton);
	EndBatchDraw();
}


int linkGame::checkLose()
{
	int t = 0;
	bool flag = true;
	for (int i = 0; i < rows * cols; i++) {
		int x1 = i / cols, y1 = i % cols;
		if (mp[x1 + 1][y1 + 1] == 0)
			continue;
		Point a = { x1, y1 };
		for (int j = i + 1; j < rows * cols; j++) {
			t = 0;
			int x2 = j / cols, y2 = j % cols;
			if (mp[x2 + 1][y2 + 1] == 0)
				continue;
			Point b = { x2, y2 };
			if (findGcd(nums[x1][y1], nums[x2][y2]) != 1) {
				t = 1;
			}
			if (t == 1 && whetcherConnect2(a, b)) {
				return 0;
			}
			else if (t == 1) {
				flag = false;
			}
		}
	}
	//所有数对均已无最大公约数
	if (flag) {
		return 2;		
	}
	//无可连接点
	else {
		return 1;
	}
}

void linkGame::Message(int val)
{
	int x = 258, y = 420;
	switch (val)
	{
	case -1:
		putimage(x, y, &acountExist);
		break;
	case 0:
		putimage(x, y, &registerSuccess);
		break;
	case 1:
		putimage(x, y, &keyTypeWrong);
		break;
	case 2:
		putimage(x, y, &acountTypeWrong);
		break;
	case 3:
		putimage(x, y, &keyUnmatch);
		break;
	case 4:
		putimage(x, y, &noAcount);
		break;
	case 5:
		putimage(x, y, &keyWrong);
		break;
	default:
		break;
	}
}

void linkGame::showRank(int level)
{
	BeginBatchDraw();

	setcolor(RGB(0, 0, 0));				//设置字体颜色
	LOGFONT	f;							//字体变量
	gettextstyle(&f);					//获取
	f.lfHeight = 80;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;	//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("微软雅黑")); //设置字体
	settextstyle(&f);
	setbkmode(TRANSPARENT);				//透明背景			

	putimage(0, 0, &rank);
	putimage(300, 800, &returnBotton);
	char numText[30]{};
	sprintf_s(numText, sizeof(numText), "%d", level + 1);
	outtextxy(330, 50, numText);
	EndBatchDraw();
}

void linkGame::getName(char s[12])
{
	for(int i = 0; i < 12; i++)
		name [i] = s[i];
}



