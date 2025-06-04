#include "Click.h"
#include<string>

const int MAXS[4] = { 50, 100, 200, 350 };
const int row[4] = { 4, 6 , 8, 10 }, col[4] = { 4, 6, 8, 10};
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
const int noConnect_x = 0, noConnect_y = 0;
const int hint_x = 590, hint_y = 440;
const int return_x = 590, return_y = 530;
const int return_x2 = 266, return_y2 = 613;
const int levelup_x = 483, levelup_y = 394;
const int leveldown_x = 246, leveldown_y = 392;
const int again_x = 300, again_y = 630;
const int play_x = 266, play_y = 510;
const int key_x = 313, key_y = 441;
const int acount_x = 313, acount_y = 381;
const int key2_x = 313, key2_y = 501;
const int sure_x = 350, sure_y = 600;
const int back_x = 171, back_y = 249;
const int register_x = 300, register_y = 556;
const int login_x = 300, login_y = 425;

Click::Click()
{
	messageVal = 0;
	input_acount = false;
	input_key = false;
	input_key2 = false;
}

void Click::update()
{
	int timer = 0;
	while (true) {
		click();				//如果用户有点击会使whetherupdate变成true
		timer += getDelay();	//获取两次while循环间的延迟
		if (timer > delay) {
			timer = 0;
			whetherUpdate = true;
		}
		//渲染画面
		if (whetherUpdate) {
			whetherUpdate = false;
			show();
			if (input_acount) 
				user.inputAcount();
			else if (input_key)
				user.inputKey();
			else if (input_key2)
				user.inputKey2();
			else if(_kbhit())
				_getch();
		}
	}
}

void Click::show()
{
	switch (picture)
	{
	case Enter:
		game.displayEnter();
		break;
	case begin:
		game.showBegin();
		break;
	case playgame:
		if (!game.play())
			picture = gameover;
		break;
	case gameover:
		game.displayOver();
		break;
	case description:
		game.Descrition();
		break;
	case levelchoose:
		game.displayLevel();
		break;
	case Register:
		BeginBatchDraw();
		game.displayRegister();
		user.showRegister(game.see, game.see2);
		EndBatchDraw();
		break;
	case Login:
		BeginBatchDraw();
		game.displayLogin();
		user.showLogin(game.see);
		EndBatchDraw();
		break;
	case message:
		game.Message(messageVal);
		break;
	case rank:
		game.showRank(rankLevel);
		break;
	default:
		break;
	}
}
void Click::click()
{
	ExMessage msg; 
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {	//鼠标左键
			switch (picture)
			{
			case Enter:
				enterPicture(msg);
				break;
			case begin:
				beginPicture(msg);
				break;
			case playgame:
				playPicture(msg);
				break;
			case gameover:
				overPicture(msg);
				break;
			case description:
				introPicture(msg);
				break;
			case levelchoose:
				levelPicture(msg);
				break;
			case Register:
				registerPicture(msg);
				break;
			case Login:
				loginPicture(msg);
				break;
			case message:
				messagePicture(msg);
				break;
			case rank:
				rankPicture(msg);
				break;
			default:
				break;
			}
			
		}
	}
}
void Click::enterPicture(ExMessage& msg)
{
	if (msg.x > register_x && msg.x < register_x + 200 &&
		msg.y > register_y && msg.y < register_y + 60) {
		picture = Register;
	}
	if (msg.x > login_x && msg.x < login_x + 200 &&
		msg.y > login_y && msg.y < login_y + 60) {
		picture = Login;
	}
	if (msg.x > quit_x && msg.x < quit_x + 200 &&
		msg.y > quit_y && msg.y < quit_y + 60)
		exit(0);
}

