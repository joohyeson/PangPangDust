/******************************************************************************/
/*!
\file  Level2.cpp
\author Choi Jae Woo
\par    email: wod6983@gmail.com
\date   2019/06/5

stage 2
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include <SDL2/SDL.h>
#include <engine/State.h>
#include "Level2.h"
#include <ctime>
#include "ComponentTypes.h"
#include "ShootBulletController.h"

extern Object* toShootBullet;

extern int bullet_count;

float t_count1 = 0;
bool check1 = true;

float n_count3 = 0.f;
int heart_count1 = 3;

int  level2RedCount= 0;

int dustcount1 = 0;


float ScaleX1 = 1000.f;

extern int failDust;

float sCount1  = 0;
bool characterState2 = false;


CustomBaseObject& Level2::CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
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

void Level2::Initialize()
{

	bullet_count = 3;
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

    eatSound.sound.LoadSound("sound/vaccum.wav");
    eatSound.sound.SetVolume(80);

    BulletCountImage.SetName("BulletCountImage");
    BulletCountImage.transform.position.Set(500, 317, 0);
    BulletCountImage.transform.SetScale(200, 80);
    BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb0.png", State::m_renderer);

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

	miss2.SetName("MISS2");
	miss2.transform.position.Set(0, -500, 0.f);
	miss2.transform.SetScale(150, 50);
	miss2.sprite.LoadImage("texture/MISS.png", State::m_renderer);

    CheckPoint.SetName("CheckPoint");
    CheckPoint.transform.position.Set(6200.f, -200.f, 0.f);
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
    CleanGauge1.transform.position.Set(man.transform.position.x - 650.f, 330.f, 0.f);
    CleanGauge1.transform.SetScale(1000, 60);
    CleanGauge1.sprite.LoadImage("texture/GreenCleanGauge.png", State::m_renderer);

    CleanGauge2.SetName("CleanGauge2");
    CleanGauge2.transform.position.Set(man.transform.position.x - 400, 330.f, 0.f);
    CleanGauge2.transform.SetScale(500, 60);
    CleanGauge2.sprite.LoadImage("texture/CleanGauge2.png", State::m_renderer);

    BulletGauge.SetName("BulletGauge");
    BulletGauge.transform.position.Set(435, 317, 0);
    BulletGauge.transform.SetScale(400, 80);
    BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge0.png", State::m_renderer);

    iteamheart.SetName("iteamheart");
    iteamheart.transform.position.Set(1000.f, -100.f, 0.f);
    iteamheart.transform.SetScale(50, 50);
    iteamheart.sprite.LoadImage("texture/Lives.png", State::m_renderer);

    item_rain.SetName("item_rain");
    item_rain.transform.position.Set(1000.f, -300.f, 0.f);
    item_rain.transform.SetScale(100, 100);
    item_rain.sprite.LoadImage("texture/negative.png", State::m_renderer);
    item_rain.SetName("RainSound");
    item_rain.sound.LoadSound("sound/rain.mp3");
    item_rain.sound.SetVolume(200);


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
    CreateUltraFineDust(ultrafinedust5, "ultrafinedust5", 3500.f, -500.f);

	ultrafinedust6 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust6, "ultrafinedust6", 3600.f, -500.f);

	ultrafinedust7 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust7, "ultrafinedust7", 4100.f, -500.f);

	ultrafinedust8 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust8, "ultrafinedust8", 4780.f, -500.f);

	ultrafinedust9 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust9, "ultrafinedust9", 5180.f, -500.f);

	ultrafinedust10 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust10, "ultrafinedust10", 5900.f, -500.f);
    backGroundMusic.Play();
    AddCustomPhysicsComponent(&man);
    AddCustomPhysicsComponent(&wall);
    AddObject(&BulletCountImage);

    AddObject(&iteamheart);

    AddObject(&robot_vacuum);
    AddObject(&item_rain);

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
	AddObject(&miss2);

    AddObject(&BulletGauge);
    AddObject(&PlayerHeart);
    CreateShootPlayer(man, "man", 150, 120);

    InitializeObjects();
}

CustomBaseObject& Level2::CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY)
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

Object& Level2::CreateFineDust(Object& finedust, const char* name, float positionX, float positionY)
{
    finedust.SetName(name);
    finedust.transform.position.Set(positionX, positionY, 0.f);
    finedust.transform.SetScale(100, 100);
    finedust.sprite.LoadImage("texture/dust.png", State::m_renderer);
    AddObject(&finedust);
    return finedust;
}
void Level2::UpdateMiniWall(class CustomBaseObject* mWall)
{
    bool collid_check = man.customPhysics.GetVelocity().y <= 0;
    float left_check = mWall->transform.position.x - mWall->transform.GetScale().x / 2;

    if (man.transform.position.x <= left_check)
    {
        collid_check = false;
    }


    mWall->customPhysics.ActiveGhostCollision(collid_check);
}
void Level2::MoveFineDust(Object& finedust)
{
    finedust.transform.position.x -= 2;
}

void Level2::EatFineDust(Object& finedust, float positioX, float positionY)
{
    float distaneeFineX = abs(finedust.transform.position.x - man.transform.position.x);
    float distanceFineY = abs(finedust.transform.position.y - man.transform.position.y);


    if (0 < distaneeFineX &&distaneeFineX < 100 && distanceFineY &&distanceFineY < 100)
    {
        dustcount1++;
        eatSound.sound.Play();
        finedust.transform.position.Set(positioX + man.transform.position.x, positionY, 0.f);
        printf("eat: %d \n", dustcount1);
        printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, finedust.transform.position.y);
    }
    else if (man.transform.position.x > finedust.transform.position.x && distaneeFineX > 330.f)
    {
        ScaleX1 -= 10;
        finedust.transform.position.Set(positioX + man.transform.position.x - 500, positionY, 0.f);
        CleanGauge1.transform.SetScale(ScaleX1, 60);
        failDust++;
        printf("fail: %d \n", failDust);
        printf("fail findust1 \n");
    }
}

CustomBaseObject& Level2::CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY)
{
    ultraFineDust->SetName(name);
    ultraFineDust->transform.position.Set(positionX, positionY, 0.f);
    ultraFineDust->transform.SetScale(200, 200);
    ultraFineDust->sprite.LoadImage("texture/UltraFineDust.png", State::m_renderer);
    AddObject(ultraFineDust);
    AddCustomPhysicsComponent(ultraFineDust);
    return *ultraFineDust;
}

CustomBaseObject& Level2::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
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
void Level2::Update(float dt)
{
    UpdateObjects(dt);

    if (check1)
    {

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
    }
    if (!check1)
    {

        FineDust1.transform.position.SetZero();
        FineDust2.transform.position.SetZero();
        FineDust3.transform.position.SetZero();
        FineDust4.transform.position.SetZero();
        FineDust5.transform.position.SetZero();
        FineDust6.transform.position.SetZero();
        FineDust7.transform.position.SetZero();
        FineDust8.transform.position.SetZero();
        FineDust9.transform.position.SetZero();
        FineDust10.transform.position.SetZero();
        bullet_count = 3;
       
    }

    UpdateMiniWall(&MiniWall1);
    UpdateMiniWall(&MiniWall2);
    UpdateMiniWall(&MiniWall3);
    UpdateMiniWall(&MiniWall4);

    UpdateMiniWall(&MiniWall5);
    UpdateMiniWall(&MiniWall6);
    UpdateMiniWall(&MiniWall7);

    if (State::m_input->IsPressed((SDL_SCANCODE_3)))
    {
        State::m_game->Change(LV_Level3);
    }

    if (CleanGauge1.transform.GetScale().x < 50 || heart_count1 == 0)
    {
        mState = eDemoTopdownPlayerState::GameOver;
        mTimer = 0;
        if (mState == eDemoTopdownPlayerState::GameOver)
        {
            State::m_game->Change(LV_GameOver);
            //gameOverScreen.sprite.isVisible = true;
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

	    if (!check1)
	    {
		    item_rain.transform.position.x = man.transform.position.x + 350;
		    item_rain.transform.position.y = 0;
		    item_rain.transform.position.z = 500;
	    }

		if (characterState2)
		{
			miss2.transform.position.Set(man.transform.position.x, man.transform.position.y + 100, 0.f);
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

    float rainDistanceX = abs(item_rain.transform.position.x - man.transform.position.x);
    float rainDistanceY = abs(item_rain.transform.position.y - man.transform.position.y);

    if (0 < rainDistanceX &&rainDistanceX < 100 && rainDistanceY &&rainDistanceY < 100)
    {

        item_rain.transform.SetScale(1280, 720);
        check1 = false;
        item_rain.transform.rotation = 0;
        item_rain.SetName("item_rain");
        item_rain.transform.SetScale(State::m_width, State::m_height);
        item_rain.sprite.LoadImage("texture/rain.png", State::m_renderer);
        item_rain.sprite.SetFrame(2);
        item_rain.sprite.SetSpeed(6.f);
        item_rain.sprite.activeAnimation = true;
        ControlAudios();
    }
    if (!check1)
    {
        n_count3 += dt;

        if (n_count3 > 5.f)
        {

            item_rain.transform.SetScale(0, 0);
            item_rain.transform.position.Set(-500, -500, 0);
            check1 = true;
            ControlAudios();
        }
    }

    if (0 < betweenCoordinate &&betweenCoordinate < 500)
    {
        ultrafinedust->transform.position.Set(900.f, -80.f, 0.f);
    }

    if (0 < betweenCoordinate2&&betweenCoordinate2 < 500)
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
        ultrafinedust5->transform.position.Set(3500.f, 120.f, 0.f);
    }
	if (0 < betweenCoordinate6 &&betweenCoordinate6 < 500)
	{
		ultrafinedust6->transform.position.Set(3600.f, -80.f, 0.f);
	}

	if (0 < betweenCoordinate7 &&betweenCoordinate7 < 500)
	{
		ultrafinedust7->transform.position.Set(4100.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate8 &&betweenCoordinate8 < 500)
	{
		ultrafinedust8->transform.position.Set(4780.f, 170.f, 0.f);
	}

	if (0 < betweenCoordinate9 &&betweenCoordinate9 < 500)
	{
		ultrafinedust9->transform.position.Set(5180.f, 150.f, 0.f);
	}

	if (0 < betweenCoordinate10 &&betweenCoordinate10 < 500)
	{
		ultrafinedust10->transform.position.Set(5900.f, 120.f, 0.f);
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
        if (heart_count1 < 3)
        {
            heart_count1++;
        }
    }
    else if (man.transform.position.x > iteamheart.transform.position.x && heartX > 330.f)
    {
        iteamheart.transform.position.Set(man.transform.position.x + 1500, 0.f, 0.f);
    }


    if (check1) {
        switch (dustcount1 % 9)
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
            dustcount1 = 0;

            break;

        default:
            break;
        }
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

    switch (heart_count1)
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

	if (characterState2)
	{

		sCount1 += dt;
		if (sCount1 > 2.f)
		{
			miss2.transform.position.Set(0.f, -500.f, 0.f);
			sCount1 = 0;
			characterState2 = false;
		}

	}

    if (man.transform.position.x > CheckPoint.transform.position.x)
    {
        State::m_game->Change(LV_Pause);
    }
    if (State::m_input->IsPressed((SDL_SCANCODE_M)))
    {
        heart_count1 = 3;
        bullet_count = 3;
        dustcount1 = 0;
        State::m_game->Change(LV_MainMenu);
    }
    UpdatePhysics(dt);	
    UpdateCustomPhysics(dt);
    Render(dt);
}

void Level2::UpdateUltraFineDust(CustomBaseObject* mDust)
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
				level2RedCount++;
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
                heart_count1--;
				characterState2 = true;
                mDust->isRed = false;
            }
            else if (man.transform.position.x > right_ultra + 230)
            {
                mDust->isRed = false;
                heart_count1--;
				characterState2 = true;

            }

        }
        float distanceUltraX = abs(mDust->transform.position.x - man.transform.position.x);
        float distanceUltraY = abs(mDust->transform.position.y - man.transform.position.y);

        if (level2RedCount > 0)
        {
            if (0 < distanceUltraX && distanceUltraX < 100 && 0 < distanceUltraY &&distanceUltraY < 100)
            {
                mDust->transform.position.Set(0, -500, 0.f);
                dustcount1++;
				level2RedCount = 0;
                mDust->isDead = true;
            }
            else if (man.transform.position.x > mDust->transform.position.x && distanceUltraX < 330.f && distanceUltraY < 100.f)
            {
                ScaleX1 -= 10;
                mDust->transform.position.Set(0, -500, 0.f);
                CleanGauge1.transform.SetScale(ScaleX1, 60);
                failDust++;
				level2RedCount = 0;
                return getbullet();
            }
        }
        else if (man.transform.position.x > mDust->transform.position.x&& distanceUltraX < 330.f && distanceUltraY < 100.f)
        {
            ScaleX1 -= 20;
            mDust->transform.position.Set(0, -500, 0.f);
            CleanGauge1.transform.SetScale(ScaleX1, 60);
            failDust++;
			level2RedCount = 0;
            return getbullet();
        }
    }
}
void Level2::getbullet()
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


void Level2::Close()
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
    RemoveObject(&item_rain);
    ClearBaseState();
}
void Level2::ControlAudios()
{
    if (!check1)
    {
        item_rain.sound.Play();
    }
    if (check1)
    {
        item_rain.sound.Free();
		ScaleX1 += 100;
    }
}

