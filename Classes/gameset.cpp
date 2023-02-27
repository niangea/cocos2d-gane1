#include "gameset.h"
#include"HelloWorldScene.h"
#include"StartGUI.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include"cocos-ext.h"
USING_NS_CC_EXT;

USING_NS_CC;



//StartGUI��������ʵ��
Scene* Gameset::createScene()
{
	auto scene = Scene::create();	//����һ������
	auto layer = Gameset::create();//����һ��StartGUI��
	scene->addChild(layer);		//��StartGUI�����ոմ����ĳ����У�
	return scene;			//�����������
}

bool Gameset::init()
{
	if (!Layer::init())	//�ȳ�ʼ�������init��������γ�ʼ��ʧ�ܣ��򴴽�StartGUI��ʧ��
	{
		return false;
	}
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С

	//��������
	
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("4.mp3", true); //��ʼ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
	
	auto slide_control = ControlSlider::create("ba1.png", "ba2.png", "bb1.png");

	slide_control->setPosition(Vec2(550, 500));

	slide_control->setMinimumValue(0);
	slide_control->setMaximumValue(100);
	slide_control->setValue(0);
	slide_control->setTag(20);
	slide_control->addTargetWithActionForControlEvents(this, cccontrol_selector(Gameset::valueChanged), Control::EventType::VALUE_CHANGED);
	this->addChild(slide_control,1001);
		


	auto cloud_1 = Sprite::create("set.png");
	cloud_1->setPosition(Vec2(1024 / 2, 768 / 2));

	this->addChild(cloud_1);
	//�˵���Ŀ�Ĵ����ж��֣�֮ǰ��HelloWorld.cpp��ʵ�ֵ���ͼƬ�˵���Ŀ(MenuItemImage)��������ͼƬ�������˵���Ŀ
	//�����Ǹ��ݱ�ǩ�������˵���Ŀ,Ȼ�����ûص�����
	auto menuitem = MenuItemImage::create(
		"goback.png",
		"goback.png",
		CC_CALLBACK_1(Gameset::EnterSecondScene, this));
	//�������˲˵���Ŀ������Ҫ����˵��У�����������Ǵ����˵�
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(Vec2(50, 700));
	//�Ѳ˵���ӵ�StartGUI����
	this->addChild(menu, 100);

	

	return true;
}





//�˵��ص�������ʵ��
void Gameset::EnterSecondScene(Ref* pSender)
{
	//����֪���������Ҫ��ת�������ͻ��뵽һ���࣬������Director�࣬�����ǹ�������
	//������ת�������õ����ǵ����������ӿڣ�replaceScene(Scene *scene),���洫��ȥ���Ǿ���һ��������������Ҫע����ǳ�������ͷ�ļ�����Ҫ���ϵ�
	Director::getInstance()->replaceScene(StartGUI::createScene());
}


void Gameset::valueChanged(Ref* pSender, Control::EventType controlEvent) {
	double value = dynamic_cast<ControlSlider*>(pSender)->getValue();
	
	musicpos = value/(double)100;

	double v = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();

	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicpos);


	
}

