/******************************************************************************/
/*!
\file   Bullet.cpp
\author Jay Austria
\modify Lee Ui jin
\second modify Son Ju Hye
\par    email: noyoucannot\@gmail.com
\par    GAM150 demo
\par	v0
\date   2018/03/28

Example that shows very simple dynamic object creation and handling of dynamic
objects, which is useful for short lived objects such as bullets.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "Bullet.h"
#include "Game.h"
#include "engine/Object.h"
#include "ContactData.h"

char GetRandomCharacter();

bool Bullet::IsOffscreen() const
{
    float halfWidth = Game::SCREEN_WIDTH / 2.f;
    float halfHeight = Game::SCREEN_HEIGHT / 2.f;
    bool isOnscreen = transform.position.x > -halfWidth &&
        transform.position.x < halfWidth &&
        transform.position.y > -halfHeight &&
        transform.position.y < halfHeight;
    return !isOnscreen;
}

void Bullet::Update(float /*dt*/)
{
    if (!IsOffscreen()) return;
    // Delete this object from current state
    this->isDead = true;
}

char GetRandomCharacter()
{
    char randomCharacter = static_cast<char>((rand() % static_cast<int>(UCHAR_MAX + 1)));
    return randomCharacter;
}

CustomBullet::CustomBullet():
    mLifeCount(0),
    mTimer(0)
{
}

void CustomBullet::Update(float dt)
{
    mTimer += dt;
	if (toShootBullet == nullptr) // the state of shooting
	{
		printf("[Bullet Die nullptr]\n");
		mTimer = 0;
		this->isDead = true;
		customPhysics.ActivePhysics(false);
	}
	else if ((mTimer >= mLifeCount) ||
		// collide with enemy
		(customPhysics.mContactData->NumContacts))
	{
		toShootBullet = nullptr;
		printf("[Bullet Die]\n");
		mTimer = 0;
		this->isDead = true;
		customPhysics.ActivePhysics(false);
	}
}

void CustomBullet::Initialize()
{
    Object::Initialize();
}
