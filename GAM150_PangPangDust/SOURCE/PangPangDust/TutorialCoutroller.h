#pragma once
/******************************************************************************/
/*!
\file   TutorialCountroller.h
\author Hun Yang
\modify Kim Ha Gyeong
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   5/30
controller for tutorial
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include "Level1.h"
enum class eDemoTopdownPlayerState2
{
	Normal,
	Damaged,
	Dead,
	GameOver,
};

enum class eDemoControllerState2
{
	Stand,
	Walk,
	Jump,
	Count,
	Down
};

enum class eDemoKeyInput2
{
	GoLeft,
	GoRight,
	GoDown,
	Jump,
	Count
};

struct b2Vec2;
class CustomBaseObject;
class CustomPhysics;
extern eDemoTopdownPlayerState    mState;
extern float               mTimer;
extern CustomBaseObject*   mGameOverScreen;
class TutorialController : public Component
{
public:
	TutorialController();
	~TutorialController();
	virtual void Initialize()       override;
	virtual void Update(float dt)   override;
	eDemoTopdownPlayerState GetControllerState() const;
private:
	void inputUpdate(float dt);
	void shoot(const b2Vec2& direction);
	void applyDamage(int damage);
public:
	float               mSpriteRotationOffset;
	float               mMaximumSpeed;
	float               mReshotCount;
	float               mBulletSpeed;
	float               mBulletLifeCount;
	int                 mMaxHealth;
	float               mDamagedCount;
	float               mDeathCount;
	float               mGameOverCount;
	bool* mInputs;
	float                   mWalkSpeed;
	float                   mJumpWalkSpeed;
	float                   mJumpSpeed;
	float                   mMinJumpSpeed;
	float mMaxFallingSpeed;
private:
	CustomPhysics*      mPhysics;
	eDemoTopdownPlayerState    mState;
	eDemoControllerState mStateMove;
	float               mStateTimer;
	float               mTimer;
	int                 mHealth;
	CustomBaseObject*   mGameOverScreen;
	CustomBaseObject**  mHealthObjects;

	bool                    mbIsGroundOn;
};
