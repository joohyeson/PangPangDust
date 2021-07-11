/******************************************************************************/
/*!
\file  Level2.h
\author Choi Jae Woo
\par    email: wod6983@gmail.com
\date   2019/06/5

stage 2
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
extern Object* uijin_;
class Level2 : public State
{
    friend class Game;

protected:

    Level2() : State() {};
    ~Level2() override {};

    void ControlAudios();
    void Initialize() override;
    void Update(float dt) override;
    void getbullet();
    CustomBaseObject& CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
        float scaleX, float scaleY, const char* filePath, bool isVisible);
    CustomBaseObject& Level2::CreateShootPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY);
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
        MiniWall5, MiniWall6, MiniWall7,BulletGauge, BulletCountImage, PlayerHeart, robot_vacuum, itemnagative, item_rain;
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
    Object dust, background, FineDust1, FineDust2, FineDust3, FineDust4, FineDust5, FineDust6, FineDust7, FineDust8, FineDust9, FineDust10, CheckPoint, iteamheart, miss2;
    CustomBaseObject gameOverScreen;
};

