#include "User.h"
#include<iostream>
#include<fstream>

const int b = 131, mod = 1e9 + 9, mod2 = 1e9 + 7;
long long bpow[20], bpow2[20];

User::User()
{
	key_n = 0;
	key2_n = 0;
	acount_n = 0;
	for (int i = 0; i < 12; i++)
	{
		key[i] = '\0';
		invisibleKey[i] = '\0';
		key2[i] = '\0';
		invisibleKey2[i] = '\0';
		acount[i] = '\0';
	}
	//导入账号
	int n;
	std::string Acount;
	long long Key;
	std::ifstream file("user.txt");
	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i < n; i++)
		{
			file >> Acount;
			file >> Key;
			mp[Acount] = Key;
		}
	}
	//预处理基数幂
	bpow[0] = 1;
	bpow2[0] = 1;
	for (int i = 1; i < 20; i++)
	{
		bpow[i] = bpow[i - 1] * b % mod;
		bpow2[i] = bpow2[i - 1] * b % mod2;
	}
}

void User::saveUser()
{
	int n = mp.size();
	std::ofstream file("user.txt");
	if (file.is_open()) 
	{
		file << n;
		file << '\n';
		for (auto& [x, y] : mp) 
		{
			file << x << '\n' << y << '\n';
		}
	}
}

void User::init()
{
	key_n = 0;
	key2_n = 0;
	acount_n = 0;
	for (int i = 0; i < 12; i++)
	{
		key[i] = '\0';
		invisibleKey[i] = '\0';
		key2[i] = '\0';
		invisibleKey2[i] = '\0';
		acount[i] = '\0';
	}
}

void User::inputKey()
{

	if (_kbhit())
	{
		char c = _getch();
		//Enter
		if (c == 13)
		{
			return;
		}
		//Backspace
		else if (c == 8)
		{
			if (key_n > 0) 
			{
				key_n--;
				key[key_n] = '\0';
				invisibleKey[key_n] = '\0';
			}
		}
		else {
			if (key_n < 10) 
			{
				key[key_n] = c;
				invisibleKey[key_n] = '*';
				key_n++;
				key[key_n] = '\0';
				invisibleKey[key_n] = '\0';
			}
		}
	}
}

void User::inputAcount()
{
	if (_kbhit())
	{
		char c = _getch();
		//Enter
		if (c == 13)
		{
			return;
		}
		//Backspace
		else if (c == 8)
		{
			if (acount_n > 0) 
			{
				acount_n--;
				acount[acount_n] = '\0';
			}
		}
		else {
			if (acount_n < 10)
			{
				acount[acount_n] = c;
				acount_n++;
				acount[acount_n] = '\0';
			}
		}
	}
}

void User::inputKey2()
{

	if (_kbhit())
	{
		char c = _getch();
		//Enter
		if (c == 13)
		{
			return;
		}
		//Backspac
		else if (c == 8)
		{
			if (key2_n > 0)
			{
				key2_n--;
				key2[key2_n] = '\0';
				invisibleKey2[key2_n] = '\0';
			}
		}
		else {
			if (key2_n < 10) 
			{
				key2[key2_n] = c;
				invisibleKey2[key2_n] = '*';
				key2_n++;
				key2[key2_n] = '\0';
				invisibleKey2[key2_n] = '\0';
			}
		}
	}
}

int User::checkRegister()
{	
	//账号格式不对
	if (acount_n == 0)return 2;
	for (int i = 0; i < acount_n; i++) 
	{
		if (acount[i] < 'a' && acount[i] > 'z' && acount[i] < 'A' && acount[i] > 'Z' && acount[i] < '0' && acount[i] > '9')
			return 2;
	}
	//密码不一致
	if (key_n != key2_n)return 3;
	for (int i = 0; i < key_n; i++)
	{
		if (key[i] != key2[i])
			return 3;
	}
	//密码格式不对
	if (key_n == 0)return 1;
	for (int i = 0; i < key_n; i++) {
		if (key[i] < 'a' && key[i] > 'z' && key[i] < 'A' && key[i] > 'Z' && key[i] < '0' && key[i] > '9')
			return 1;
	}
	//账号已存在
	if (mp.find(acount) != mp.end())
		return -1;
	mp[acount] = gethash(key, key_n);
	saveUser();
	return 0;
}

int User::checkLogin()
{
	std::string s_acount = acount;
	std::string s_key = key;
	//账号不存在
	if (mp.find(s_acount) == mp.end())
		return 4;
	//密码错误
	if (mp[s_acount] != gethash(key, key_n))
		return 5;
	return 6;
}

void User::showRegister(bool see1, bool see2)
{

	setcolor(RGB(0, 0, 0));				//设置字体颜色
	LOGFONT	f;							//字体变量
	gettextstyle(&f);					//获取
	f.lfHeight = 25;
	f.lfWidth = 12;
	f.lfQuality = ANTIALIASED_QUALITY;	//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("微软雅黑")); //设置字体
	settextstyle(&f);
	setbkmode(TRANSPARENT);				//透明背景

	if (see1)
	{
		outtextxy(313, 441, key);
	}
	else 
	{
		outtextxy(313, 441, invisibleKey);
	}
	if (see2)
	{
		outtextxy(313, 501, key2);
	}
	else
	{
		outtextxy(313, 501, invisibleKey2);
	}
	outtextxy(313, 381, acount);

}

void User::showLogin(bool see)
{
	setcolor(RGB(0, 0, 0));				//设置字体颜色
	LOGFONT	f;							//字体变量
	gettextstyle(&f);					//获取
	f.lfHeight = 25;
	f.lfWidth = 12;
	f.lfQuality = ANTIALIASED_QUALITY;	//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("微软雅黑")); //设置字体
	settextstyle(&f);
	setbkmode(TRANSPARENT);				//透明背景


	if (see) 
	{
		outtextxy(313, 441, key);
	}
	else 
	{
		outtextxy(313, 441, invisibleKey);
	}
	outtextxy(313, 381, acount);

}

long long User::gethash(char* s, int n)
{
	long long hash1 = 0, hash2 = 0;
	for (int i = 0; i < n; i++)
	{
		hash1 = (hash1 + (s[i] * bpow[i]) % mod) % mod;
		hash2 = (hash2 + (s[n - 1 - i] * bpow2[i]) % mod2) % mod2;
	}
	return hash1 | (hash2 << 31);
}


