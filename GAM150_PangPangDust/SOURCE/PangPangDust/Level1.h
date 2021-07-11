/******************************************************************************/
/*!
\file  Level1.h
\author Son Ju Hye
\par    email: juhye.son990902@gmail.com
\date   2019/06/11

stage 1

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

class Level1 : public State
{
	friend class Game;

protected:

	Level1() : State() {};
	~Level1() override {};

	void Initialize() override;
	void Update(float dt) override;
	void getbullet();
	CustomBaseObject& CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
		float scaleX, float scaleY, const char* filePath, bool isVisible);
    CustomBaseObject& Level1::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);
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
	MiniWall5, MiniWall6, MiniWall7, BulletGauge, BulletCountImage, PlayerHeart, robot_vacuum, itemnagative, BulletCountX;

    CustomBaseObject BulletCountBomb;

    Music backGroundMusic, eatDustMusic;

	CustomBaseObject* ultrafinedust = nullptr;
	CustomBaseObject* ultrafinedust2 = nullptr;
	CustomBaseObject* ultrafinedust3 = nullptr;
	CustomBaseObject* ultrafinedust4 = nullptr;
	CustomBaseObject* ultrafinedust5 = nullptr;

	
	Object dust, background, FineDust1, FineDust2, FineDust4, FineDust5, FineDust7, FineDust8, FineDust9, FineDust10, CheckPoint, iteamheart, miss, eatSound, WaterBombSound;
	CustomBaseObject gameOverScreen;
};

