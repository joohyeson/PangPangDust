/******************************************************************************/
/*!
\file   ShootBulletController.cpp
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo

\modify Son Ju Hye
\email : juhye.son@gamilc.com
\second modify Choi JaeWoo
\date  4/30

controller for game
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "ShootBulletController.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "Bullet.h"
#include "Color.h"
#include "Game.h"
#include "ContactData.h"
#include "CustomPhysics.h"
#include "Level1.h"

CustomBaseObject wall;
int jumpcount = 3; // to limit jump upto 3
extern int bullet_count;

ShootBulletController::ShootBulletController() :
	Component(eComponentTypes::ShootBulletController),
	mSpriteRotationOffset(90.f),
	mMaximumSpeed(30.f),
	mReshotCount(0.5f),
	mBulletSpeed(100.f),
	mBulletLifeCount(0.7f),
	mMaxHealth(3),
	mDamagedCount(2.5f),
	mDeathCount(1.5f),
	mGameOverCount(2.f),
	mInputs(nullptr),
	mWalkSpeed(13.f),
	mJumpWalkSpeed(5.0f),
	mJumpSpeed(40.f),
	mMinJumpSpeed(40.f), mMaxFallingSpeed(-15), mState(eDemoTopdownPlayerState::Normal),

	mStateMove(eDemoControllerState::Stand),
	mStateTimer(0),
	mTimer(0),
	mHealth(0)
{
}

ShootBulletController::~ShootBulletController()
{
	mOwner->sprite.color.a = 255;
	delete[]mHealthObjects;
}

void ShootBulletController::Initialize()
{
	// set pointer to custom physics component
	mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);

    mShootSound.SetName("shootSound");
    mShootSound.sound.LoadSound("sound/beep.wav");
    mShootSound.sound.SetVolume(50);
	mGameOverScreen = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("GameOverScreen"));

	// health objects (HUD) initialize
	mHealth = mMaxHealth;
	mHealthObjects = new CustomBaseObject*[mMaxHealth];


	// set Player's contact user data
	ContactData* data = new ContactData;
	data->Type = eContactTypes::Player;
	data->NumContacts = 0;
	data->Owner = dynamic_cast<CustomBaseObject*>(mOwner);
	dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.SetContactUserData(data);
	// if there is something in mInputs, delete them
	if (mInputs)
	{
		delete mInputs;
		mInputs = nullptr;
	}

	// allocate inputs
	mInputs = new bool[static_cast<int>(eDemoKeyInput::Count)];
	for (int i = 0; i < static_cast<int>(eDemoKeyInput::Count); ++i)
	{
		mInputs[i] = false;
	}

	// Store custom physics
	mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);
}

void ShootBulletController::Update(float dt)
{
	CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);


	switch (mState)
	{
	case eDemoTopdownPlayerState::Normal:
		inputUpdate(dt);
		if (owner->customPhysics.mContactData->NumContacts > 0)
		{
			applyDamage(1);
		}
		break;
	case eDemoTopdownPlayerState::Damaged:
		inputUpdate(dt);
		mStateTimer += dt;
		if (mStateTimer >= mDamagedCount)
		{
			mState = eDemoTopdownPlayerState::Normal;
			mStateTimer = 0.f;
			mOwner->sprite.color.a = 255;
			owner->customPhysics.mContactData->NumContacts = 0;
		}
		break;

	case eDemoTopdownPlayerState::GameOver:
		mTimer += dt;
		if (mTimer > mGameOverCount)
		{
			State::sCurrentState->m_game->Change(LV_MainMenu);
		}
		break;

	default:
		break;
	}
	b2Vec2 newVelocity = mPhysics->GetVelocity();

	// if there is no foot sensor, just set on ground
	if (mPhysics->mSensorContactData.empty())
	{
		mbIsGroundOn = true;
	}
	else
	{
		// if foot sensor contact with something, set on ground.
		mbIsGroundOn = (mPhysics->mSensorContactData[0]->NumContacts > 0);
	}


	// Update player velocity based on current state
	switch (mStateMove)
	{
	case eDemoControllerState::Stand:
	{
		// set velocity zero
		newVelocity.SetZero();
		// floating in the air
		if (!mbIsGroundOn)
		{
			mStateMove = eDemoControllerState::Jump;
		}

		// walk
		if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)]
			!= mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
		{
			mStateMove = eDemoControllerState::Walk;
		}
		// jump
		else if (mInputs[static_cast<int>(eDemoKeyInput::Jump)])
		{
			if (jumpcount > 0)
			{
				newVelocity.y = mJumpSpeed;
				owner->customPhysics.SetVelocity(newVelocity);
				mStateMove = eDemoControllerState::Jump;
				jumpcount--;
			}
			else if (owner->customPhysics.HasBody()) 
			{
				if (owner->customPhysics.IsColliding()) //if collide with wall
				{
					jumpcount = 3; // to limit jump upto 3
				}
			}
		}
		if (mInputs[static_cast<int>(eDemoKeyInput::GoDown)])
		{
			newVelocity.y = mMaxFallingSpeed;
			owner->customPhysics.SetVelocity(newVelocity);
			mStateMove = eDemoControllerState::Down;
		}
	}
	break;
	case eDemoControllerState::Walk:
	{
		// walk
		if (mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
		{
			newVelocity.x = mWalkSpeed;
			// animation flip off
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_NONE;
		}
		else if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)])
		{
			newVelocity.x = 0;
			// animation flip on
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			mStateMove = eDemoControllerState::Stand;
			newVelocity.SetZero();
			owner->customPhysics.SetVelocity(newVelocity);
		}

		// jump
		if (mInputs[static_cast<int>(eDemoKeyInput::Jump)])
		{
			if (jumpcount > 0)
			{
				newVelocity.y = mJumpSpeed;
				owner->customPhysics.SetVelocity(newVelocity);
				mStateMove = eDemoControllerState::Jump;
				jumpcount--;
			}
			else if (owner->customPhysics.HasBody())
			{
				if (owner->customPhysics.IsColliding()) // if collide with wall
				{
					jumpcount = 3; // to limit jump upto 3
				}
			}
		}
		if (mInputs[static_cast<int>(eDemoKeyInput::GoDown)])
		{
			newVelocity.y = mMaxFallingSpeed;
			owner->customPhysics.SetVelocity(newVelocity);
			mStateMove = eDemoControllerState::Down;
		}
	}
	break;
	case eDemoControllerState::Jump:
	{

		printf("[Velocity: %.2f, %.2f]\n", newVelocity.x, newVelocity.y);
		newVelocity.y = std::max(newVelocity.y, mMaxFallingSpeed);
		if (!mInputs[static_cast<int>(eDemoKeyInput::Jump)]
			&& newVelocity.y > 0)
		{
			newVelocity.y = std::min(newVelocity.y, mMinJumpSpeed);
			owner->customPhysics.SetVelocity(newVelocity);
		}

		// walk
		if (mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
		{
			newVelocity.x = mJumpWalkSpeed;
			// animation flip off
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_NONE;
		}
		else if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)])
		{
			newVelocity.x = 0;
			// animation flip on
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			newVelocity.x = 0;
			owner->customPhysics.SetVelocity(newVelocity);
		}
		// stand
		if (mbIsGroundOn)
		{
			mStateMove = eDemoControllerState::Stand;
		}
		if (mInputs[static_cast<int>(eDemoKeyInput::GoDown)])
		{
			newVelocity.y = mMaxFallingSpeed;
			owner->customPhysics.SetVelocity(newVelocity);
			mStateMove = eDemoControllerState::Down;
		}
	}
	break;
	case eDemoControllerState::Down:
	{
		printf("[Velocity: %.2f, %.2f]\n", newVelocity.x, newVelocity.y);
		newVelocity.y = std::max(newVelocity.y, mMaxFallingSpeed);
		if (!mInputs[static_cast<int>(eDemoKeyInput::GoDown)]
			&& newVelocity.y < 0)
		{
			newVelocity.y = std::min(newVelocity.y, mMinJumpSpeed);
			owner->customPhysics.SetVelocity(newVelocity);
		}

		// walk
		if (mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
		{
			newVelocity.x = mJumpWalkSpeed;
			// animation flip off
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_NONE;
		}
		else if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)])
		{
			newVelocity.x = 0;
			// animation flip on
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			newVelocity.x = 0;
			owner->customPhysics.SetVelocity(newVelocity);
		}
		// stand
		if (mbIsGroundOn)
		{
			mStateMove = eDemoControllerState::Stand;
		}
	}
	default:
		break;
	}


}

void ShootBulletController::inputUpdate(float dt)
{
	CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);
	b2Vec2 velocity(owner->customPhysics.GetVelocity());


	// mouse is not on button
	auto MousePos = State::m_input->GetMousePos();
	MousePos.x = MousePos.x - State::m_game->m_width   * 0.5f + State::sCurrentState->m_pCamera->position.x;
	MousePos.y = State::m_game->m_height * 0.5f - MousePos.y + State::sCurrentState->m_pCamera->position.y;
	b2Vec2 player(owner->transform.position.x, owner->transform.position.y);
	b2Vec2 direction = MousePos - player;
	direction.Normalize();
	// Update Input key

	mInputs[static_cast<int>(eDemoKeyInput::GoLeft)] = State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_A);
	mInputs[static_cast<int>(eDemoKeyInput::GoRight)] =true;
	mInputs[static_cast<int>(eDemoKeyInput::GoDown)] = State::sCurrentState->m_input->IsTriggered(SDL_SCANCODE_S);
	mInputs[static_cast<int>(eDemoKeyInput::Jump)] =
		State::sCurrentState->m_input->IsTriggered(
			_SPACE) ||
		State::sCurrentState->m_input->IsTriggered(SDL_SCANCODE_W);


	// Apply new velocity
	//mOwner->physics.SetVelocity(newVelocity);
	// Shoot bullet
	mTimer += dt;

	if (State::sCurrentState->m_input->IsPressed(SDL_BUTTON_LEFT))
	{
		// if timer is over reshot count (second), shoot bullet again
		if (bullet_count > 0 && bullet_count <= 3)
		{
			if (mTimer >= mReshotCount)
			{
				mTimer = 0;
				shoot(direction);
				bullet_count--;
               
                mShootSound.sound.Play();
			}

		}
	}

	owner->customPhysics.GetBody()->SetLinearDamping(1.0f);

}

void ShootBulletController::shoot(const b2Vec2& direction)
{
	CustomBullet *newBullet = new CustomBullet;
 
	newBullet->SetName("Bullet");
	newBullet->transform.position.Set(
		mOwner->transform.position.x + direction.x * (mOwner->transform.GetHalfScale().x + 10.f),
		mOwner->transform.position.y + direction.y * (mOwner->transform.GetHalfScale().y + 10.f), 0.f);
	newBullet->transform.SetScale(48.f, 48.f);
	newBullet->transform.rotation = mOwner->transform.rotation;

    

	newBullet->sprite.color = Color::WHITE;
	newBullet->sprite.LoadImage("texture/WaterBomb.png", State::m_renderer);
	newBullet->customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &newBullet->transform);
	ContactData* userData = new ContactData;
	userData->Type = eContactTypes::Bullet;
	userData->NumContacts = 0;
	userData->Owner = newBullet;
	newBullet->customPhysics.SetContactUserData(userData);

	newBullet->mLifeCount = 0.7f;
	//State::sCurrentState->AddComponentToObject(newBullet, eComponentTypes::DemoWrapPosition);
	State::sCurrentState->AddDynamicObjectAndInitialize(newBullet);
	State::sCurrentState->AddCustomPhysicsComponent(newBullet);

  

    
	// Have bullet move in the direction the turret is facing
	newBullet->customPhysics.SetVelocity(direction.x * mBulletSpeed, direction.y * mBulletSpeed);
	printf("Velocity: %.2f, %.2f\n", newBullet->customPhysics.GetVelocity().x, newBullet->customPhysics.GetVelocity().y);
	newBullet->customPhysics.ActiveGhostCollision(false);
	//newBullet->isDead = true;
	//Level1::getbullet(newBullet);
	if (toShootBullet == nullptr)
	{
		toShootBullet = newBullet;

	}

}

void ShootBulletController::applyDamage(int damage)
{
	if (mState == eDemoTopdownPlayerState::Normal)
	{
		for (int i = mHealth - 1; i >= 0 && i >= (mHealth - static_cast<int>(damage)); --i)
		{
			mHealthObjects[i]->sprite.color.a = 0;
		}
		mHealth -= damage;
		if (mHealth > 0)
		{
			mState = eDemoTopdownPlayerState::Damaged;
			mTimer = 0;
			mOwner->sprite.color.a /= 2;
		}
		else
		{
			mState = eDemoTopdownPlayerState::Dead;
			mTimer = 0;
			CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);
			owner->customPhysics.bodyType = CustomPhysics::STATIC;
			owner->customPhysics.GetBody()->SetType(b2BodyType::b2_staticBody);
		}
	}
}

eDemoTopdownPlayerState ShootBulletController::GetControllerState() const
{
	return mState;
}
