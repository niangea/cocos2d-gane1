#include "StartGUI.h"
#include"HelloWorldScene.h"
#include<string>
#include "SimpleAudioEngine.h"
#include"MazeScene.h"
#include"Message.h"
#include"config.h"
#include"gameset.h"
#include"AnimationScene.h"
#include"End.h"

using namespace std;


/*
��Ϸ�Ľ��뻭��
��1����ʼ��Ϸ
��2����Ϸ����
��3���������ֿ�ݰ�ť
��4����Ϸ�汾��Ϣ
*/


// GBKתUTF-8
std::string GBK2UTF82(const std::string& gbk) {
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


void StartGUI::loadvideo() {
	
}

//StartGUI��������ʵ��
Scene* StartGUI::createScene()
{
	auto scene = Scene::create();	
	auto layer = StartGUI::create();
	scene->addChild(layer);		
	return scene;			
}

bool StartGUI::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (musicoff == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("4.mp3", true); //��ʼ��������
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicpos);
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
	this->addChild(pic, 1);
	pic->setPosition(Vec2(700, 350));




	//��ʼ��ť
	auto label = Label::createWithSystemFont(GBK2UTF82("��ʼ��Ϸ!"), "fonts/HGWT_CNKI.TTF", 40);
	
	auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(StartGUI::StartGame, this));
	
	//�������ڰ�ť
	auto label2 = Label::createWithSystemFont(GBK2UTF82("��������"), "fonts/HGWT_CNKI.TTF", 40);

	auto menuitem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(StartGUI::Gameset, this));
	menuitem->setTag(10001);
	menuitem2->setTag(10002);

	auto menu = Menu::create(menuitem, menuitem2, NULL);
	menu->alignItemsVertically();

	//���ֿ��ذ�ť
	auto label3 = Sprite::create("music.png");

	label3->setTag(1111);
	auto menuitem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(StartGUI::MusicSet, this));
	menuitem3->setPosition(Vec2(350,300));

	menuitem3->setTag(2222);
	auto m = Menu::create(menuitem3, NULL);
	m->setTag(3333);
	this->addChild(m, 12);

	//��Ϸ��Ϣ��ť
	auto label4 = MenuItemImage::create(
		"mess.png",
		"mess.png",
		CC_CALLBACK_1(StartGUI::Messages, this));
	auto menuitem4 = MenuItemLabel::create(label4, CC_CALLBACK_1(StartGUI::Messages, this));
	menuitem4->setPosition(Vec2(400, 300));
	auto m2 = Menu::create(menuitem4, NULL);
	this->addChild(m2, 12);	
	this->addChild(menu,10);



	return true;
}


void  StartGUI::StartGame2(Ref* pSender) {
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

//������Ϸ
void StartGUI::StartGame(Ref* pSender)
{
	auto go = CallFuncN::create([&](Ref* psender) {
		Director::getInstance()->replaceScene(MazeScene::createScene());
		});
	auto loadvideos = CallFuncN::create([&](Ref* psender) {
		Vector<SpriteFrame* >frameVector;
		for (int i = 2; i <= 606; i += 2)
		{
		
			auto spriteFrame = SpriteFrame::create("show/" + to_string(i) + ".jpg", Rect(0, 0, 1424, 768));
			frameVector.pushBack(spriteFrame);
		}
		auto animation = Animation::createWithSpriteFrames(frameVector);
		animation->setDelayPerUnit(0.07f);
		auto animate = Animate::create(animation);


		auto pic = Sprite::create();
		pic->runAction(RepeatForever::create(animate));
		this->addChild(pic, 10000);
		pic->setPosition(Vec2(700, 350));
		
		});
	auto opt = Sequence::create(
		loadvideos,
		DelayTime::create(7.5),
		go,
		nullptr		
	);
	auto act = RepeatForever::create(opt);
	this->runAction(act);

}

//������Ϸ����
void StartGUI::Gameset(Ref* pSender)
{
	Director::getInstance()->replaceScene(Gameset::createScene());

}

int tag = 0;
//������������
void StartGUI::MusicSet(Ref* pSender)
{
	auto b = (Sprite*)this->getChildByTag(3333)->getChildByTag(2222)->getChildByTag(1111);
	if (tag == 0) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();//��ͣ��������

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("music2.png");
		b->setTexture(texture);
		tag = 1;

		musicoff = 1;
	}
	else {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();//��ͷ���ñ�������

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("music.png");
		b->setTexture(texture);
		tag = 0;

		musicoff = 0;
	}

}

//�����Ȩ��Ϣ
void StartGUI::Messages(Ref* pSender)
{

	Director::getInstance()->replaceScene(Message::createScene());
}