/******************************************************************************/
/*!
\file  Tutorial.cpp
\author Kim Ha Gyeong
\par    email: digiepn.hagyoeng@gmail.com
\date   2019/06/11

stage Tutorial

*****YOU CANNOT MODIFY THIS FILE!!*****
*/
/******************************************************************************/
#include "CommonLevel.h"
#include <SDL2/SDL.h>
#include <engine/State.h>
#include "Tutorial.h"
#include <ctime>
#include "ComponentTypes.h"
#include "TutorialCoutroller.h"

int fillBulletGauge = 1;
extern int bullet_count;
static int heartCount = 3;
static int red = 0;
static int dustCount = 0;
static int failDust = 0;
extern int tutorialCount = 0; // Count for Progress of the Tutorial When this count is increased, the player can see the next stage in the tutorial
static float ScaleX = 1000.f;

void Tutorial::Initialize()
{
	bullet_count = 0;
	State::sCurrentState = this;
	State::m_pCamera = &camera;

	camera.position.Set(0, 0, 0);

	m_useBuiltInPhysics = false;
	b2Vec2 gravity(0.0f, -25.8f);
	SetCustomPhysicsWorld(gravity);
	backGroundMusic.LoadMusic("sound/Ending_Hero.mp3");
	backGroundMusic.Play();
	background.SetName("Start");
	background.transform.SetScale(State::m_width, State::m_height);
	background.sprite.LoadImage("texture/background11.png", State::m_renderer);
	background.transform.position.Set(0, 0, 0);

	BulletCountImage.SetName("BulletCountImage");
	BulletCountImage.transform.position.Set(500, 317, 0);
	BulletCountImage.transform.SetScale(200, 80);
	BulletCountImage.sprite.LoadImage("texture/BulletCount/BulletCountBomb0.png", State::m_renderer);

	tutorialdywjd.SetName("dywjd");
	tutorialdywjd.transform.position.Set(300.f, -200.f, 0.f);
	tutorialdywjd.transform.SetScale(150, 150);
	tutorialdywjd.sprite.LoadImage("texture/dywjd.png", State::m_renderer);

	tutorialakf.SetName("akf");
	tutorialakf.transform.position.Set(0.f, -100.f, 0.f);
	tutorialakf.transform.SetScale(400, 100);
	tutorialakf.sprite.LoadImage("texture/tutorial/Picture1.png", State::m_renderer);

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
	CheckPoint.transform.position.Set(4300, -200.f, 0.f);
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
	CleanGauge1.transform.SetScale(1000, 60);
	CleanGauge1.sprite.LoadImage("texture/GreenCleanGauge.png", State::m_renderer);

	CleanGauge2.SetName("CleanGauge2");
	CleanGauge2.transform.position.Set(400, 330.f, 0.f);
	CleanGauge2.transform.SetScale(500, 60);
	CleanGauge2.sprite.LoadImage("texture/CleanGauge2.png", State::m_renderer);

	BulletGauge.SetName("BulletGauge");
	BulletGauge.transform.position.Set(500, 317, 0);
	BulletGauge.transform.SetScale(400, 80);
	BulletGauge.sprite.LoadImage("texture/BulletGauge/BulletGauge0.png", State::m_renderer);

	AddObject(&wall3);
	AddObject(&wall);
	AddCustomPhysicsComponent(&wall3);
	AddCustomPhysicsComponent(&wall4);
	AddCustomPhysicsComponent(&wall5);
	AddObject(&wall5);
	AddObject(&background);
	AddObject(&wall4);

	ultrafinedust = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust, "ultrafinedust", 1500.f, -500.f);

	ultrafinedust2 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust2, "ultrafinedust2", 2800.f, -500.f);

	ultrafinedust3 = new CustomBaseObject;
	CreateUltraFineDust(ultrafinedust3, "ultrafinedust3", 3500.f, -500.f);

	AddCustomPhysicsComponent(&man);
	AddCustomPhysicsComponent(&wall);
	AddObject(&BulletCountImage);

	CreateFineDust(FineDust1, "FineDust1", 500.f, 0.f);
	CreateFineDust(FineDust2, "FineDust2", 1000.f, -70.f);
	CreateFineDust(FineDust3, "FineDust3", 800.f, -120.f);
	CreateFineDust(FineDust4, "FineDust4", 700.f, 170.f);
	CreateFineDust(FineDust5, "FineDust5", 900.f, -220.f);

	CreateMiniwall(MiniWall1, "MiniWall1", 100, 20, 500.f, 75.f);
	CreateMiniwall(MiniWall2, "MiniWall2", 100, 20, 850.f, 50.f);
	CreateMiniwall(MiniWall3, "MiniWall3", 100, 20, 1450.f, 30.f);
	CreateMiniwall(MiniWall4, "MiniWall4", 100, 20, 1700.f, 150.f);
	CreateMiniwall(MiniWall5, "MiniWall5", 100, 20, 2000.f, 75.f);

	AddObject(&CheckPoint);
	AddObject(&CleanGauge2);
	AddObject(&CleanGauge1);

	AddObject(&BulletGauge);
	AddObject(&PlayerHeart);

	CreateShootPlayer(man, "man", 150, 120);
	AddObject(&tutorialdywjd);
	AddObject(&tutorialakf);

	InitializeObjects();
}

