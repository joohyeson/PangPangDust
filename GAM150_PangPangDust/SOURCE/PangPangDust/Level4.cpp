/******************************************************************************/
/*!
\file  Level4.cpp
\author Kim Ha Gyeong
\par    email: digiepn.hagyoeng@gmail.com
\date   2019/06/11

stage 4
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include <SDL2/SDL.h>
#include <engine/State.h>
#include "Level4.h"
#include <ctime>
#include "ComponentTypes.h"
#include "Level4Controller.h"

 int heartCount = 3;
 int red = 0;
 int dustCount = 0;
extern int failDust;
extern float ScaleX;
float timecount = 0;
extern int countt = 0;

float s_count4 = 0;
bool characterState4 = false;

CustomBaseObject& Level4::CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
	float scaleX, float scaleY, const char* filePath, bool isVisible)
{
	sprite.SetName(name);
	sprite.transform.position.Set(positionX, positionY, 0);
	sprite.transform.SetScale(scaleX, scaleY);
	sprite.transform.rotation = 0;
	sprite.sprite.LoadImage(filePath, State::m_renderer);
	sprite.sprite.isHud = true;
	sprite.sprite.isVisible = isVisible;
	State::sCurrentState->AddObject(&sprite);
	return sprite;
}

void Level4::Initialize()
{
	State::sCurrentState = this;
	State::m_pCamera = &camera;
    printf("failDust:%d\n", failDust);
	timecount=0;
	countt = 0;
	camera.position.Set(0, 0, 0);

	m_useBuiltInPhysics = false;
	b2Vec2 gravity(0.0f, -25.8f);
	SetCustomPhysicsWorld(gravity);
	background.SetName("Start");
	background.transform.SetScale(State::m_width, State::m_height);
	background.sprite.LoadImage("texture/background4321.png", State::m_renderer);
	background.transform.position.Set(0, 0, 0);
    background.sprite.SetFrame(4);
    background.sprite.SetSpeed(3.f);
    background.sprite.activeAnimation = true;
    background.sound.LoadSound("sound/Ending_Hero.mp3");
    background.sound.SetVolume(80);

	wall.SetName("Wall");
	wall.transform.position.Set(14000.f, -300.0f, 0.0f);
	wall.transform.SetScale(30000, 10);
	wall.sprite.color = SDL_Color{ 255, 255, 255, 255 };
	wall.sprite.LoadImage("texture/rect.png", State::m_renderer);
	wall.sprite.color.r = wall.sprite.color.g
		= wall.sprite.color.b = 0X0;
	wall.customPhysics.pOwnerTransform = &wall.transform;
	wall.customPhysics.bodyType = CustomPhysics::STATIC;
	wall.customPhysics.AllocateBody(GetCustomPhysicsWorld());

	miss4.SetName("MISS4");
	miss4.transform.position.Set(0, -500, 0.f);
	miss4.transform.SetScale(150, 50);
	miss4.sprite.LoadImage("texture/MISS.png", State::m_renderer);

	time.SetName("time");
	time.transform.position.Set(50, 100, 0.f);
	time.transform.SetScale(1000, 300);
	time.sprite.LoadImage("texture/time.png", State::m_renderer);

	CheckPoint.SetName("CheckPoint");
	CheckPoint.transform.position.Set(12700.f, -200.f, 0.f);
	CheckPoint.transform.SetScale(150, 120);
	CheckPoint.sprite.LoadImage("texture/flag.png", State::m_renderer);

	wall3.SetName("Wall3");
	wall3.transform.position.Set(-360.0f, -80.0f, 0.0f);
	wall3.transform.SetScale(10, 800);
	wall3.sprite.color = SDL_Color{ 255, 255, 255, 255 };
	wall3.sprite.LoadImage("texture/rect.png", State::m_renderer);
	wall3.sprite.color.r = wall3.sprite.color.g
		= wall3.sprite.color.b = 0X0;
	wall3.customPhysics.pOwnerTransform = &wall3.transform;
	wall3.customPhysics.bodyType = CustomPhysics::STATIC;
	wall3.customPhysics.AllocateBody(GetCustomPhysicsWorld());

	wall4.SetName("Wall4");
	wall4.transform.position.Set(100.0f, 100.0f, 0.0f);
	wall4.transform.SetScale(100, 20);
	wall4.sprite.color = SDL_Color{ 255, 255, 255, 255 };
	wall4.sprite.LoadImage("texture/rect.png", State::m_renderer);
	wall4.sprite.color.r = wall4.sprite.color.g
		= wall4.sprite.color.b = 0X0;
	wall4.customPhysics.pOwnerTransform = &wall4.transform;
	wall4.customPhysics.bodyType = CustomPhysics::STATIC;
	wall4.customPhysics.AllocateBody(GetCustomPhysicsWorld());

	wall5.SetName("Wall5");
	wall5.transform.position.Set(14000.f, 400.0f, 0.0f);
	wall5.transform.SetScale(30000, 50);
	wall5.sprite.color = SDL_Color{ 255, 255, 255, 255 };
	wall5.sprite.LoadImage("texture/rect.png", State::m_renderer);
	wall5.sprite.color.r = wall5.sprite.color.g
		= wall5.sprite.color.b = 0X0;
	wall5.customPhysics.pOwnerTransform = &wall5.transform;
	wall5.customPhysics.bodyType = CustomPhysics::STATIC;
	wall5.customPhysics.AllocateBody(GetCustomPhysicsWorld());

	PlayerHeart.SetName("PlayerHeart");
	PlayerHeart.transform.position.Set(-550.f, 260.f, 0.f);
	PlayerHeart.transform.SetScale(150, 50);
	PlayerHeart.sprite.LoadImage("texture/Lives/Lives3.png", State::m_renderer);

	CleanGauge1.SetName("CleanGauge1");
	CleanGauge1.transform.position.Set(650.f, 330.f, 0.f);
	CleanGauge1.transform.SetScale(ScaleX, 60);
	CleanGauge1.sprite.LoadImage("texture/GreenCleanGauge.png", State::m_renderer);

	CleanGauge2.SetName("CleanGauge2");
	CleanGauge2.transform.position.Set(400, 330.f, 0.f);
	CleanGauge2.transform.SetScale(500, 60);
	CleanGauge2.sprite.LoadImage("texture/CleanGauge2.png", State::m_renderer);

	iteamheart.SetName("iteamheart");
	iteamheart.transform.position.Set(1500.f, -100.f, 0.f);
	iteamheart.transform.SetScale(50, 50);
	iteamheart.sprite.LoadImage("texture/Lives.png", State::m_renderer);
    backGroundMusic.LoadMusic("sound/Ending_Hero.mp3");

	AddObject(&wall3);
	AddObject(&wall);
	AddCustomPhysicsComponent(&wall3);
	AddCustomPhysicsComponent(&wall4);
	AddCustomPhysicsComponent(&wall5);
	AddObject(&wall5);
	AddObject(&background);
	AddObject(&wall4);

    backGroundMusic.Play();
	ultrafinedust = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust, "ultrafinedust", 500.f, -500.f);

	ultrafinedust2 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust2, "ultrafinedust2", 900.f, -500.f);

	ultrafinedust3 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust3, "ultrafinedust3", 1500.f, -500.f);

	ultrafinedust4 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust4, "ultrafinedust4", 2000.f, -500.f);

	ultrafinedust5 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust5, "ultrafinedust5", 2600.f, -500.f);

	ultrafinedust6 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust6, "ultrafinedust6", 3400.f, -500.f);

	ultrafinedust7 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust7, "ultrafinedust7", 4000.f, -500.f);

	ultrafinedust8 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust8, "ultrafinedust8", 4800.f, -500.f);

	ultrafinedust9 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust9, "ultrafinedust9", 5400.f, -500.f);

	ultrafinedust10 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust10, "ultrafinedust10", 6000.f, -500.f);

	ultrafinedust11 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust11, "ultrafinedust11", 6600.f, -500.f);

	ultrafinedust12 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust12, "ultrafinedust12", 7100.f, -500.f);

	ultrafinedust13 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust13, "ultrafinedust13", 7600.f, -500.f);

	ultrafinedust14 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust14, "ultrafinedust14", 8000.f, -500.f);

	ultrafinedust15 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust15, "ultrafinedust15", 8600.f, -500.f);

	ultrafinedust16 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust16, "ultrafinedust16", 9200.f, -500.f);

	ultrafinedust17 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust17, "ultrafinedust17", 9800.f, -500.f);

	ultrafinedust18 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust18, "ultrafinedust18", 10200.f, -500.f);

	ultrafinedust19 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust19, "ultrafinedust19", 10700.f, -500.f);

	ultrafinedust20 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust20, "ultrafinedust20", 11200.f, -500.f);

	ultrafinedust21 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust21, "ultrafinedust21", 11600.f, -500.f);

	ultrafinedust22 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust22, "ultrafinedust22", 12100.f, -500.f);

	ultrafinedust23 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust23, "ultrafinedust23", 12400.f, -500.f);

	AddCustomPhysicsComponent(&man);
	AddCustomPhysicsComponent(&wall);
	AddCustomPhysicsComponent(&MiniWall10);

	AddObject(&iteamheart);

	CreateMiniwall(MiniWall1, "MiniWall1", 100, 20, 500.f, 75.f);
	CreateMiniwall(MiniWall2, "MiniWall2", 100, 20, 850.f, 50.f);
	CreateMiniwall(MiniWall3, "MiniWall3", 100, 20, 1450.f, 30.f);
	CreateMiniwall(MiniWall4, "MiniWall4", 100, 20, 1700.f, 150.f);
	CreateMiniwall(MiniWall5, "MiniWall5", 100, 20, 2000.f, 75.f);
	CreateMiniwall(MiniWall6, "MiniWall6", 100, 20, 2500.f, 75.f);
	CreateMiniwall(MiniWall7, "MiniWall7", 100, 20, 3000.f, 45.f);
	CreateMiniwall(MiniWall8, "MiniWall8", 100, 20, 3500.f, 55.f);
	CreateMiniwall(MiniWall9, "MiniWall9", 100, 20, 3800.f, 75.f);
	CreateMiniwall(MiniWall10, "MiniWall10", 100, 20, 4300.f, 100.f);
	CreateMiniwall(MiniWall11, "MiniWall11", 100, 20, 4800.f, 75.f);
	CreateMiniwall(MiniWall12, "MiniWall12", 100, 20, 5600.f, 50.f);
	CreateMiniwall(MiniWall13, "MiniWall13", 100, 20, 6000.f, 30.f);
	CreateMiniwall(MiniWall14, "MiniWall14", 100, 20, 6700.f, 150.f);
	CreateMiniwall(MiniWall15, "MiniWall15", 100, 20, 7400.f, 100.f);
	CreateMiniwall(MiniWall16, "MiniWall16", 100, 20, 8400.f, 130.f);
	CreateMiniwall(MiniWall17, "MiniWall17", 100, 20, 9300.f, 25.f);
	CreateMiniwall(MiniWall18, "MiniWall18", 100, 20, 10000.f, 75.f);
	CreateMiniwall(MiniWall19, "MiniWall19", 100, 20, 11000.f, 140.f);
	CreateMiniwall(MiniWall20, "MiniWall20", 100, 20, 12000.f, 100.f);

	AddObject(&CheckPoint);
	AddObject(&CleanGauge2);
	AddObject(&CleanGauge1);
	AddObject(&time);
	AddObject(&miss4);


	AddObject(&PlayerHeart);

	CreateShootPlayer(man, "man", 150, 120);

	CreateHudSprite(gameOverScreen, "GameOverScreen", 0, 0, 2560.f, 1920.f, "texture/GameOverScreen.png", false);

	InitializeObjects();
}
void Level4::UpdateMiniWall(class CustomBaseObject* mWall)
{
	bool collidCheck = man.customPhysics.GetVelocity().y <= 0;
	float left_Check = mWall->transform.position.x - mWall->transform.GetScale().x / 2;

	if (man.transform.position.x <= left_Check
		)
	{
		collidCheck = false;
	}


	mWall->customPhysics.ActiveGhostCollision(collidCheck);
}
CustomBaseObject& Level4::CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY)
{
	miniwall.SetName(name);
	miniwall.transform.position.Set(positionX, positionY, 0.0f);
	miniwall.transform.SetScale(scaleX, scaleY);
	miniwall.sprite.color = SDL_Color{ 255, 255, 255, 255 };
	miniwall.sprite.LoadImage("texture/rect.png", State::m_renderer);
	miniwall.sprite.color.r = miniwall.sprite.color.g
		= miniwall.sprite.color.b = 0X0;
	miniwall.customPhysics.pOwnerTransform = &miniwall.transform;
	miniwall.customPhysics.bodyType = CustomPhysics::STATIC;
	miniwall.customPhysics.AllocateBody(GetCustomPhysicsWorld());
	AddObject(&miniwall);
	AddCustomPhysicsComponent(&miniwall);
	return miniwall;
}

Object& Level4::CreateFineDust(Object& finedust, const char* name, float positionX, float positionY)
{
	finedust.SetName(name);
	finedust.transform.position.Set(positionX, positionY, 0.f);
	finedust.transform.SetScale(100, 100);
	finedust.sprite.LoadImage("texture/dust.png", State::m_renderer);
	AddObject(&finedust);
	return finedust;
}

void Level4::MoveFineDust(Object& finedust)
{
	finedust.transform.position.x -= 2;
}

void Level4::EatFineDust(Object& finedust, float positioX, float positionY)
{
	float dustCoordinateX = abs(finedust.transform.position.x - man.transform.position.x);
	float dustCoordinateY = abs(finedust.transform.position.y - man.transform.position.y);


	if (0 < dustCoordinateX &&dustCoordinateX < 100 && dustCoordinateY &&dustCoordinateY < 100)
	{
		dustCount++;
		finedust.transform.position.Set(positioX + man.transform.position.x, positionY, 0.f);
		printf("eat: %d \n", dustCount);
		printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, finedust.transform.position.y);
	}
	else if (man.transform.position.x > finedust.transform.position.x && dustCoordinateX > 330.f)
	{
		ScaleX -= 10;
		finedust.transform.position.Set(positioX + man.transform.position.x - 500, positionY, 0.f);
		CleanGauge1.transform.SetScale(ScaleX, 60);
		failDust++;
		printf("fail: %d \n", failDust);
		printf("fail findust1 \n");
	}

}

CustomBaseObject& Level4::CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY)
{
	ultraFineDust->SetName(name);
	ultraFineDust->transform.position.Set(positionX, positionY, 0.f);
	ultraFineDust->transform.SetScale(200, 200);
	ultraFineDust->sprite.LoadImage("texture/UltraFineDust.png", State::m_renderer);
	AddObject(ultraFineDust);
	AddCustomPhysicsComponent(ultraFineDust);
	return *ultraFineDust;
}


CustomBaseObject& Level4::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
{
	player.SetName(name);
	player.transform.position.Set(-350.f, -140.f, 0.f);
	player.transform.SetScale(scaleX, scaleY);
	player.transform.rotation = 0;
	player.sprite.LoadImage("texture/Picture1.png", State::m_renderer);

	player.sprite.rewindAnimation = true;
	player.sprite.activeAnimation = true;
	player.sprite.SetFrame(6);
	player.sprite.SetSpeed(12.f);

	player.customPhysics.bodyType = CustomPhysics::DYNAMIC;
	player.customPhysics.radius = (scaleX > scaleY ? scaleX : scaleY) * 0.5f;
	player.customPhysics.SetDensity(1.f);
	player.customPhysics.SetRestitution(0.f);
	player.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &player.transform);

	State::sCurrentState->AddComponentToObject(&player, eComponentTypes::Level4Controller);
	State::sCurrentState->AddCustomPhysicsComponent(&player);
	State::sCurrentState->AddObject(&player);
	return player;
}
void Level4::Update(float dt)
{
	UpdateObjects(dt);

	UpdateMiniWall(&MiniWall1);
	UpdateMiniWall(&MiniWall2);
	UpdateMiniWall(&MiniWall3);
	UpdateMiniWall(&MiniWall4);
	UpdateMiniWall(&MiniWall5);
	UpdateMiniWall(&MiniWall6);
	UpdateMiniWall(&MiniWall7);
	UpdateMiniWall(&MiniWall8);
	UpdateMiniWall(&MiniWall9);
	UpdateMiniWall(&MiniWall10);
	UpdateMiniWall(&MiniWall11);
	UpdateMiniWall(&MiniWall12);
	UpdateMiniWall(&MiniWall13);
	UpdateMiniWall(&MiniWall14);
	UpdateMiniWall(&MiniWall15);
	UpdateMiniWall(&MiniWall16);
	UpdateMiniWall(&MiniWall17);
	UpdateMiniWall(&MiniWall18);
	UpdateMiniWall(&MiniWall19);
	UpdateMiniWall(&MiniWall20);

	UpdateMiniWall(&wall4);

	{
		timecount+=dt;
		if(timecount >= 3.f)
		{
			time.sprite.Free();
			time.transform.position.y = -500;
			countt = 1;
		}
	}

	if (CleanGauge1.transform.GetScale().x < 50 || heartCount == 0)
	{
		mState = eDemoTopdownPlayerState::GameOver;
		mTimer = 0;
		if (mState == eDemoTopdownPlayerState::GameOver)
		{
			gameOverScreen.sprite.isVisible = true;
		}
	}

	if (man.transform.position.x > CheckPoint.transform.position.x)
	{
        printf("failDust:%d", failDust);
		if (failDust > 100)
		{
			State::m_game->Change(LV_BadEnding);
		}
		else
		{
			State::m_game->Change(LV_HappyEnding);
		}
	}

	if (CleanGauge1.transform.GetScale().x < 50 || heartCount == 0)
	{
		mState = eDemoTopdownPlayerState::GameOver;
		mTimer = 0;
		if (mState == eDemoTopdownPlayerState::GameOver)
		{
			gameOverScreen.sprite.isVisible = true;
		}
	}

	float betweenCoordinate = abs(ultrafinedust->transform.position.x - man.transform.position.x);
	float betweenCoordinate2 = abs(ultrafinedust2->transform.position.x - man.transform.position.x);
	float betweenCoordinate3 = abs(ultrafinedust3->transform.position.x - man.transform.position.x);
	float betweenCoordinate4 = abs(ultrafinedust4->transform.position.x - man.transform.position.x);
	float betweenCoordinate5 = abs(ultrafinedust5->transform.position.x - man.transform.position.x);
	float betweenCoordinate6 = abs(ultrafinedust6->transform.position.x - man.transform.position.x);
	float betweenCoordinate7 = abs(ultrafinedust7->transform.position.x - man.transform.position.x);
	float betweenCoordinate8 = abs(ultrafinedust8->transform.position.x - man.transform.position.x);
	float betweenCoordinate9 = abs(ultrafinedust9->transform.position.x - man.transform.position.x);
	float betweenCoordinate10 = abs(ultrafinedust10->transform.position.x - man.transform.position.x);
	float betweenCoordinate11 = abs(ultrafinedust11->transform.position.x - man.transform.position.x);
	float betweenCoordinate12 = abs(ultrafinedust12->transform.position.x - man.transform.position.x);
	float betweenCoordinate13 = abs(ultrafinedust13->transform.position.x - man.transform.position.x);
	float betweenCoordinate14 = abs(ultrafinedust14->transform.position.x - man.transform.position.x);
	float betweenCoordinate15 = abs(ultrafinedust15->transform.position.x - man.transform.position.x);
	float betweenCoordinate16 = abs(ultrafinedust16->transform.position.x - man.transform.position.x);
	float betweenCoordinate17 = abs(ultrafinedust17->transform.position.x - man.transform.position.x);
	float betweenCoordinate18 = abs(ultrafinedust18->transform.position.x - man.transform.position.x);
	float betweenCoordinate19 = abs(ultrafinedust19->transform.position.x - man.transform.position.x);
	float betweenCoordinate20 = abs(ultrafinedust20->transform.position.x - man.transform.position.x);
	float betweenCoordinate21 = abs(ultrafinedust21->transform.position.x - man.transform.position.x);
	float betweenCoordinate22 = abs(ultrafinedust22->transform.position.x - man.transform.position.x);
	float betweenCoordinate23 = abs(ultrafinedust23->transform.position.x - man.transform.position.x);

	{
		camera.position.x = man.transform.position.x + 350.f;
		CleanGauge1.transform.position.x = man.transform.position.x - 300;
		CleanGauge2.transform.position.x = man.transform.position.x - 50;
		background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
		PlayerHeart.transform.position.x = man.transform.position.x - 200;

		if (characterState4)
		{
			miss4.transform.position.Set(man.transform.position.x, man.transform.position.y + 100, 0.f);
		}
	}

	if (State::m_input->IsPressed((SDL_SCANCODE_A)))
	{
		camera.position.x = man.transform.position.x + 350.f;
		CleanGauge1.transform.position.x = man.transform.position.x - 300;
		CleanGauge2.transform.position.x = man.transform.position.x - 50;
		background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
		PlayerHeart.transform.position.x = man.transform.position.x - 200;
	}

	if (0 < betweenCoordinate &&betweenCoordinate < 500)
	{
		ultrafinedust->transform.position.Set(500.f, -80.f, 0.f);
	}

	if (0 < betweenCoordinate2 &&betweenCoordinate2 < 500)
	{
		ultrafinedust2->transform.position.Set(900.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate3 &&betweenCoordinate3 < 500)
	{
		ultrafinedust3->transform.position.Set(1500.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate4 &&betweenCoordinate4 < 500)
	{
		ultrafinedust4->transform.position.Set(2000.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate5 &&betweenCoordinate5 < 500)
	{
		ultrafinedust5->transform.position.Set(2600.f, 120.f, 0.f);
	}

	if (0 < betweenCoordinate6 &&betweenCoordinate6 < 500)
	{
		ultrafinedust6->transform.position.Set(3400.f, -80.f, 0.f);
	}

	if (0 < betweenCoordinate7 &&betweenCoordinate7 < 500)
	{
		ultrafinedust7->transform.position.Set(4000.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate8 &&betweenCoordinate8 < 500)
	{
		ultrafinedust8->transform.position.Set(4800.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate9 &&betweenCoordinate9 < 500)
	{
		ultrafinedust9->transform.position.Set(5400.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate10 &&betweenCoordinate10 < 500)
	{
		ultrafinedust10->transform.position.Set(6000.f, 120.f, 0.f);
	}

	if (0 < betweenCoordinate11 &&betweenCoordinate11 < 500)
	{
		ultrafinedust11->transform.position.Set(6600.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate12 &&betweenCoordinate12 < 500)
	{
		ultrafinedust12->transform.position.Set(7100.f, 50.f, 0.f);
	}

	if (0 < betweenCoordinate13 && betweenCoordinate13 < 500)
	{
		ultrafinedust13->transform.position.Set(7600.f, 100.f, 0.f);
	}

	if (0 < betweenCoordinate14 &&betweenCoordinate14 < 500)
	{
		ultrafinedust14->transform.position.Set(8000.f, 120.f, 0.f);
	}

	if (0 < betweenCoordinate15 &&betweenCoordinate15 < 500)
	{
		ultrafinedust15->transform.position.Set(8600.f, 200.f, 0.f);
	}

	if (0 < betweenCoordinate16 &&betweenCoordinate16 < 500)
	{
		ultrafinedust16->transform.position.Set(9200.f, 120.f, 0.f);
	}

	if (0 < betweenCoordinate17 &&betweenCoordinate17 < 500)
	{
		ultrafinedust17->transform.position.Set(9800.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate18 &&betweenCoordinate18 < 500)
	{
		ultrafinedust18->transform.position.Set(10200.f, 120.f, 0.f);
	}

	if (0 < betweenCoordinate19 &&betweenCoordinate19 < 500)
	{
		ultrafinedust19->transform.position.Set(10700.f, 30.f, 0.f);
	}

	if (0 < betweenCoordinate20 &&betweenCoordinate20 < 500)
	{
		ultrafinedust20->transform.position.Set(11200.f, 100.f, 0.f);
	}

	if (0 < betweenCoordinate21 &&betweenCoordinate21 < 500)
	{
		ultrafinedust21->transform.position.Set(11600.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate22 &&betweenCoordinate22 < 500)
	{
		ultrafinedust22->transform.position.Set(12100.f, 120.f, 0.f);
	}

	if (0 < betweenCoordinate23 &&betweenCoordinate23 < 500)
	{
		ultrafinedust23->transform.position.Set(12400.f, 120.f, 0.f);
	}

	float heartX = abs(iteamheart.transform.position.x - man.transform.position.x);
	float heartY = abs(iteamheart.transform.position.y - man.transform.position.y);

	if (0 < heartX &&heartX < 100 && heartY &&heartY < 100)
	{
		iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
		if (heartCount < 3)
		{
			heartCount++;
		}
	}
	else if (man.transform.position.x > iteamheart.transform.position.x && heartX > 330.f)
	{
		iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
	}

	switch (heartCount)
	{
	case 0:
		PlayerHeart.sprite.Free();
		PlayerHeart.sprite.LoadImage("texture/Lives/Lives0.png", State::m_renderer);
		break;
	case 1:
		PlayerHeart.sprite.Free();
		PlayerHeart.sprite.LoadImage("texture/Lives/Lives1.png", State::m_renderer);
		break;
	case 2:
		PlayerHeart.sprite.Free();
		PlayerHeart.sprite.LoadImage("texture/Lives/Lives2.png", State::m_renderer);
		break;
	case 3:
		PlayerHeart.sprite.Free();
		PlayerHeart.sprite.LoadImage("texture/Lives/Lives3.png", State::m_renderer);
		break;
	default:
		break;
	}

	getbullet();

	if (characterState4)
	{

		s_count4 += dt;
		if (s_count4 > 2.f)
		{
			miss4.transform.position.Set(0.f, -500.f, 0.f);
			s_count4 = 0;
			characterState4 = false;
		}

	}

	if (State::m_input->IsPressed((SDL_SCANCODE_M)))
	{
		heartCount = 3;
		dustCount = 0;
		State::m_game->Change(LV_MainMenu);
		State::m_game->Change(LV_MainMenu);
	}

	UpdatePhysics(dt);
	UpdateCustomPhysics(dt);
	Render(dt);
}

void Level4::UpdateUltraFineDust(CustomBaseObject* mDust)
{
	if (mDust != nullptr)
	{
		float left_ultra = mDust->transform.position.x - mDust->transform.GetScale().x / 2;
		float right_ultra = mDust->transform.position.x + mDust->transform.GetScale().x / 2;
		float up_ultra = mDust->transform.position.y + mDust->transform.GetScale().y / 2;
		float down_ultra = mDust->transform.position.y - mDust->transform.GetScale().y / 2;
		if (toShootBullet != nullptr)
		{
			if (toShootBullet->transform.position.x >= left_ultra &&
				toShootBullet->transform.position.x <= right_ultra &&
				toShootBullet->transform.position.y >= down_ultra &&
				toShootBullet->transform.position.y <= up_ultra)
			{
				mDust->sprite.Free();
				mDust->sprite.LoadImage("texture/dust.png", m_renderer);
				toShootBullet = nullptr;
				red++;
				mDust->isRed = false;
			}
		}
		if (mDust->isRed)
		{
			if (man.transform.position.x >= left_ultra &&
				man.transform.position.x <= right_ultra &&
				man.transform.position.y >= down_ultra &&
				man.transform.position.y <= up_ultra)
			{
				mDust->sprite.color.a = 0;
				heartCount--;
				ScaleX-=20;
				CleanGauge1.transform.SetScale(ScaleX, 60);

				characterState4 = true;
				mDust->isRed = false;
			}
			else if (man.transform.position.x > right_ultra)
			{
				mDust->isRed = false;
				ScaleX -= 20;
				CleanGauge1.transform.SetScale(ScaleX, 60);

				heartCount--;
				characterState4 = true;
			}

		}
		float distanceUltraX = abs(mDust->transform.position.x - man.transform.position.x);
		float distanceUltraY = abs(mDust->transform.position.y - man.transform.position.y);

		if (red > 0)
		{
			if (0 < distanceUltraX && distanceUltraX < 100 && 0 < distanceUltraY &&distanceUltraY < 100)
			{
				mDust->transform.position.Set(0, -500, 0.f);
				dustCount++;
				red = 0;
				mDust->isDead = true;
			}
			else if (man.transform.position.x > mDust->transform.position.x && distanceUltraX < 330.f && distanceUltraY < 100.f)
			{
				ScaleX -= 10;
				
				mDust->transform.position.Set(0, -500, 0.f);
				CleanGauge1.transform.SetScale(ScaleX, 60);
				failDust++;
				red = 0;
				return getbullet();
			}
		}
		else if (man.transform.position.x > mDust->transform.position.x&& distanceUltraX < 330.f && distanceUltraY < 100.f)
		{
			ScaleX -= 20;
			mDust->transform.position.Set(0, -500, 0.f);
			CleanGauge1.transform.SetScale(ScaleX, 60);
			failDust++;
			red = 0;
			return getbullet();
		}
	}
}
void Level4::getbullet()
{
	UpdateUltraFineDust(ultrafinedust);
	UpdateUltraFineDust(ultrafinedust2);
	UpdateUltraFineDust(ultrafinedust3);
	UpdateUltraFineDust(ultrafinedust4);
	UpdateUltraFineDust(ultrafinedust5);
	UpdateUltraFineDust(ultrafinedust6);
	UpdateUltraFineDust(ultrafinedust7);
	UpdateUltraFineDust(ultrafinedust8);
	UpdateUltraFineDust(ultrafinedust9);
	UpdateUltraFineDust(ultrafinedust10);
	UpdateUltraFineDust(ultrafinedust11);
	UpdateUltraFineDust(ultrafinedust12);
	UpdateUltraFineDust(ultrafinedust13);
	UpdateUltraFineDust(ultrafinedust14);
	UpdateUltraFineDust(ultrafinedust15);
	UpdateUltraFineDust(ultrafinedust16);
	UpdateUltraFineDust(ultrafinedust17);
	UpdateUltraFineDust(ultrafinedust18);
	UpdateUltraFineDust(ultrafinedust19);
	UpdateUltraFineDust(ultrafinedust20);
	UpdateUltraFineDust(ultrafinedust21);
	UpdateUltraFineDust(ultrafinedust22);
	UpdateUltraFineDust(ultrafinedust23);
}


void Level4::Close()
{
	RemoveObject(ultrafinedust);
	RemoveObject(ultrafinedust2);
	RemoveObject(ultrafinedust3);
	RemoveObject(ultrafinedust4);
	RemoveObject(ultrafinedust5);
	RemoveObject(ultrafinedust6);
	RemoveObject(ultrafinedust7);
	RemoveObject(ultrafinedust8);
	RemoveObject(ultrafinedust9);
	RemoveObject(ultrafinedust10);
	RemoveObject(ultrafinedust11);
	RemoveObject(ultrafinedust12);
	RemoveObject(ultrafinedust13);
	RemoveObject(ultrafinedust14);
	RemoveObject(ultrafinedust15);
	RemoveObject(ultrafinedust16);
	RemoveObject(ultrafinedust17);
	RemoveObject(ultrafinedust18);
	RemoveObject(ultrafinedust19);
	RemoveObject(ultrafinedust20);
	RemoveObject(ultrafinedust21);
	RemoveObject(ultrafinedust22);
	RemoveObject(ultrafinedust23);

	ClearBaseState();
}

