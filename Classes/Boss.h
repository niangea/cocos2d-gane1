#pragma once

#include "cocos2d.h"					

using namespace cocos2d;

class Boss : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Boss);

	void StartGame(Ref* pSender);//ת������ʼ����	


	void Gameset(Ref* pSender);//ת������Ϸ����

	void MusicSet(Ref* pSender); //ת������������

	void Message(Ref* pSender); ///ת������Ϸ��Ϣ

	void loadvideo();

	void StartGame2(Ref* pSender);
};