CustomBaseObject& Tutorial::CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY)
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

void Tutorial::UpdateMiniWall(class CustomBaseObject* mWall)
{
	bool collid_check = man.customPhysics.GetVelocity().y <= 0;
	float left_check = mWall->transform.position.x - mWall->transform.GetScale().x / 2;

	if (man.transform.position.x <= left_check)
	{
		collid_check = false;
	}


	mWall->customPhysics.ActiveGhostCollision(collid_check);
}

Object& Tutorial::CreateFineDust(Object& finedust, const char* name, float positionX, float positionY)
{
	finedust.SetName(name);
	finedust.transform.position.Set(positionX, positionY, 0.f);
	finedust.transform.SetScale(100, 100);
	finedust.sprite.LoadImage("texture/dust.png", State::m_renderer);
	AddObject(&finedust);

	return finedust;
}

void Tutorial::MoveFineDust(Object& finedust)
{
	finedust.transform.position.x -= 2;
}

void Tutorial::EatFineDust(Object& finedust, float positioX, float positionY)
{
	if (tutorialCount >= 2)
	{
		float BetweenDustCoordinate1 = finedust.transform.position.x - man.transform.position.x;
		float BetweenDustCoordinate11 = finedust.transform.position.y - man.transform.position.y;
		float abDustCoordinate11 = abs(BetweenDustCoordinate11);
		float abDustCoordinate1 = abs(BetweenDustCoordinate1);

		if (0 < abDustCoordinate1 &&abDustCoordinate1 < 100 && abDustCoordinate11 &&abDustCoordinate11 < 100)
		{
			dustCount++;
			finedust.transform.position.Set(positioX + man.transform.position.x, positionY, 0.f);
			printf("eat: %d \n", dustCount);
			printf("Velocity: %.2f, %.2f\n", finedust.transform.position.x, finedust.transform.position.y);
			if (tutorialCount == 2)
			{
				tutorialCount++;
			}
		}
		else if (man.transform.position.x > finedust.transform.position.x && abDustCoordinate1 > 330.f)
		{
			ScaleX -= 10;
			finedust.transform.position.Set(positioX + man.transform.position.x - 500, positionY, 0.f);
			CleanGauge1.transform.SetScale(ScaleX, 60);
			failDust++;
			printf("fail: %d \n", failDust);
			printf("fail findust1 \n");
		}

	}

}

CustomBaseObject& Tutorial::CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY)
{
	ultraFineDust->SetName(name);
	ultraFineDust->transform.position.Set(positionX, positionY, 0.f);
	ultraFineDust->transform.SetScale(200, 200);
	ultraFineDust->sprite.LoadImage("texture/UltraFineDust.png", State::m_renderer);
	AddObject(ultraFineDust);
	AddCustomPhysicsComponent(ultraFineDust);
	return *ultraFineDust;
}


