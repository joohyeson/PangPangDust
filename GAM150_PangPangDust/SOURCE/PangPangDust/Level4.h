#pragma once
/******************************************************************************/
/*!
\file  Level4.h
\author Kim Ha Gyeong
\par    email: digiepn.hagyoeng@gmail.com
\date   2019/06/11

stage 4
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "CustomBaseObject.h"

class CustomBullet;
CustomBaseObject& CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);

extern  CustomBaseObject wall;
extern CustomBaseObject man;
extern Object* toShootBullet;

class Level4 : public State
{
	friend class Game;

protected:

	Level4() : State() {};
	~Level4() override {};

	void ControlAudios();
	void Initialize() override;
	void Update(float dt) override;
	void getbullet();
	CustomBaseObject& CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
		float scaleX, float scaleY, const char* filePath, bool isVisible);
	CustomBaseObject& Level4::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);
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
		MiniWall5, MiniWall6, MiniWall7, MiniWall8, MiniWall9, MiniWall10, MiniWall11, MiniWall12, MiniWall13, MiniWall14, MiniWall15, MiniWall16, MiniWall17, MiniWall18, MiniWall19, MiniWall20, PlayerHeart;
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
	CustomBaseObject* ultrafinedust11 = nullptr;
	CustomBaseObject* ultrafinedust12 = nullptr;
	CustomBaseObject* ultrafinedust13 = nullptr;
	CustomBaseObject* ultrafinedust14 = nullptr;
	CustomBaseObject* ultrafinedust15 = nullptr;
	CustomBaseObject* ultrafinedust16 = nullptr;
	CustomBaseObject* ultrafinedust17 = nullptr;
	CustomBaseObject* ultrafinedust18 = nullptr;
	CustomBaseObject* ultrafinedust19 = nullptr;
	CustomBaseObject* ultrafinedust20 = nullptr;
	CustomBaseObject* ultrafinedust21 = nullptr;
	CustomBaseObject* ultrafinedust22 = nullptr;
	CustomBaseObject* ultrafinedust23 = nullptr;


	Object dust, background, CheckPoint, iteamheart, miss4, time;
	CustomBaseObject gameOverScreen;
};