void Click::playPicture(ExMessage& msg)
{
	static bool whetherChoose;
	if (msg.x > leftBound && msg.x < leftBound + cols * blockSize &&
		msg.y > topBound && msg.y < topBound + rows * blockSize) {
		int col = (msg.x - leftBound) / blockSize;
		int row = (msg.y - topBound) / blockSize;
		//第二次点击格子
		if (whetherChoose) {
			Point cur = { row, col };
			if (cur != lastchoose) {
				whetherChoose = false;

				//清空choose数组
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
					{
						game.choose[i][j] = 0;
					}

				game.clear(cur, lastchoose);

			}
		}
		//第一次点击格子
		else {
			if (game.nums[row][col] != 1) {
				lastchoose = { row, col };
				game.choose[row][col] = 1;
				whetherChoose = true;
			}
		}
	}

	//点击提示
	if (msg.x > hint_x && msg.x < hint_x + 200 &&
		msg.y > hint_y && msg.y < hint_y + 60) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				game.choose[i][j] = 0;
			}
		whetherChoose = 0;
		game.getHint();
	}

	//点击返回
	if (msg.x > return_x && msg.x < return_x + 200 &&
		msg.y > return_y && msg.y < return_y + 60) {
		picture = begin;
	}
}

void Click::overPicture(ExMessage& msg)
{
	if (msg.x > quit_x && msg.x < quit_x + 200 &&
		msg.y > quit_y && msg.y < quit_y + 60)
		exit(0);
	if (msg.x > again_x && msg.x < again_x + 200 &&
		msg.y > again_y && msg.y < again_y + 60)
		picture = begin;
}

void Click::levelPicture(ExMessage& msg)
{
	if (msg.x > leveldown_x && msg.x < leveldown_x + 36 &&
		msg.y > leveldown_y && msg.y < leveldown_y + 52) {
		game.level--;
		if (game.level < 1)
			game.level = 4;
	}
	if (msg.x > levelup_x && msg.x < levelup_x + 36 &&
		msg.y > levelup_y && msg.y < levelup_y + 52) {
		game.level++;
		if (game.level > 4)
			game.level = 1;
	}
	if (msg.x > play_x && msg.x < play_x + 259 &&
		msg.y > play_y && msg.y < play_y + 71) {
		rows = row[game.level - 1];
		cols = col[game.level - 1];
		leftBound = LeftBound[game.level - 1];
		topBound = TopBound[game.level - 1];
		picture = playgame;
		game.init();
	}
	if (msg.x > return_x2 && msg.x < return_x2 + 259 &&
		msg.y > return_y2 && msg.y < return_y2 + 71) {
		game.level = 1;
		picture = begin;
	}
}

void Click::loginPicture(ExMessage& msg)
{

	if (msg.x > acount_x && msg.x < acount_x + 240 &&
		msg.y > acount_y && msg.y < acount_y + 40) {
		input_acount = true;
		input_key = false;

	}
	else if (msg.x > key_x && msg.x < key_x + 240 &&
		msg.y > key_y && msg.y < key_y + 40) {
		input_acount = false;
		input_key = true;
	}
	else if (msg.x > key_x + 250 && msg.x < key_x + 250 + 61 &&
		msg.y > key_y && msg.y < key_y + 40) {
		game.see = 1 - game.see;
	}
	else {
		if (msg.x > sure_x && msg.x < sure_x + 120 &&
			msg.y > sure_y && msg.y < sure_y + 50) {
			int val = user.checkLogin();
			//登录成功
			if (val == 6) {
				game.getName(user.acount);
				user.init();
				picture = begin;
			}
			else {
				messageVal = val;
				picture = message;
			}
		}
		if (msg.x > back_x && msg.x < back_x + 120 &&
			msg.y > back_y && msg.y < back_y + 50) {
			user.init();
			game.see = 0;
			game.see2 = 0;
			picture = Enter;
		}
		input_acount = false;
		input_key = false;
	}
}

void Click::messagePicture(ExMessage& msg)
{
	if (msg.x > sure_x && msg.x < sure_x + 120 &&
		msg.y > sure_y && msg.y < sure_y + 50)
	{
		if (messageVal < 4) 
		{
			picture = Register;
		}
		else picture = Login;
	}
}

