#include "Message.h"
#include"HelloWorldScene.h"
#include"StartGUI.h"

//StartGUI��������ʵ��
Scene* Message::createScene()
{
	auto scene = Scene::create();	//����һ������
	auto layer = Message::create();//����һ��StartGUI��
	scene->addChild(layer);		//��StartGUI�����ոմ����ĳ����У�
	return scene;			//�����������
}

bool Message::init()
{
	if (!Layer::init())	//�ȳ�ʼ�������init��������γ�ʼ��ʧ�ܣ��򴴽�StartGUI��ʧ��
	{
		return false;
	}
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С

	auto cloud_1 = Sprite::create("messgui.png");
	cloud_1->setPosition(Vec2(1024 / 2, 768 / 2));

	this->addChild(cloud_1);
	//�˵���Ŀ�Ĵ����ж��֣�֮ǰ��HelloWorld.cpp��ʵ�ֵ���ͼƬ�˵���Ŀ(MenuItemImage)��������ͼƬ�������˵���Ŀ
	//�����Ǹ��ݱ�ǩ�������˵���Ŀ,Ȼ�����ûص�����
	auto menuitem = MenuItemImage::create(
		"goback.png",
		"goback.png",
		CC_CALLBACK_1(Message::EnterSecondScene, this));
	//�������˲˵���Ŀ������Ҫ����˵��У�����������Ǵ����˵�
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(Vec2(50, 700));
	//�Ѳ˵���ӵ�StartGUI����
	this->addChild(menu,100);

	return true;
}
//�˵��ص�������ʵ��
void Message::EnterSecondScene(Ref* pSender)
{
	//����֪���������Ҫ��ת�������ͻ��뵽һ���࣬������Director�࣬�����ǹ�������
	//������ת�������õ����ǵ����������ӿڣ�replaceScene(Scene *scene),���洫��ȥ���Ǿ���һ��������������Ҫע����ǳ�������ͷ�ļ�����Ҫ���ϵ�
	Director::getInstance()->replaceScene(StartGUI::createScene());
}