CustomBaseObject& Tutorial::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
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

	State::sCurrentState->AddComponentToObject(&player, eComponentTypes::TutorialController);
	State::sCurrentState->AddCustomPhysicsComponent(&player);
	State::sCurrentState->AddObject(&player);
	return player;
}

void Tutorial::Update(float dt)
{
	UpdateObjects(dt);
	/******************* Logic ******************/

	if (man.transform.position.x > CheckPoint.transform.position.x)
	{
		sCurrentState->m_game->Change(LV_MainMenu);
	}

	if (State::m_input->IsPressed((SDL_SCANCODE_SPACE)))
	{
		if (tutorialCount == 0)
		{
			tutorialCount++;
			tutorialakf.sprite.Free();
			tutorialakf.sprite.LoadImage("texture/tutorial/Picture2.png", State::m_renderer);
		}
		else if (tutorialCount == 3)
		{
			tutorialCount++;
		}
		else if (tutorialCount == 5)
		{
			tutorialCount++;
		}
		else if (tutorialCount == 11)
		{
			tutorialCount++;
		}
		printf("%d", tutorialCount);
		printf("%d", red);
	}

	UpdateMiniWall(&MiniWall1);
	UpdateMiniWall(&MiniWall2);
	UpdateMiniWall(&MiniWall3);
	UpdateMiniWall(&MiniWall4);
	UpdateMiniWall(&MiniWall5);


	float betweenCoordinate = abs(ultrafinedust->transform.position.x - man.transform.position.x);
	float betweenCoordinate2 = abs(ultrafinedust2->transform.position.x - man.transform.position.x);
	float betweenCoordinate3 = abs(ultrafinedust3->transform.position.x - man.transform.position.x);


	{
		if (tutorialCount >= 1)
		{
			camera.position.x = man.transform.position.x + 350.f;
			CleanGauge1.transform.position.x = man.transform.position.x - 300;
			CleanGauge2.transform.position.x = man.transform.position.x - 50;
			background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
			BulletGauge.transform.position.x = man.transform.position.x + 785;
			BulletCountImage.transform.position.x = man.transform.position.x + 375;
			PlayerHeart.transform.position.x = man.transform.position.x - 200;
			tutorialdywjd.transform.position.x = man.transform.position.x + 800;
			tutorialakf.transform.position.x = man.transform.position.x + 500;
		}
	}

	if (State::m_input->IsPressed((SDL_SCANCODE_A)))
	{
		camera.position.x = man.transform.position.x + 350.f;
		CleanGauge1.transform.position.x = man.transform.position.x - 300;
		CleanGauge2.transform.position.x = man.transform.position.x - 50;
		background.transform.position.Set(man.transform.position.x + 350.f, 0, 0);
		BulletGauge.transform.position.x = man.transform.position.x + 785;
		BulletCountImage.transform.position.x = man.transform.position.x + 300;
		PlayerHeart.transform.position.x = man.transform.position.x - 200;
	}


	if (tutorialCount == 2)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture3.png", State::m_renderer);
	}
	else if (tutorialCount == 3)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture4.png", State::m_renderer);
	}
	else if (tutorialCount == 4)
	{
		tutorialakf.sprite.Free();

		tutorialakf.sprite.LoadImage("texture/tutorial/Picture5.png", State::m_renderer);
	}
	else if (tutorialCount == 5)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture6.png", State::m_renderer);
	}
	else if (tutorialCount == 6)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture7.png", State::m_renderer);
		if (fillBulletGauge == 1)
		{
			dustCount = 70;
			fillBulletGauge++;
		}
	}
	else if (tutorialCount == 7)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture9.png", State::m_renderer);
	}
	else if (tutorialCount == 9)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture10.png", State::m_renderer);
	}
	else if (tutorialCount == 10)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture11.png", State::m_renderer);
	}
	else if (tutorialCount == 11)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture12.png", State::m_renderer);
	}
	else if (tutorialCount == 12)
	{
		tutorialakf.sprite.Free();
		tutorialakf.sprite.LoadImage("texture/tutorial/Picture13.png", State::m_renderer);
	}

	if (0 < betweenCoordinate &&betweenCoordinate < 200)
	{
		ultrafinedust->transform.position.Set(1500, -80.f, 0.f);
		if (tutorialCount == 4)
		{
			tutorialCount++;
		}
	}

	if (0 < betweenCoordinate2 &&betweenCoordinate2 < 200)
	{
		ultrafinedust2->transform.position.Set(2800, 150.f, 0.f);

		if (tutorialCount == 7)
		{
			tutorialCount++;
		}
	}

	if (0 < betweenCoordinate3 &&betweenCoordinate3 < 500)
	{

		ultrafinedust3->transform.position.Set(3500, 170.f, 0.f);
	}

	if (tutorialCount >= 2)
	{
		MoveFineDust(FineDust1);
		MoveFineDust(FineDust2);
		MoveFineDust(FineDust3);
		MoveFineDust(FineDust4);
		MoveFineDust(FineDust5);
	}

	EatFineDust(FineDust1, 1500.f, 0.f);
	EatFineDust(FineDust2, 2000.f, -70.f);
	EatFineDust(FineDust3, 2500.f, -120.f);
	EatFineDust(FineDust4, 3000.f, 170.f);
	EatFineDust(FineDust5, 1000.f, -220.f);

	if (tutorialCount > 5)
	{
		switch (dustCount % 9)
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
			dustCount = 0;
			if (tutorialCount == 6)
			{
				tutorialCount++;
			}
			break;

		default:
			break;
		}
		if (tutorialCount >= 6)
		{
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
		}
	}


	if (tutorialCount > 10)
	{
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
	}


	getbullet();

	if (State::m_input->IsPressed((SDL_SCANCODE_M)))
	{
		State::m_game->Change(LV_MainMenu);
	}
	UpdatePhysics(dt);
	UpdateCustomPhysics(dt);
	Render(dt);
}

