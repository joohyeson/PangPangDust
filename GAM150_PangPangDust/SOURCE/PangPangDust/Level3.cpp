/******************************************************************************/
/*!
\file  Level3.cpp
\author Lee Ui Jin
\par    email: digipen.uijin@gmail.com
\date   2019/06/11

stage 3
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include <SDL2/SDL.h>
#include <engine/State.h>
#include "Level3.h"
#include <ctime>
#include "ComponentTypes.h"
#include "ShootBulletController.h"

extern int bullet_count;

 int heartCount3 = 3;
 int level3RedCount = 0;
 int dustCount3 = 0;
extern int failDust;
extern float ScaleX;

float tCount1 = 0;
float n_count = 0;
float n_count2 = 0;
float g_count = 0;
float s_count3 = 0;
bool characterState3 = false;

 bool check2 = false;
bool negativeCheck;
bool negativeCheck2 = false;
bool goggleCheck = false;

CustomBaseObject& Level3::CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
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

void Level3::Initialize()
{
	bullet_count = 3;
	State::sCurrentState = this;
	State::m_pCamera = &camera;

	isEmptyLoaded1 = false;
	isEmptyLoaded2 = false;
	isEmptyLoaded3 = false;
	isEmptyLoaded4 = false;
	isEmptyLoaded5 = false;
	isEmptyLoaded6 = false;
	isEmptyLoaded7 = false;
	isEmptyLoaded8 = false;
	isEmptyLoaded9 = false;
	isEmptyLoaded10 = false;

	camera.position.Set(0, 0, 0);

	m_useBuiltInPhysics = false;
	const b2Vec2 gravity(0.0f, -25.8f);
	SetCustomPhysicsWorld(gravity);
	background.SetName("Start");
	background.transform.SetScale(State::m_width, State::m_height);
	background.sprite.LoadImage("texture/backgroundss.png", State::m_renderer);
	background.transform.position.Set(0, 0, 0);
    background.sprite.SetFrame(4);
    background.sprite.SetSpeed(3.f);
    background.sprite.activeAnimation = true;

    background.sound.LoadSound("sound/Ending_Hero.mp3");
    background.sound.SetVolume(80);

	BulletCountImage.SetName("BulletCountImage");
	BulletCountImage.transform.position.Set(500, 317, 0);
	BulletCountImage.transform.SetScale(200, 80);
	BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb0.png", State::m_renderer);

	miss3.SetName("MISS3");
	miss3.transform.position.Set(0, -500, 0.f);
	miss3.transform.SetScale(150, 50);
	miss3.sprite.LoadImage("texture/MISS.png", State::m_renderer);

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

	CheckPoint.SetName("CheckPoint");
	CheckPoint.transform.position.Set(7500.f, -200.f, 0.f);
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

	BulletGauge.SetName("BulletGauge");
	BulletGauge.transform.position.Set(435, 317, 0);
	BulletGauge.transform.SetScale(400, 80);
	BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge0.png", State::m_renderer);

	iteamheart.SetName("iteamheart");
	iteamheart.transform.position.Set(1500.f, -100.f, 0.f);
	iteamheart.transform.SetScale(50, 50);
	iteamheart.sprite.LoadImage("texture/Lives.png", State::m_renderer);

	itemnagative.SetName("itemnagative");
	itemnagative.transform.position.Set(2500.f, -100.f, 0.f);
	itemnagative.transform.SetScale(100, 100);
	itemnagative.sprite.LoadImage("texture/negative.png", State::m_renderer);
    itemnagative.sound.LoadSound("sound/mud.ogg");
    itemnagative.sound.SetVolume(300);

	itemnagative2.SetName("itemnagative2");
	itemnagative2.transform.position.Set(5500.f, -100.f, 0.f);
	itemnagative2.transform.SetScale(100, 100);
	itemnagative2.sprite.LoadImage("texture/negative.png", State::m_renderer);
    itemnagative2.sound.LoadSound("sound/mud.ogg");
    itemnagative2.sound.SetVolume(300);

	robot_vacuum.SetName("robot_vacuum");
	robot_vacuum.transform.position.Set(2000.f, -300.f, 0.f);
	robot_vacuum.transform.SetScale(120, 120);
	robot_vacuum.sprite.LoadImage("texture/robot.png", State::m_renderer);

	goggles.SetName("goggles");
	goggles.transform.position.Set(200.f, -200.f, 0.f);
	goggles.transform.SetScale(120, 120);
	goggles.sprite.LoadImage("texture/negative.png", State::m_renderer);

    eatSound.sound.LoadSound("sound/vaccum.wav");
    eatSound.sound.SetVolume(80);

	potion.SetName("potion");
	potion.transform.position.Set(1500.f, -200.f, 0.f);
	potion.transform.SetScale(120, 120);
	potion.sprite.LoadImage("texture/potion.png", State::m_renderer);
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
	CreateUltraFineDust(ultrafinedust, "ultrafinedust", 700.f, -500.f);

	ultrafinedust2 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust2, "ultrafinedust2", 1000.f, -500.f);

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

	AddCustomPhysicsComponent(&man);
	AddCustomPhysicsComponent(&wall);
	AddCustomPhysicsComponent(&MiniWall10);
	AddObject(&BulletCountImage);

	AddObject(&iteamheart);

	AddObject(&robot_vacuum);
	AddObject(&goggles);
	AddObject(&potion);

	CreateFineDust(FineDust1, "FineDust1", 500.f, 0.f);
	CreateFineDust(FineDust2, "FineDust2", 1000.f, -70.f);
	CreateFineDust(FineDust3, "FineDust3", 800.f, -120.f);
	CreateFineDust(FineDust4, "FineDust4", 700.f, 170.f);
	CreateFineDust(FineDust5, "FineDust5", 900.f, -220.f);
	CreateFineDust(FineDust6, "FineDust6", 600.f, 100.f);
	CreateFineDust(FineDust7, "FineDust7", 1200.f, 70.f);
	CreateFineDust(FineDust8, "FineDust8", 1500.f, 150.f);
	CreateFineDust(FineDust9, "FineDust9", 850.f, 210.f);
	CreateFineDust(FineDust10, "FineDust10", 1300.f, 270.f);

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

	AddObject(&CheckPoint);
	AddObject(&CleanGauge2);
	AddObject(&CleanGauge1);
	AddObject(&miss3);

	AddObject(&BulletGauge);
	AddObject(&PlayerHeart);
	AddObject(&itemnagative);
	AddObject(&itemnagative2);

	CreateShootPlayer(man, "man", 150, 120);

	//CreateHudSprite(gameOverScreen, "GameOverScreen", 0, 0, 2560.f, 1920.f, "texture/GameOverScreen.png", false);

	InitializeObjects();
}
void Level3::UpdateMiniWall(class CustomBaseObject* mWall)
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
CustomBaseObject& Level3::CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY)
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

Object& Level3::CreateFineDust(Object& finedust, const char* name, float positionX, float positionY)
{
	finedust.SetName(name);
	finedust.transform.position.Set(positionX, positionY, 0.f);
	finedust.transform.SetScale(100, 100);
	finedust.sprite.LoadImage("texture/dust.png", State::m_renderer);
	AddObject(&finedust);
	return finedust;
}

void Level3::MoveFineDust(Object& finedust)
{
	finedust.transform.position.x -= 2;
}

void Level3::EatFineDust(Object& finedust, float positioX, float positionY)
{
	float dustCoordinateX = abs(finedust.transform.position.x - man.transform.position.x);
	float dustCoordinateY =abs(finedust.transform.position.y - man.transform.position.y);

	if (0 < dustCoordinateX &&dustCoordinateX < 100 && dustCoordinateY &&dustCoordinateY < 100)
	{
		dustCount3++;
        eatSound.sound.Play();
		finedust.transform.position.Set(positioX + man.transform.position.x, positionY, 0.f);
		printf("eat: %d \n", dustCount3);
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

	if (check2)
	{
		if (0 < abs(robot_vacuum.transform.position.x - finedust.transform.position.x) && abs(robot_vacuum.transform.position.x - finedust.transform.position.x) < 300
			&& abs(robot_vacuum.transform.position.y - finedust.transform.position.y) && abs(robot_vacuum.transform.position.y - finedust.transform.position.y) < 200)
		{
			dustCount3++;
			finedust.transform.position.Set(1500.f + man.transform.position.x - 500, positionY, 0.f);

			printf("eat: %d \n", dustCount3);
			printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, FineDust1.transform.position.y);
		}
		else if (finedust.transform.position.y < 0 && (robot_vacuum.transform.position.x > finedust.transform.position.x && abs(robot_vacuum.transform.position.x - finedust.transform.position.x) > 330.f))
		{
			dustCount3++;
			finedust.transform.position.Set(1500.f + man.transform.position.x - 500, positionY, 0.f);

			printf("eat: %d \n", dustCount3);
			printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, finedust.transform.position.y);
		}
	}
}

CustomBaseObject& Level3::CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY)
{
	ultraFineDust->SetName(name);
	ultraFineDust->transform.position.Set(positionX, positionY, 0.f);
	ultraFineDust->transform.SetScale(200, 200);
	ultraFineDust->sprite.LoadImage("texture/UltraFineDust.png", State::m_renderer);
	AddObject(ultraFineDust);
	AddCustomPhysicsComponent(ultraFineDust);
	return *ultraFineDust;
}


CustomBaseObject& Level3::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
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

	State::sCurrentState->AddComponentToObject(&player, eComponentTypes::ShootBulletController);
	State::sCurrentState->AddCustomPhysicsComponent(&player);
	State::sCurrentState->AddObject(&player);
	return player;
}
void Level3::Update(float dt)
{
	UpdateObjects(dt);
	float d_x = abs(robot_vacuum.transform.position.x - man.transform.position.x);
	float d_y = abs(robot_vacuum.transform.position.y - man.transform.position.y);

	float abs_potion_x = abs(potion.transform.position.x - man.transform.position.x);
	float abs_potion_y = abs(potion.transform.position.y - man.transform.position.y);

    static int checkFail = 1;
	if (0 < abs_potion_x && abs_potion_x < 50 && abs_potion_y && abs_potion_y < 50)
	{
        if(checkFail==1)
        {
            failDust -= 10;
            checkFail = 0;
        }
        
		if (ScaleX > 970)
		{
			ScaleX = 1000;
		}
		else
		{
			ScaleX += 30;
		}
		potion.sprite.Free();
		printf("%f", ScaleX);
	}

	if (0 < d_x && d_x < 250 && d_y && d_y < 80)
	{
		robot_vacuum.transform.SetScale(300, 300);
		robot_vacuum.transform.position.Set(2000.f, -250.f, 0.f);
		check2 = true;
	}
	if (check2)
	{
		tCount1 += dt;
		if (tCount1 > 5.f)
		{
			check2 = false;
			robot_vacuum.transform.position.Set(0, 0, 0);
			robot_vacuum.transform.SetScale(0, 0);

		}
		robot_vacuum.transform.position.x = man.transform.position.x + 100;
	}

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
	UpdateMiniWall(&wall4);

	float negativeX = abs(itemnagative.transform.position.x - man.transform.position.x);
	float negativeY = abs(itemnagative.transform.position.y - man.transform.position.y);


	if (0 < negativeX &&negativeX < 100 && negativeY &&negativeY < 100)
	{
		itemnagative.transform.SetScale(1280, 720);
		negativeCheck = true;
		itemnagative.sprite.LoadImage("texture/paint.png", State::m_renderer);
                ControlAudios();
	}

	if (negativeCheck)
	{
		n_count += dt;

		if (n_count > 5.f)
		{
			printf("time :%f\n", n_count);
			itemnagative.transform.SetScale(0, 0);
			itemnagative.transform.position.Set(-500, -500, 0);
			negativeCheck = false;
                        ControlAudios();
		}
	}

	float negative2X = abs(itemnagative2.transform.position.x - man.transform.position.x);
	float negative2Y = abs(itemnagative2.transform.position.y - man.transform.position.y);

	if (0 < negative2X &&negative2X < 100 && negative2Y &&negative2Y < 100)
	{
		itemnagative2.transform.SetScale(1280, 720);
		negativeCheck2 = true;
		itemnagative2.sprite.LoadImage("texture/paint.png", State::m_renderer);
                ControlAudios();
	}
	if (negativeCheck2)
	{
		n_count2 += dt;

		if (n_count2 > 5.f)
		{
			printf("time :%f\n", n_count2);
			itemnagative2.transform.SetScale(0, 0);
			itemnagative2.transform.position.Set(-500, -500, 0);
			negativeCheck2 = false;
                        ControlAudios();
		}
	}

	float goggleX = abs(goggles.transform.position.x - man.transform.position.x);
	float goggleY = abs(goggles.transform.position.y - man.transform.position.y);


	if (0 < goggleX &&goggleX < 100 && goggleY &&goggleY < 100)
	{
		goggles.transform.position.Set(-500, 0, 0);
		goggleCheck = true;
	}

	if (goggleCheck)
	{
		g_count += dt;
                ControlAudios();
		if (g_count > 5.f)
		{
			g_count = 0.f;
			printf("time :%f\n", g_count);
			goggles.transform.position.Set(0, -500.f, 0);
			goggleCheck = false;
			afterCount = true;
                        ControlAudios();

		}
	}

	if (man.transform.position.x > CheckPoint.transform.position.x)
	{
		State::m_game->Change(LV_Level4);
	}

	if (CleanGauge1.transform.GetScale().x < 50 || heartCount3 == 0)
	{
		mState = eDemoTopdownPlayerState::GameOver;
		mTimer = 0;
		if (mState == eDemoTopdownPlayerState::GameOver)
		{
            State::m_game->Change(LV_GameOver);
			//gameOverScreen.sprite.isVisible = true;
		}
	}

	if (CleanGauge1.transform.GetScale().x < 50 || heartCount3 == 0)
	{
		mState = eDemoTopdownPlayerState::GameOver;
		mTimer = 0;
		if (mState == eDemoTopdownPlayerState::GameOver)
		{
            State::m_game->Change(LV_GameOver);
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


	{
		camera.position.x = man.transform.position.x + 350.f;
		CleanGauge1.transform.position.x = man.transform.position.x - 300;
		CleanGauge2.transform.position.x = man.transform.position.x - 50;
		background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
		BulletGauge.transform.position.x = man.transform.position.x + 785;
		BulletCountImage.transform.position.x = man.transform.position.x + 375;
		PlayerHeart.transform.position.x = man.transform.position.x - 200;
		if (negativeCheck)
		{
			itemnagative.transform.position.x = man.transform.position.x + 350;
			itemnagative.transform.position.y = 0;
			itemnagative.transform.position.z = 500;
		}
		if (negativeCheck2)
		{
			itemnagative2.transform.position.x = man.transform.position.x + 350;
			itemnagative2.transform.position.y = 0;
			itemnagative2.transform.position.z = 500;
		}
		if (characterState3)
		{
			miss3.transform.position.Set(man.transform.position.x, man.transform.position.y + 100, 0.f);
		}
	}

	if (State::m_input->IsPressed((SDL_SCANCODE_A)))
	{
		camera.position.x = man.transform.position.x + 350.f;
		CleanGauge1.transform.position.x = man.transform.position.x - 300;
		CleanGauge2.transform.position.x = man.transform.position.x - 50;
		background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
		BulletGauge.transform.position.x = man.transform.position.x + 785;
		BulletCountImage.transform.position.x = man.transform.position.x + 375;
		PlayerHeart.transform.position.x = man.transform.position.x - 200;
	}

	if (goggleCheck)
	{
		if (0 < betweenCoordinate &&betweenCoordinate < 1500)
		{
			if (!isEmptyLoaded1)
			{
				ultrafinedust->sprite.Free();
				ultrafinedust->sprite.LoadImage("texture/empty.png", State::m_renderer);
				ultrafinedust->transform.position.Set(700.f, -80.f, 0.f);
				isEmptyLoaded1 = true;
			}
			if (ultrafinedust->isRed)
			{
				if (betweenCoordinate < 250 && !ultra1)
				{
					ultrafinedust->sprite.Free();
					ultrafinedust->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra1 = true;
				}
			}

		}


		if (0 < betweenCoordinate2 &&betweenCoordinate2 < 1500)
		{
			if (!isEmptyLoaded2)
			{
				ultrafinedust2->sprite.Free();
				ultrafinedust2->sprite.LoadImage("texture/empty.png", State::m_renderer);
				ultrafinedust2->transform.position.Set(1000.f, 150.f, 0.f);
				isEmptyLoaded2 = true;
			}
			if (ultrafinedust2->isRed)
			{
				if (betweenCoordinate2 < 250 && !ultra2)
				{
					ultrafinedust2->sprite.Free();
					ultrafinedust2->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra2 = true;
				}
			}

		}


		if (0 < betweenCoordinate3 &&betweenCoordinate3 < 1500)
		{
			if (!isEmptyLoaded3)
			{
				ultrafinedust3->sprite.Free();
				ultrafinedust3->sprite.LoadImage("texture/empty.png", State::m_renderer);
				ultrafinedust3->transform.position.Set(1500.f, 170.f, 0.f);
				isEmptyLoaded3 = true;
			}
			if (ultrafinedust3->isRed)
			{
				if (betweenCoordinate3 < 250 && !ultra3)
				{
					ultrafinedust3->sprite.Free();
					ultrafinedust3->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra3 = true;
				}
			}

		}


		if (0 < betweenCoordinate4 &&betweenCoordinate4 < 1500)
		{
			if (!isEmptyLoaded4)
			{
				ultrafinedust4->sprite.Free();
				ultrafinedust4->sprite.LoadImage("texture/empty.png", State::m_renderer);
				ultrafinedust4->transform.position.Set(2000.f, 150.f, 0.f);
				isEmptyLoaded4 = true;
			}
			if (ultrafinedust4->isRed)
			{
				if (betweenCoordinate4 < 250 && !ultra4)
				{
					ultrafinedust4->sprite.Free();
					ultrafinedust4->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra4 = true;
				}
			}

		}

		if (0 < betweenCoordinate5 &&betweenCoordinate5 < 1500)
		{
			if (!isEmptyLoaded5)
			{
				ultrafinedust5->sprite.Free();
				ultrafinedust5->sprite.LoadImage("texture/empty.png", State::m_renderer);

				ultrafinedust5->transform.position.Set(2600.f, 120.f, 0.f);
				isEmptyLoaded5 = true;
			}
			if (ultrafinedust5->isRed)
			{
				if (betweenCoordinate5 < 250 && !ultra5)
				{
					ultrafinedust5->sprite.Free();
					ultrafinedust5->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra5 = true;
				}
			}

		}


		if (0 < betweenCoordinate6 &&betweenCoordinate6 < 1500)
		{
			if (!isEmptyLoaded6)
			{
				ultrafinedust6->sprite.Free();
				ultrafinedust6->sprite.LoadImage("texture/empty.png", State::m_renderer);

				ultrafinedust6->transform.position.Set(3400.f, -80.f, 0.f);
				isEmptyLoaded6 = true;
			}
			if (!ultrafinedust6->isRed)
			{
				if (betweenCoordinate6 < 250 && !ultra6)
				{
					ultrafinedust6->sprite.Free();
					ultrafinedust6->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra6 = true;
				}

			}

		}

		if (0 < betweenCoordinate7 &&betweenCoordinate7 < 1500)
		{
			if (!isEmptyLoaded7)
			{
				ultrafinedust7->sprite.Free();
				ultrafinedust7->sprite.LoadImage("texture/empty.png", State::m_renderer);

				ultrafinedust7->transform.position.Set(4000.f, 150.f, 0.f);
				isEmptyLoaded7 = true;
			}
			if (ultrafinedust7->isRed)
			{
				if (betweenCoordinate7 < 250 && !ultra7)
				{
					ultrafinedust7->sprite.Free();
					ultrafinedust7->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra7 = true;
				}
			}

		}


		if (0 < betweenCoordinate8 &&betweenCoordinate8 < 1500)
		{
			if (!isEmptyLoaded8)
			{
				ultrafinedust8->sprite.Free();
				ultrafinedust8->sprite.LoadImage("texture/empty.png", State::m_renderer);

				ultrafinedust8->transform.position.Set(4800.f, 170.f, 0.f);
				isEmptyLoaded8 = true;
			}
			if (ultrafinedust8->isRed)
			{
				if (betweenCoordinate8 < 250 && !ultra8)
				{
					ultrafinedust8->sprite.Free();
					ultrafinedust8->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra8 = true;
				}
			}


		}


		if (0 < betweenCoordinate9 &&betweenCoordinate9 < 1500)
		{
			if (!isEmptyLoaded9)
			{

				ultrafinedust9->sprite.Free();
				ultrafinedust9->sprite.LoadImage("texture/empty.png", State::m_renderer);
				ultrafinedust9->transform.position.Set(5400.f, 150.f, 0.f);

				isEmptyLoaded9 = true;
			}
			if (ultrafinedust9->isRed)
			{
				if (betweenCoordinate9 < 250 && !ultra9)
				{
					ultrafinedust9->sprite.Free();
					ultrafinedust9->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra9 = true;
				}
			}

		}

		if (0 < betweenCoordinate10 &&betweenCoordinate10 < 1500)
		{
			if (!isEmptyLoaded10)
			{
				ultrafinedust10->sprite.Free();
				ultrafinedust10->sprite.LoadImage("texture/empty.png", State::m_renderer);
				ultrafinedust10->transform.position.Set(6000.f, 120.f, 0.f);
				isEmptyLoaded10 = true;
			}
			if (ultrafinedust10->isRed)
			{
				if (betweenCoordinate10 < 250 && !ultra10)
				{
					ultrafinedust10->sprite.Free();
					ultrafinedust10->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
					ultra10 = true;
				}
			}

		}


	}
	else if (!goggleCheck)
	{

		if (afterCount)
		{
			ultrafinedust->transform.position.y = -500;
			ultrafinedust2->transform.position.y = -500;
			ultrafinedust3->transform.position.y = -500;
			ultrafinedust4->transform.position.y = -500;
			ultrafinedust5->transform.position.y = -500;
			ultrafinedust6->transform.position.y = -500;
			ultrafinedust7->transform.position.y = -500;
			ultrafinedust8->transform.position.y = -500;
			ultrafinedust9->transform.position.y = -500;
			ultrafinedust10->transform.position.y = -500;

			ultrafinedust->sprite.Free();
			ultrafinedust2->sprite.Free();
			ultrafinedust3->sprite.Free();
			ultrafinedust4->sprite.Free();
			ultrafinedust5->sprite.Free();
			ultrafinedust6->sprite.Free();
			ultrafinedust7->sprite.Free();
			ultrafinedust8->sprite.Free();
			ultrafinedust9->sprite.Free();
			ultrafinedust10->sprite.Free();

			ultrafinedust->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust2->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust3->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust4->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust5->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust6->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust7->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust8->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust9->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);
			ultrafinedust10->sprite.LoadImage("texture/ultraFineDust.png", State::m_renderer);

			afterCount = false;
		}



		if (0 < betweenCoordinate &&betweenCoordinate < 500)
		{

			ultrafinedust->transform.position.Set(700.f, -80.f, 0.f);

		}

		if (0 < betweenCoordinate2 &&betweenCoordinate2 < 500)
		{

			ultrafinedust2->transform.position.Set(1000.f, 150.f, 0.f);

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

	}

	MoveFineDust(FineDust1);
	MoveFineDust(FineDust2);
	MoveFineDust(FineDust3);
	MoveFineDust(FineDust4);
	MoveFineDust(FineDust5);
	MoveFineDust(FineDust6);
	MoveFineDust(FineDust7);
	MoveFineDust(FineDust8);
	MoveFineDust(FineDust9);
	MoveFineDust(FineDust10);

	float heartX = abs(iteamheart.transform.position.x - man.transform.position.x);
	float heartY = abs(iteamheart.transform.position.y - man.transform.position.y);


	if (0 < heartX &&heartX < 100 && heartY &&heartY < 100)
	{
		iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
		if (heartCount3 < 3)
		{
			heartCount3++;
		}
	}
	else if (man.transform.position.x > iteamheart.transform.position.x && heartX > 330.f)
	{
		iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
	}

	EatFineDust(FineDust1, 1500.f, 0.f);
	EatFineDust(FineDust2, 2000.f, -70.f);
	EatFineDust(FineDust3, 2500.f, -120.f);
	EatFineDust(FineDust4, 3000.f, 170.f);
	EatFineDust(FineDust5, 1000.f, -220.f);
	EatFineDust(FineDust6, 1200.f, 100.f);
	EatFineDust(FineDust7, 2500.f, 80.f);
	EatFineDust(FineDust8, 1400.f, 150.f);
	EatFineDust(FineDust9, 950.f, 210.f);
	EatFineDust(FineDust10, 1800.f, 270.f);

	switch (dustCount3 % 9)
	{
	case 0:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge0.png", State::m_renderer);
		break;
	case 1:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge1.png", State::m_renderer);
		break;
	case 2:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge2.png", State::m_renderer);
		break;
	case 3:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge3.png", State::m_renderer);
		break;
	case 4:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge4.png", State::m_renderer);
		break;
	case 5:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge5.png", State::m_renderer);
		break;
	case 6:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge6.png", State::m_renderer);
		break;
	case 7:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge7.png", State::m_renderer);
		break;
	case 8:
		BulletGauge.sprite.Free();
		BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge8.png", State::m_renderer);
		bullet_count = 3;
		dustCount3 = 0;

		break;

	default:
		break;
	}

	switch (bullet_count)
	{
	case 0:
		BulletCountImage.sprite.Free();
		BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb0.png", State::m_renderer);
		break;
	case 1:
		BulletCountImage.sprite.Free();
		BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb1.png", State::m_renderer);
		break;
	case 2:
		BulletCountImage.sprite.Free();
		BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb2.png", State::m_renderer);
		break;
	case 3:
		BulletCountImage.sprite.Free();
		BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb3.png", State::m_renderer);
		break;
	default:
		break;
	}

	switch (heartCount3)
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

	if (characterState3)
	{

		s_count3 += dt;
		if (s_count3 > 2.f)
		{
			miss3.transform.position.Set(0.f, -500.f, 0.f);
			s_count3 = 0;
			characterState3 = false;
		}

	}

	if (State::m_input->IsPressed((SDL_SCANCODE_M)))
	{
		heartCount3 = 3;
		bullet_count = 3;
		dustCount3 = 0;
		State::m_game->Change(LV_MainMenu);
	}

	UpdatePhysics(dt);		
	UpdateCustomPhysics(dt);
	Render(dt);
}

void Level3::UpdateUltraFineDust(CustomBaseObject* mDust)
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
				level3RedCount++;
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
				heartCount3--;
				mDust->isRed = false;
				characterState3 = true;
			}
			else if (man.transform.position.x > right_ultra + 230)
			{
				mDust->isRed = false;
				heartCount3--;
				characterState3 = true;

			}

		}
		float distanceUltraX = abs(mDust->transform.position.x - man.transform.position.x);
		float distanceUltraY = abs(mDust->transform.position.y - man.transform.position.y);


		//after finedust
		if (level3RedCount > 0)
		{
			if (0 < distanceUltraX && distanceUltraX < 100 && 0 < distanceUltraY &&distanceUltraY < 100)
			{
				mDust->transform.position.Set(0, -500, 0.f);
				dustCount3++;
				printf("eat ultra\n");
				level3RedCount = 0;
				mDust->isDead = true;
			}
			else if (man.transform.position.x > mDust->transform.position.x && distanceUltraX < 330.f && distanceUltraY < 100.f)
			{
				ScaleX -= 10;
				mDust->transform.position.Set(0, -500, 0.f);
				CleanGauge1.transform.SetScale(ScaleX, 60);
				failDust++;
				level3RedCount = 0;
			}
		}
		else if (man.transform.position.x > mDust->transform.position.x&& distanceUltraX < 330.f && distanceUltraY < 100.f)
		{
			ScaleX -= 20;
			mDust->transform.position.Set(0, -500, 0.f);
			CleanGauge1.transform.SetScale(ScaleX, 60);
			failDust++;
			level3RedCount = 0;
			return getbullet();
		}
	}
}
void Level3::getbullet()
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
}


void Level3::Close()
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
	ClearBaseState();
}

void Level3::ControlAudios()
{
    if (goggleCheck)
    {
        goggles.sound.Play();
    }

    if (negativeCheck)
    {
        itemnagative.sound.Play();
    }

    if (negativeCheck2)
    {
        itemnagative2.sound.Play();
    }

}