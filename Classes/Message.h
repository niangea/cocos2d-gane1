#pragma once
#include "cocos2d.h"					//����ͷ�ļ�

using namespace cocos2d;				//ʹ��cocos2d�����ռ�

class Message : public Layer		//�½�һ���࣬�̳в㣨Layer��
{
public:
    static Scene* createScene();		//Message��������ʵ��

    virtual bool init();				//Message��ĳ�ʼ��

    CREATE_FUNC(Message);			//����Message��Create����

    void EnterSecondScene(Ref* pSender);	//����һ���˵��ص�����������ʵ���˳�������ת
};