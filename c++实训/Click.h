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
	void update();							//������Ϸ
	void show();							//չʾ����
	void click();							//�������¼�
	void enterPicture(ExMessage& msg);					//������Ϸ����
	void beginPicture(ExMessage& msg);		//��ʼ����
	void playPicture(ExMessage& msg);		//��Ϸ����
	void overPicture(ExMessage& msg);		//��������
	void levelPicture(ExMessage& msg);		//�Ѷ�ѡ�����
	void registerPicture(ExMessage& msg);	//ע��ҳ��
	void loginPicture(ExMessage& msg);		//��¼����
	void messagePicture(ExMessage& msg);							//ע��͵�¼ʧ�ܻ�ɹ�����Ϣ
	void rankPicture(ExMessage& msg);					//���а�
	void introPicture(ExMessage& msg);		//�̳̽���
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
	bool input_key;					//�Ƿ�������
	bool input_acount;
	bool input_key2;
	int messageVal;					//������Ϣ
	int rankLevel;					//��ǰչʾ�����а���ڵ��Ѷ�
};

