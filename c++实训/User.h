﻿#pragma once 
#include<conio.h>
#include<iostream>
#include<string>
#include<unordered_map>
#include<graphics.h>

class User
{
public:
	User();
	void saveUser();
	void init();
	void initKey2();
	void inputKey();
	void inputAcount();
	void inputKey2();
	int checkRegister();
	int checkLogin();
	int checkCancel();
	void showKey2(bool see2);
	void showKey(bool see);
	void showAcount();
	long long gethash(char *s, int n);
	void cancel();							//删除账号
	char acount[12];
	

private:
	std::unordered_map<std::string, long long>mp;
	char key[12];
	char key2[12];
	char invisibleKey[12];
	char invisibleKey2[12];
	int acount_n;
	int key2_n;
	int key_n;
};