void Click::rankPicture(ExMessage& msg)
{
	if (msg.x > 50  && msg.x < 50 + 57 &&
		msg.y > 445 && msg.y < 49 + 445)
	{
		rankLevel = (rankLevel + 3) % 4;
	}
	else if (msg.x > 682 && msg.x < 682 + 57 &&
		msg.y > 445 && msg.y < 49 + 445)
	{
		rankLevel = (rankLevel + 1) % 4;
	}
	else if (msg.x > 300 && msg.x < 500 &&
		msg.y > 800 && msg.y < 860)
	{
		rankLevel = 0;
		picture = begin;
	}
}

void Click::introPicture(ExMessage& msg)
{

}

void Click::registerPicture(ExMessage& msg)
{
	if (msg.x > acount_x && msg.x < acount_x + 240 &&
		msg.y > acount_y && msg.y < acount_y + 40)
	{
		input_acount = true;
		input_key = false;
		input_key2 = false;
	}
	else if (msg.x > key_x && msg.x < key_x + 240 &&
		msg.y > key_y && msg.y < key_y + 40) 
	{
		input_key = true;
		input_acount = false;
		input_key2 = false;
	}
	else if (msg.x > key2_x && msg.x < key2_x + 240 &&
		msg.y > key2_y && msg.y < key2_y + 40)
	{
		input_key2 = true;
		input_acount = false;
		input_key = false;
	}
	else if (msg.x > key_x + 250 && msg.x < key_x + 250 + 61 &&
		msg.y > key_y && msg.y < key_y + 40)
	{
		game.see = 1 - game.see;
	}
	else if (msg.x > key2_x + 250 && msg.x < key2_x + 250 + 61 &&
		msg.y > key2_y && msg.y < key2_y + 40) 
	{
		game.see2 = 1 - game.see2;
	}
	else{
		if (msg.x > sure_x && msg.x < sure_x + 120 &&
			msg.y > sure_y && msg.y < sure_y + 50)
		{
			int val = user.checkRegister();
			messageVal = val;
			picture = message;
		}
		if (msg.x > back_x && msg.x < back_x + 120 &&
			msg.y > back_y && msg.y < back_y + 50) 
		{
			picture = Enter;
			game.see = 0;
			game.see2 = 0;
			user.init();
		}
		input_key2 = false;
		input_acount = false;
		input_key = false;
	}
}

void Click::beginPicture(ExMessage& msg)
{
	if (msg.x > beginBotton_x && msg.x < beginBotton_x + 200 &&
		msg.y > beginBotton_y && msg.y < beginBotton_y + 60) 
	{
		picture = levelchoose;
	}
	else if (msg.x > continue_x && msg.x < continue_x + 200 &&
		msg.y > continue_y && msg.y < continue_y + 60)
	{
		game.init2();
		picture = playgame;
	}
	else if (msg.x > quit_x && msg.x < quit_x + 200 &&
		msg.y > quit_y && msg.y < quit_y + 60)
		exit(0);
	else if (msg.x > rank_x && msg.x < rank_x + 200 &&
		msg.y > rank_y && msg.y < rank_y + 60)
	{
		rankLevel = 0;
		picture = rank;
	}
	else if (msg.x > intro_x && msg.x < intro_x + 200 &&
		msg.y > intro_y && msg.y < intro_y + 60)
	{

	}
	else if (msg.x > logout_x && msg.x < logout_x + 200 &&
		msg.y > logout_y && msg.y < logout_y + 60) 
	{
		picture = Enter;
	}
}

int Click::getDelay()
{
	static unsigned long long lasTime = 0;
	unsigned long long current = GetTickCount();
	if (lasTime == 0) 
	{
		lasTime = current;
		return 0;
	}
	else 
	{
		int res = current - lasTime;
		lasTime = current;
		game.curTime += res;
		return res;
	}
	
}

