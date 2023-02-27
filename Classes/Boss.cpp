#include "Boss.h"
#include"HelloWorldScene.h"
#include<string>
#include "SimpleAudioEngine.h"
#include"MazeScene.h"
#include"Message.h"
#include"config.h"
#include"gameset.h"
#include"AnimationScene.h"

using namespace std;


/*
��Ϸ�Ľ��뻭��
��1����ʼ��Ϸ
��2����Ϸ����
��3���������ֿ�ݰ�ť
��4����Ϸ�汾��Ϣ
*/


// GBKתUTF-8
std::string GBK2UTF83(const std::string& gbk) {
	std::string utf_8 = "";

	int n = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);
	WCHAR* str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char* str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	utf_8 = str2;
	delete[]str1;
	str1 = nullptr;
	delete[]str2;
	str2 = nullptr;
	return utf_8;
}


void Boss::loadvideo() {
	this->removeAllChildren(); //���ԭ�����
	// ��ʼ������ʾ����
	Vector<SpriteFrame* >frameVector;
	for (int i = 2; i <= 344; i += 2)
	{
		//�����i��Ӧ�����и��������Ƶ֡��
		auto spriteFrame = SpriteFrame::create("end/" + to_string(i) + ".jpg", Rect(0, 0, 1024, 768));
		frameVector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(frameVector);
	animation->setDelayPerUnit(0.07f);
	auto animate = Animate::create(animation);

	// ��ӻ���
	auto pic = Sprite::create();
	//pic->setTag(PLAYER_TAG);
	pic->runAction(RepeatForever::create(animate));
	this->addChild(pic, 10000);
	pic->setPosition(Vec2(200, 200));
}

//StartGUI��������ʵ��
Scene* Boss::createScene()
{
	auto scene = Scene::create();
	auto layer = Boss::create();
	scene->addChild(layer);
	return scene;
}

bool Boss::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (musicoff == 0) {


		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bossout.mp3", true); //���ű�������

	}




	Size VisibleSize = Director::getInstance()->getVisibleSize();

	// ��ʼ������ʾ����
	Vector<SpriteFrame* >frameVector;
	for (int i = 2; i <= 344; i += 2)
	{
		//�����i��Ӧ�����и��������Ƶ֡��
		auto spriteFrame = SpriteFrame::create("start/" + to_string(i) + ".jpg", Rect(0, 0, 1424, 768));
		frameVector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(frameVector);
	animation->setDelayPerUnit(0.07f);
	auto animate = Animate::create(animation);

	// ��ӻ���
	auto pic = Sprite::create();
	//pic->setTag(PLAYER_TAG);
	pic->runAction(RepeatForever::create(animate));
	//this->addChild(pic, 1);
	pic->setPosition(Vec2(700, 350));




	//��ʼ��ť
	auto label = Label::createWithSystemFont(GBK2UTF83("��ʼ����ս!"), "fonts/HGWT_CNKI.TTF", 40);

	//����ȷ�ϣ�����������
	auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(Boss::StartGame, this));




	
	menuitem->setTag(10001);
	

	auto menu = Menu::create(menuitem, NULL);
	menu->alignItemsVertically();


	//�������ð�ť
	auto label3 = Sprite::create("BOSSSHOW.png");

	label3->setPosition(500, 400);

	//label3->setScale(0.9);

	this->addChild(label3, 12);

	//�������ð�ť

	auto label4 = MenuItemImage::create(
		"mess.png",
		"mess.png",
		CC_CALLBACK_1(Boss::Message, this));

	//auto label4 = Label::createWithSystemFont(GBK2UTF82("��Ϸ��Ϣ"), "fonts/HGWT_CNKI.TTF", 40);

	//����ȷ�ϣ�����������
	auto menuitem4 = MenuItemLabel::create(label4, CC_CALLBACK_1(Boss::Message, this));
	menuitem4->setPosition(Vec2(400, 300));
	
	//auto m2 = Menu::create(menuitem4, NULL);
	//this->addChild(m2, 12);


	auto label5 = MenuItemImage::create(
		"setbutton.png",
		"setbutton.png",
		CC_CALLBACK_1(Boss::Message, this));

	label5->setPosition(Vec2(600, 100));
	//this->addChild(label5, 120);


	/*
	Vector<SpriteFrame* >frameVector;
	for (int i = 2; i <= 400; i += 2)
	{
		//�����i��Ӧ�����и��������Ƶ֡��
		auto spriteFrame = SpriteFrame::create("video/" + to_string(i) + ".jpg", Rect(0, 0, 1024, 768));
		frameVector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(frameVector);
	animation->setDelayPerUnit(0.07f);
	auto animate = Animate::create(animation);

	// ��ӻ���
	auto pic = Sprite::create();
	//pic->setTag(PLAYER_TAG);
	pic->runAction(RepeatForever::create(animate));
	this->addChild(pic, 1);
	pic->setPosition(Vec2(1024 / 2, 768 / 2));
	*/





	this->addChild(menu, 100);



	return true;
}




void  Boss::StartGame2(Ref* pSender) {
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

//������Ϸ
void Boss::StartGame(Ref* pSender)
{
	auto go = CallFuncN::create([&](Ref* psender) {
		Director::getInstance()->replaceScene(AnimationScene::createScene());
		});

	auto loadvideos = CallFuncN::create([&](Ref* psender) {
		// ��ʼ������ʾ����
		Vector<SpriteFrame* >frameVector;
		for (int i = 2; i <= 180; i += 2)
		{
			//�����i��Ӧ�����и��������Ƶ֡��
			auto spriteFrame = SpriteFrame::create("BOSS/" + to_string(i) + ".jpg", Rect(0, 0, 1424, 768));
			frameVector.pushBack(spriteFrame);
		}
		auto animation = Animation::createWithSpriteFrames(frameVector);
		animation->setDelayPerUnit(0.07f);
		auto animate = Animate::create(animation);

		// ��ӻ���
		auto pic = Sprite::create();
		//pic->setTag(PLAYER_TAG);
		pic->runAction(RepeatForever::create(animate));
		this->addChild(pic, 10000);
		pic->setPosition(Vec2(700, 370));

		});
	auto opt = Sequence::create(
		loadvideos,
		DelayTime::create(5.5),
		go,
		nullptr

	);
	auto act = RepeatForever::create(opt);
	this->runAction(act);








}

//������Ϸ����
void Boss::Gameset(Ref* pSender)
{




	Director::getInstance()->replaceScene(Gameset::createScene());
	//Director::getInstance()->replaceScene(AnimationScene::createScene());
}


//������������
void Boss::MusicSet(Ref* pSender)
{



	


	//Director::getInstance()->replaceScene(HelloWorld::createScene());
}

//�����Ȩ��Ϣ
void Boss::Message(Ref* pSender)
{

	Director::getInstance()->replaceScene(Message::createScene());
}