/******************************************************************************/
/*!
\file   Level4Countroller.cpp
\author Hun Yang
\modify Kim Ha Gyeong
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   5/30
controller for tutorial

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "TutorialCoutroller.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "Bullet.h"
#include "Color.h"
#include "Game.h"
#include "ContactData.h"
#include "CustomPhysics.h"
#include "Level1.h"
#include "Level4Controller.h"

//Most functions are the same with shootbulletcontroller.

int jumpCountLeve4 = 3;
extern int countt;

Level4Controller::Level4Controller() :
	Component(eComponentTypes::Level4Controller),
	mSpriteRotationOffset(90.f),
	mMaximumSpeed(30.f),
	mReshotCount(0.5f),
	mBulletSpeed(70.f),
	mBulletLifeCount(0.7f),
	mMaxHealth(3),
	mDamagedCount(2.5f),
	mDeathCount(1.5f),
	mGameOverCount(2.f),
	mInputs(nullptr),
	mWalkSpeed(30.f),
	mJumpWalkSpeed(5.0f),
	mJumpSpeed(40.f),
	mMinJumpSpeed(40.f), mMaxFallingSpeed(-15), mState(eDemoTopdownPlayerState::Normal),

	mStateMove(eDemoControllerState::Stand),
	mStateTimer(0),
	mTimer(0),
	mHealth(0)
{
}

Level4Controller::~Level4Controller()
{
	mOwner->sprite.color.a = 255;
	delete[]mHealthObjects;
}

void Level4Controller::Initialize()
{
	mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);

	mShootSound.SetName("shootSound");
	mShootSound.sound.LoadSound("sound/beep.wav");
	mShootSound.sound.SetVolume(50);

	mGameOverScreen = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("GameOverScreen"));
	mHealth = mMaxHealth;
	mHealthObjects = new CustomBaseObject*[mMaxHealth];

	ContactData* data = new ContactData;
	data->Type = eContactTypes::Player;
	data->NumContacts = 0;
	data->Owner = dynamic_cast<CustomBaseObject*>(mOwner);
	dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.SetContactUserData(data);
	if (mInputs)
	{
		delete mInputs;
		mInputs = nullptr;
	}

	mInputs = new bool[static_cast<int>(eDemoKeyInput2::Count)];
	for (int i = 0; i < static_cast<int>(eDemoKeyInput2::Count); ++i)
	{
		mInputs[i] = false;
	}

	mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);
}

void Level4Controller::Update(float dt)
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
			State::m_game->Change(LV_MainMenu);
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
		if (mInputs[static_cast<int>(eDemoKeyInput2::GoLeft)]
			!= mInputs[static_cast<int>(eDemoKeyInput2::GoRight)])
		{
			mStateMove = eDemoControllerState::Walk;
		}
		// jump
		else if (mInputs[static_cast<int>(eDemoKeyInput2::Jump)])
		{
				if (jumpCountLeve4 > 0)
				{
					newVelocity.y = mJumpSpeed;
					owner->customPhysics.SetVelocity(newVelocity);
					mStateMove = eDemoControllerState::Jump;
					jumpCountLeve4--;

				}
				else if (owner->customPhysics.HasBody())
				{
					if (owner->customPhysics.IsColliding())
					{
						jumpCountLeve4 = 3;
					}
				}
		}
		if (mInputs[static_cast<int>(eDemoKeyInput2::GoDown)])
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
			if(countt != 0)
			{
				if (mInputs[static_cast<int>(eDemoKeyInput2::GoRight)])
				{
					newVelocity.x = mWalkSpeed;
					owner->customPhysics.SetVelocity(newVelocity);
					mOwner->sprite.flip = SDL_FLIP_NONE;
				}
			}

		else if (mInputs[static_cast<int>(eDemoKeyInput2::GoLeft)])
		{
			newVelocity.x = 0;
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
		if (mInputs[static_cast<int>(eDemoKeyInput2::Jump)])
		{
				if (jumpCountLeve4 > 0)
				{
					newVelocity.y = mJumpSpeed;
					owner->customPhysics.SetVelocity(newVelocity);
					mStateMove = eDemoControllerState::Jump;
					jumpCountLeve4--;
				}
				else if (owner->customPhysics.HasBody())
				{
					if (owner->customPhysics.IsColliding())
					{
						jumpCountLeve4 = 3;
					}
				}
		}
		if (mInputs[static_cast<int>(eDemoKeyInput2::GoDown)])
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
		if (!mInputs[static_cast<int>(eDemoKeyInput2::Jump)]
			&& newVelocity.y > 0)
		{
			newVelocity.y = std::min(newVelocity.y, mMinJumpSpeed);
			owner->customPhysics.SetVelocity(newVelocity);
		}

		// walk
		if (mInputs[static_cast<int>(eDemoKeyInput2::GoRight)])
		{
			newVelocity.x = mJumpWalkSpeed;
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_NONE;
		}
		else if (mInputs[static_cast<int>(eDemoKeyInput2::GoLeft)])
		{
			newVelocity.x = 0;
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			newVelocity.x = 0;
			owner->customPhysics.SetVelocity(newVelocity);
		}
		if (mbIsGroundOn)
		{
			mStateMove = eDemoControllerState::Stand;
		}
		if (mInputs[static_cast<int>(eDemoKeyInput2::GoDown)])
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
		if (!mInputs[static_cast<int>(eDemoKeyInput2::GoDown)]
			&& newVelocity.y < 0)
		{
			newVelocity.y = std::min(newVelocity.y, mMinJumpSpeed);
			owner->customPhysics.SetVelocity(newVelocity);
		}

		// walk
		if (mInputs[static_cast<int>(eDemoKeyInput2::GoRight)])
		{
			newVelocity.x = mJumpWalkSpeed;
			// animation flip off
			owner->customPhysics.SetVelocity(newVelocity);
			mOwner->sprite.flip = SDL_FLIP_NONE;
		}
		else if (mInputs[static_cast<int>(eDemoKeyInput2::GoLeft)])
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

void Level4Controller::inputUpdate(float dt)
{
	CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);
	b2Vec2 velocity(owner->customPhysics.GetVelocity());

	auto MousePos = State::m_input->GetMousePos();
	MousePos.x = MousePos.x - State::m_game->m_width   * 0.5f + State::m_pCamera->position.x;
	MousePos.y = State::m_game->m_height * 0.5f - MousePos.y + State::m_pCamera->position.y;
	b2Vec2 player(owner->transform.position.x, owner->transform.position.y);
	b2Vec2 direction = MousePos - player;
	direction.Normalize();

	mInputs[static_cast<int>(eDemoKeyInput2::GoLeft)] = State::m_input->IsPressed(SDL_SCANCODE_A);
	mInputs[static_cast<int>(eDemoKeyInput2::GoRight)] = true;
	mInputs[static_cast<int>(eDemoKeyInput2::GoDown)] = State::m_input->IsTriggered(SDL_SCANCODE_S);
	mInputs[static_cast<int>(eDemoKeyInput2::Jump)] =
		State::m_input->IsTriggered(
			_SPACE) ||
		State::m_input->IsTriggered(SDL_SCANCODE_W);

	mTimer += dt;

	if (State::m_input->IsPressed(SDL_BUTTON_LEFT))
	{
			if (mTimer >= mReshotCount)
			{
				mTimer = 0;
				shoot(direction);
				mShootSound.sound.Play();

			}
	}
	owner->customPhysics.GetBody()->SetLinearDamping(1.0f);

}

void Level4Controller::shoot(const b2Vec2& direction)
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
	State::sCurrentState->AddDynamicObjectAndInitialize(newBullet);
	State::sCurrentState->AddCustomPhysicsComponent(newBullet);

	newBullet->customPhysics.SetVelocity(direction.x * mBulletSpeed, direction.y * mBulletSpeed);
	printf("Velocity: %.2f, %.2f\n", newBullet->customPhysics.GetVelocity().x, newBullet->customPhysics.GetVelocity().y);
	newBullet->customPhysics.ActiveGhostCollision(false);

	if (toShootBullet == nullptr)
	{
		toShootBullet = newBullet;

	}

}

void Level4Controller::applyDamage(int damage)
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

eDemoTopdownPlayerState Level4Controller::GetControllerState() const
{
	return mState;
}
