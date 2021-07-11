#pragma once
/******************************************************************************/
/*!
\file  Tutorial.h
\author Kim Ha Gyeong
\par    email: digiepn.hagyoeng@gmail.com
\date   2019/06/11

stage Tutorial

*****YOU CANNOT MODIFY THIS FILE!!*****
*/
/******************************************************************************/
#include "engine\State.h"
#include "engine\Object.h"
#include "CustomBaseObject.h"
class CustomBullet;
CustomBaseObject& CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);

extern  CustomBaseObject wall;
extern CustomBaseObject man;
extern Object* toShootBullet;

class Tutorial : public State
{
	friend class Game;

protected:

	Tutorial() : State() {};
	~Tutorial() override {};

	void Initialize() override;
	void Update(float dt) override;
	void getbullet();

	CustomBaseObject& Tutorial::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);
	CustomBaseObject& CreateMiniwall(CustomBaseObject& miniwall, const char* name, float scaleX, float scaleY, float positionX, float positionY);
	void UpdateMiniWall(class CustomBaseObject* mWall);
	Object& CreateFineDust(Object& finedust, const char* name, float positionX, float positionY);
	void MoveFineDust(Object& finedust);
	void EatFineDust(Object& finedust, float positioX, float positionY);
	CustomBaseObject& CreateUltraFineDust(CustomBaseObject* ultraFineDust, const char* name, float positionX, float positionY);
	void UpdateUltraFineDust(CustomBaseObject* mDust);

	void Close() override;

private:
	const int period = 180;
	float ellapsedtime = 0.0f;

	CustomBaseObject man, wall3, wall4, wall5, CleanGauge1, CleanGauge2, MiniWall1, MiniWall2, MiniWall3, MiniWall4,
		MiniWall5, BulletGauge, BulletCountImage, PlayerHeart;

	Music backGroundMusic;

	CustomBaseObject* ultrafinedust = nullptr;
	CustomBaseObject* ultrafinedust2 = nullptr;
	CustomBaseObject* ultrafinedust3 = nullptr;

	Object background, FineDust1, FineDust2, FineDust3, FineDust4, FineDust5, CheckPoint , tutorialdywjd, tutorialakf;
	CustomBaseObject gameOverScreen;
};

