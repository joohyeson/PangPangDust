/******************************************************************************/
/*!
\file  Level1.cpp
\author Son Ju Hye
\par    email: juhye.son990902@gmail.com
\date   2019/06/11

stage 1

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include <SDL2/SDL.h>
#include <engine/State.h>
#include "Level1.h"
#include <ctime>
#include "ComponentTypes.h"
#include "ShootBulletController.h"

extern Object* toShootBullet = nullptr;

int bullet_count = 3;
float tCount = 0;
float sCount = 0;
int heartCount4 = 3;
int level1RedCount = 0;
int dustCount4 = 0;

extern int failDust = 0;

float ScaleX = 1000.f;
bool check = false;
bool characterState = false;

eDemoTopdownPlayerState    mState;
float               mTimer;
CustomBaseObject*   mGameOverScreen;

CustomBaseObject& Level1::CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
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

void Level1::Initialize()
{
	State::sCurrentState = this;
	State::m_pCamera = &camera;

	camera.position.Set(0, 0, 0);

	m_useBuiltInPhysics = false;
	b2Vec2 gravity(0.0f, -25.8f);
	SetCustomPhysicsWorld(gravity);
	background.SetName("Start");
	background.transform.SetScale(State::m_width, State::m_height);
	background.sprite.LoadImage("texture/backgroundss.png", State::m_renderer);
    background.sprite.SetFrame(4);
    background.sprite.SetSpeed(3.f);
    background.sprite.activeAnimation = true;

	background.transform.position.Set(0, 0, 0);

    background.sound.LoadSound("sound/Ending_Hero.mp3");
    background.sound.SetVolume(80);

    BulletCountBomb.SetName("BulletCountBomb");
    BulletCountBomb.transform.position.Set(500, 317, 0);
    BulletCountBomb.transform.SetScale(200, 80);
    BulletCountBomb.sprite.LoadImage("texture/BulletCount/BulletCountBomb0.png", State::m_renderer);

	wall.SetName("Wall");
	wall.transform.position.Set(14000.f, -300.0f, 0.0f);
	wall.transform.SetScale(30000, 10);
	wall.sprite.color = SDL_Color{ 255, 255, 255, 255 };
	wall.sprite.LoadImage("texture/rect.png", State::m_renderer);
	wall.sprite.color.r = wall.sprite.color.g
		= wall.sprite.color.b = 0X0;
	wall.customPhysics.pOwnerTransform = &wall.transform;
	wall.customPhysics.pOwnerTransform = &wall.transform;
	wall.customPhysics.bodyType = CustomPhysics::STATIC;
	wall.customPhysics.AllocateBody(GetCustomPhysicsWorld());

	CheckPoint.SetName("CheckPoint");
	CheckPoint.transform.position.Set(3600.f, -200.f, 0.f);
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

	miss.SetName("MISS");
	miss.transform.position.Set(0, -500, 0.f);
	miss.transform.SetScale(150, 50);
	miss.sprite.LoadImage("texture/MISS.png", State::m_renderer);

	CleanGauge1.SetName("CleanGauge1");
	CleanGauge1.transform.position.Set(man.transform.position.x - 650.f, 330.f, 0.f);
	CleanGauge1.transform.SetScale(1000, 60);
	CleanGauge1.sprite.LoadImage("texture/GreenCleanGauge.png", State::m_renderer);

	CleanGauge2.SetName("CleanGauge2");
	CleanGauge2.transform.position.Set(man.transform.position.x - 400, 330.f, 0.f);
	CleanGauge2.transform.SetScale(500, 60);
	CleanGauge2.sprite.LoadImage("texture/CleanGauge2.png", State::m_renderer);

	BulletGauge.SetName("BulletGauge");
	BulletGauge.transform.position.Set( 435,  317, 0);
	BulletGauge.transform.SetScale(400, 80);
	BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge0.png", State::m_renderer);

	iteamheart.SetName("iteamheart");
	iteamheart.transform.position.Set(1000.f, -100.f, 0.f);
	iteamheart.transform.SetScale(50, 50);
	iteamheart.sprite.LoadImage("texture/Lives.png", State::m_renderer);

	robot_vacuum.SetName("robot_vacuum");
	robot_vacuum.transform.position.Set(1500.f, -300.f, 0.f);
	robot_vacuum.transform.SetScale(120, 120);
	robot_vacuum.sprite.LoadImage("texture/robot.png", State::m_renderer);

	AddObject(&wall3);
	AddObject(&wall);
	AddCustomPhysicsComponent(&wall3);
	AddCustomPhysicsComponent(&wall4);
	AddCustomPhysicsComponent(&wall5);
	AddObject(&wall5);
	AddObject(&background);
	AddObject(&wall4);
    backGroundMusic.LoadMusic("sound/Ending_Hero.mp3");
    
	ultrafinedust = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust, "ultrafinedust", 900.f, -500.f);

	ultrafinedust2 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust2, "ultrafinedust2", 1500.f, -500.f);

	ultrafinedust3 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust3, "ultrafinedust3", 2000.f, -500.f);

	ultrafinedust4 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust4, "ultrafinedust4", 2600.f, -500.f);

	ultrafinedust5 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust5, "ultrafinedust5", 3400.f, -500.f);

	eatSound.sound.LoadSound("sound/vaccum.wav");
	eatSound.sound.SetVolume(80);
    backGroundMusic.Play();
	AddCustomPhysicsComponent(&man);
	AddCustomPhysicsComponent(&wall);
    AddObject(&BulletCountBomb);
	AddObject(&iteamheart);

	AddObject(&robot_vacuum);

	CreateFineDust(FineDust1, "FineDust1", 500.f, 0.f);
	CreateFineDust(FineDust2, "FineDust2", 1000.f, -70.f);
	CreateFineDust(FineDust4, "FineDust4", 700.f, 170.f);
	CreateFineDust(FineDust5, "FineDust5", 900.f, -220.f);
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


	AddObject(&CheckPoint);
	AddObject(&CleanGauge2);
	AddObject(&CleanGauge1);

	AddObject(&BulletGauge);
	AddObject(&PlayerHeart);
	AddObject(&miss);

	CreateShootPlayer(man, "man", 150, 120);

	//CreateHudSprite(gameOverScreen, "GameOverScreen", 0, 0, 2560.f, 1920.f, "texture/GameOverScreen.png", false);

	InitializeObjects();
}
void Level1::UpdateMiniWall(class CustomBaseObject* mWall)
{
	bool collid_check = man.customPhysics.GetVelocity().y <= 0;
    float left_check = mWall->transform.position.x - mWall->transform.GetScale().x / 2;

    if (man.transform.position.x <= left_check)
    {
        collid_check = false;
    }


    mWall->customPhysics.ActiveGhostCollision(collid_check);
}
CustomBaseObject& Level1::CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY)
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

Object& Level1::CreateFineDust(Object& finedust, const char* name, float positionX,float positionY)
{
	finedust.SetName(name);
	finedust.transform.position.Set(positionX, positionY, 0.f);
	finedust.transform.SetScale(100, 100);
	finedust.sprite.LoadImage("texture/dust.png", State::m_renderer);
	AddObject(&finedust);
	return finedust;
}

void Level1::MoveFineDust(Object& finedust)
{
	finedust.transform.position.x -=2;
}

void Level1::EatFineDust(Object& finedust, float positioX, float positionY)
{
	float distanceFineX = abs(finedust.transform.position.x - man.transform.position.x);
	float distanceFineY = abs(finedust.transform.position.y - man.transform.position.y);

	if (0 < distanceFineX &&distanceFineX < 100 && distanceFineY &&distanceFineY < 100)
	{
		dustCount4++;
		eatSound.sound.Play();
		finedust.transform.position.Set(positioX + man.transform.position.x, positionY, 0.f);
		printf("eat: %d \n", dustCount4);
		printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, finedust.transform.position.y);
	}
	else if (man.transform.position.x > finedust.transform.position.x && distanceFineX > 330.f)
	{
		ScaleX -= 10;
		finedust.transform.position.Set(positioX + man.transform.position.x -500, positionY, 0.f);
		CleanGauge1.transform.SetScale(ScaleX, 60);
		failDust++;
		printf("fail: %d \n", failDust);
		printf("fail findust1 \n");
	}

	if (check)
	{
		if (0 < abs(robot_vacuum.transform.position.x - finedust.transform.position.x) && abs(robot_vacuum.transform.position.x - finedust.transform.position.x) < 300
			&& abs(robot_vacuum.transform.position.y - finedust.transform.position.y) && abs(robot_vacuum.transform.position.y - finedust.transform.position.y) < 200)
		{
			dustCount4++;
			eatSound.sound.Play();
			finedust.transform.position.Set(1500.f + man.transform.position.x -500, positionY, 0.f);

			printf("eat: %d \n", dustCount4);
			printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, FineDust1.transform.position.y);
		}
		else if (finedust.transform.position.y < 0 && (robot_vacuum.transform.position.x > finedust.transform.position.x && abs(robot_vacuum.transform.position.x - finedust.transform.position.x) > 330.f))
		{
			dustCount4++;
			eatSound.sound.Play();
			finedust.transform.position.Set(1500.f + man.transform.position.x-500, positionY, 0.f);

			printf("eat: %d \n", dustCount4);
			printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, finedust.transform.position.y);
		}
	}
}

CustomBaseObject& Level1::CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY)
{
	ultraFineDust->SetName(name);
	ultraFineDust->transform.position.Set(positionX, positionY, 0.f);
	ultraFineDust->transform.SetScale(200, 200);
	ultraFineDust->sprite.LoadImage("texture/UltraFineDust.png", State::m_renderer);
	AddObject(ultraFineDust);
	AddCustomPhysicsComponent(ultraFineDust);
	return *ultraFineDust;
}

CustomBaseObject& Level1::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
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
void Level1::Update(float dt)
{
	UpdateObjects(dt);
   if( backGroundMusic.IsPaused())
   {
       backGroundMusic.Play();
   }

	float d_x = abs(robot_vacuum.transform.position.x - man.transform.position.x); //distance
	float d_y = abs(robot_vacuum.transform.position.y - man.transform.position.y);

   
	if (0 < d_x && d_x < 250 && d_y && d_y < 80)
	{
		robot_vacuum.transform.SetScale(300, 300);
		robot_vacuum.transform.position.Set(2000.f, -250.f, 0.f);
		check = true;
	}

	if (check)
	{
		tCount += dt;
		if (tCount > 5.f)
		{
			check = false;
			robot_vacuum.transform.position.Set(0, 0, 0);
			robot_vacuum.transform.SetScale(0, 0);

		}
		robot_vacuum.transform.position.x = man.transform.position.x+100;
	}

    UpdateMiniWall(&MiniWall1);
    UpdateMiniWall(&MiniWall2);
    UpdateMiniWall(&MiniWall3);
    UpdateMiniWall(&MiniWall4);
    UpdateMiniWall(&MiniWall5);
    UpdateMiniWall(&MiniWall6);
    UpdateMiniWall(&MiniWall7);
    UpdateMiniWall(&wall4);
	
	if (man.transform.position.x > CheckPoint.transform.position.x)
	{
		State::m_game->Pause();
	}

	if (CleanGauge1.transform.GetScale().x < 50 || heartCount4 == 0)
	{
		mState = eDemoTopdownPlayerState::GameOver;
		mTimer = 0;
		if (mState == eDemoTopdownPlayerState::GameOver)
		{
            State::m_game->Change(LV_GameOver);
			
		}
	}

    if (man.transform.position.x > CheckPoint.transform.position.x)
    {
	    State::m_game->Change(LV_Pause);
    }
    if (State::m_input->IsPressed((SDL_SCANCODE_2)))
    {
        State::m_game->Change(LV_Level2);
    }
	if (CleanGauge1.transform.GetScale().x < 50 || heartCount4 == 0)
	{
		mState = eDemoTopdownPlayerState::GameOver;
		mTimer = 0;
		if (mState == eDemoTopdownPlayerState::GameOver)
		{
            State::m_game->Change(LV_GameOver);
		}
	}

	float betweenCoordinate = abs(ultrafinedust->transform.position.x - man.transform.position.x); // to appear ultra finedust when player close to ultrafine dust
	float betweenCoordinate2 = abs(ultrafinedust2->transform.position.x - man.transform.position.x);
	float betweenCoordinate3 = abs(ultrafinedust3->transform.position.x - man.transform.position.x);
	float betweenCoordinate4 = abs(ultrafinedust4->transform.position.x - man.transform.position.x);
	float betweenCoordinate5 = abs(ultrafinedust5->transform.position.x - man.transform.position.x);

	{
		camera.position.x = man.transform.position.x + 350.f;
		CleanGauge1.transform.position.x = man.transform.position.x - 300;
		CleanGauge2.transform.position.x = man.transform.position.x - 50;
		background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
		BulletGauge.transform.position.x = man.transform.position.x + 785;
		
        BulletCountBomb.transform.position.x = man.transform.position.x + 375;
  
	    PlayerHeart.transform.position.x = man.transform.position.x - 200;
		if (characterState)
		{
			miss.transform.position.Set(man.transform.position.x, man.transform.position.y + 100, 0.f);
		}
	}

	if (0 < betweenCoordinate &&betweenCoordinate < 500)
	{
		ultrafinedust->transform.position.Set(900.f, -80.f, 0.f);
	}

	if (0 < betweenCoordinate2 &&betweenCoordinate2 < 500)
	{
		ultrafinedust2->transform.position.Set(1500.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate3 &&betweenCoordinate3 < 500)
	{
		ultrafinedust3->transform.position.Set(2000.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate4 &&betweenCoordinate4 < 500)
	{
		ultrafinedust4->transform.position.Set(2600.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate5 &&betweenCoordinate5 < 500)
	{
		ultrafinedust5->transform.position.Set(3000.f, 120.f, 0.f);
	}

	MoveFineDust(FineDust1);
	MoveFineDust(FineDust2);
	MoveFineDust(FineDust4);
	MoveFineDust(FineDust5);
	MoveFineDust(FineDust7);
	MoveFineDust(FineDust8);
	MoveFineDust(FineDust9);
	MoveFineDust(FineDust10);

	float heartX = abs(iteamheart.transform.position.x - man.transform.position.x);
	float heartY = abs(iteamheart.transform.position.y - man.transform.position.y);

	if (0 < heartX &&heartX < 100 && heartY &&heartY < 100)
	{
		iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
		if (heartCount4 < 3)
		{
			heartCount4++;
		}
	}
	else if(man.transform.position.x > iteamheart.transform.position.x && heartX > 330.f)
	{
		iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
	}

	EatFineDust(FineDust1, 1500.f, 0.f);
	EatFineDust(FineDust2, 2000.f, -70.f);
	EatFineDust(FineDust4, 3000.f, 170.f);
	EatFineDust(FineDust5, 1000.f, -220.f);
	EatFineDust(FineDust7, 2500.f, 80.f);
	EatFineDust(FineDust8, 1400.f, 150.f);
	EatFineDust(FineDust9, 950.f, 210.f);
	EatFineDust(FineDust10, 1800.f, 270.f);

	switch (dustCount4 % 9)
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
		dustCount4 = 0;
		break;

	default:
		break;
	}

	switch (bullet_count)
	{
	case 0:
        
        BulletCountBomb.sprite.Free();
        BulletCountBomb.sprite.LoadImage("texture/BulletCount/BulletCountBomb0.png", State::m_renderer);

       
		break;
	case 1:
        BulletCountBomb.sprite.Free();
        BulletCountBomb.sprite.LoadImage("texture/BulletCount/BulletCountBomb1.png", State::m_renderer);
       
        
		break;
	case 2:
        BulletCountBomb.sprite.Free();
        BulletCountBomb.sprite.LoadImage("texture/BulletCount/BulletCountBomb2.png", State::m_renderer);
        
        
		break;
	case 3:
        BulletCountBomb.sprite.Free();
        BulletCountBomb.sprite.LoadImage("texture/BulletCount/BulletCountBomb3.png", State::m_renderer);
        
       
		break;
	default:
		break;
	}

	switch (heartCount4)
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

	if (characterState)
	{
			sCount += dt;
			if (sCount > 2.f) // miss count time
			{
				miss.transform.position.Set(0.f, -500.f, 0.f);
				sCount = 0;
				characterState = false;
			}
			
	}
  
	if (State::m_input->IsPressed((SDL_SCANCODE_M)))
	{
		heartCount4=3;
		bullet_count=3;
		dustCount4=0;
        State::m_game->Change(LV_MainMenu);
	}
    if (State::m_input->IsTriggered((SDL_SCANCODE_P)))
    {
        printf("P is pressed\n");
       
        backGroundMusic.Pause();
        State::m_game->Pause();
    }

	UpdatePhysics(dt);	
	UpdateCustomPhysics(dt);
	Render(dt);
}

void Level1::UpdateUltraFineDust(CustomBaseObject* mDust)
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
				level1RedCount++;
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
				heartCount4--;
				characterState = true;

				mDust->isRed = false;
			}
			else if (man.transform.position.x > right_ultra + 230)
			{
				mDust->isRed = false;
				heartCount4--;
				characterState = true;
			}

		}

		float distanceXultra = abs(mDust->transform.position.x - man.transform.position.x);
		float distanceyultra = abs(mDust->transform.position.y - man.transform.position.y);

		if (level1RedCount > 0)
		{
			if (0 < distanceyultra && distanceyultra < 100 && 0 < distanceXultra &&distanceXultra < 100)
			{
				mDust->transform.position.Set(0, -500, 0.f);
				dustCount4++;
				level1RedCount = 0;
				mDust->isDead=true;
			}
			else if (man.transform.position.x > mDust->transform.position.x && distanceyultra < 330.f && distanceXultra < 100.f)
			{
				ScaleX -= 10;
				mDust->transform.position.Set(0, -500, 0.f);
				CleanGauge1.transform.SetScale(ScaleX, 60);
				failDust++;
				level1RedCount = 0;
				return getbullet();
			}
		}
		else if (man.transform.position.x > mDust->transform.position.x&& distanceyultra < 330.f && distanceXultra < 100.f)
		{
				ScaleX -= 20;
				mDust->transform.position.Set(0, -500, 0.f);
				CleanGauge1.transform.SetScale(ScaleX, 60);
				failDust++;
				level1RedCount = 0;
				return getbullet();
		}
	}
}
void Level1::getbullet()
{
	UpdateUltraFineDust(ultrafinedust);
	UpdateUltraFineDust(ultrafinedust2);
	UpdateUltraFineDust(ultrafinedust3);
	UpdateUltraFineDust(ultrafinedust4);
	UpdateUltraFineDust(ultrafinedust5);
}


void Level1::Close()
{
	RemoveObject(ultrafinedust);
	RemoveObject(ultrafinedust2);
	RemoveObject(ultrafinedust3);
	RemoveObject(ultrafinedust4);
	RemoveObject(ultrafinedust5);
	ClearBaseState();
}