void Tutorial::UpdateUltraFineDust(CustomBaseObject* mDust)
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

				if (tutorialCount == 8)
				{
					tutorialCount++;
				}
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
				if (tutorialCount > 8)
				{
					heartCount--;
				}
				mDust->isRed = false;
			}
			else if (man.transform.position.x > right_ultra)
			{
				mDust->isRed = false;
				if(tutorialCount>8)
				{
					heartCount--;
				}
				if (tutorialCount == 10)
				{
					tutorialCount++;
				}
			}

		}
		float distanceUtlraX = abs(mDust->transform.position.x - man.transform.position.x);
		float distanceUtlraY = abs(mDust->transform.position.y - man.transform.position.y);

		if (red > 0)
		{
			if (0 < distanceUtlraX && distanceUtlraX < 100 && 0 < distanceUtlraY &&distanceUtlraY < 100)
			{
				mDust->transform.position.Set(0, -500, 0.f);
				dustCount++;
				red = 0;
				mDust->isDead = true;
				if (tutorialCount == 9)
				{
					tutorialCount++;
				}
			}
			else if (man.transform.position.x > mDust->transform.position.x && distanceUtlraX < 330.f && distanceUtlraY < 100.f)
			{
				ScaleX -= 10;
				mDust->transform.position.Set(0, -500, 0.f);
				CleanGauge1.transform.SetScale(ScaleX, 60);
				failDust++;
				red = 0;
				return getbullet();
			}
		}
		else if (man.transform.position.x > mDust->transform.position.x&& distanceUtlraX < 330.f && distanceUtlraY < 100.f)
		{
			if(tutorialCount > 6)
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

}
void Tutorial::getbullet()
{
	UpdateUltraFineDust(ultrafinedust);
	UpdateUltraFineDust(ultrafinedust2);
	UpdateUltraFineDust(ultrafinedust3);
}

void Tutorial::Close()
{
	RemoveObject(ultrafinedust);
	RemoveObject(ultrafinedust2);
	RemoveObject(ultrafinedust3);
	RemoveObject(&tutorialakf);
	ClearBaseState();
}

