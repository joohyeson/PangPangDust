/******************************************************************************/
/*!
\file  Level3.h
\author Lee Ui Jin
\par    email: digipen.uijin@gmail.com
\date   2019/06/11

stage 3
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "CustomBaseObject.h"
#include  "ShootBulletController.h"

class CustomBullet;
CustomBaseObject& CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);

extern  CustomBaseObject wall;
extern CustomBaseObject man;
extern Object* toShootBullet;

class Level3 : public State
{
	friend class Game;

protected:

	Level3() : State() {};
	~Level3() override {};

	void ControlAudios();
	void Initialize() override;
	void Update(float dt) override;
	void getbullet();
	CustomBaseObject& CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
		float scaleX, float scaleY, const char* filePath, bool isVisible);
	CustomBaseObject& Level3::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);
	CustomBaseObject& CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY);
	Object& CreateFineDust(Object& finedust, const char* name, float positionX, float positionY);
	void MoveFineDust(Object& finedust);
	void EatFineDust(Object& finedust, float positioX, float positionY);
	CustomBaseObject& CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY);
	void UpdateUltraFineDust(CustomBaseObject* mDust);
	void UpdateMiniWall(class CustomBaseObject* mWall);
	void Close() override;

private:
	const int period = 180;

	CustomBaseObject man, wall3, wall4, wall5, CleanGauge1, CleanGauge2, MiniWall1, MiniWall2, MiniWall3, MiniWall4,
		MiniWall5, MiniWall6, MiniWall7, MiniWall8, MiniWall9, MiniWall10, MiniWall11, MiniWall12, MiniWall13, MiniWall14, BulletGauge, BulletCountImage, PlayerHeart, robot_vacuum, itemnagative, itemnagative2, goggles;
    
	Music backGroundMusic;

	CustomBaseObject* ultrafinedust = nullptr;
	CustomBaseObject* ultrafinedust2 = nullptr;
	CustomBaseObject* ultrafinedust3 = nullptr;
	CustomBaseObject* ultrafinedust4 = nullptr;
	CustomBaseObject* ultrafinedust5 = nullptr;
	CustomBaseObject* ultrafinedust6 = nullptr;
	CustomBaseObject* ultrafinedust7 = nullptr;
	CustomBaseObject* ultrafinedust8 = nullptr;
	CustomBaseObject* ultrafinedust9 = nullptr;
	CustomBaseObject* ultrafinedust10 = nullptr;

    Object eatSound;

	bool ultra1 = false;
	bool ultra2 = false;
	bool ultra3 = false;
	bool ultra4 = false;
	bool ultra5 = false;
	bool ultra6 = false;
	bool ultra7 = false;
	bool ultra8 = false;
	bool ultra9 = false;
	bool ultra10 = false;

	bool afterCount = false;
	Object dust, background, FineDust1, FineDust2, FineDust3, FineDust4, FineDust5, FineDust6, FineDust7, FineDust8, FineDust9, FineDust10, CheckPoint, iteamheart, potion, miss3;
	CustomBaseObject gameOverScreen;

	bool isEmptyLoaded1 = false;
	bool isEmptyLoaded2 = false;
	bool isEmptyLoaded3 = false;
	bool isEmptyLoaded4 = false;
	bool isEmptyLoaded5 = false;
	bool isEmptyLoaded6 = false;
	bool isEmptyLoaded7 = false;
	bool isEmptyLoaded8 = false;
	bool isEmptyLoaded9 = false;
	bool isEmptyLoaded10 = false;

};

