#pragma once
#include "cocos2d.h"					//����ͷ�ļ�
#include"config.h"

#include"cocos-ext.h"
USING_NS_CC_EXT;

USING_NS_CC;

using namespace cocos2d;				//ʹ��cocos2d�����ռ�

class Gameset : public Layer		//�½�һ���࣬�̳в㣨Layer��
{
public:
	static Scene* createScene();		

	virtual bool init();				

	CREATE_FUNC(Gameset);	

	
	
	void valueChanged(Ref* pSender, Control::EventType controlEvent);

	void EnterSecondScene(Ref* pSender);	//����һ���˵��ص�����������ʵ���˳�������ת
};