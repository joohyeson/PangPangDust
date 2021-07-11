/******************************************************************************/
/*!
\file   RegisterComponents.cpp
\author Hun Yang
\*modify Kim Ha Gyeong, Son Ju Hye, Lee Ui Jin
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/03/25
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "engine\State.h"
#include "RegisterComponents.h"
#include "engine/ComponentBuilder.h"
#include "DemoUIButton.h"
#include "ShootBulletController.h"
#include "Level4Controller.h"
#include "TutorialCoutroller.h"

void RegisterComponents()
{
    State::AddComponentBuilder( eComponentTypes::DemoUIButton,
                                new ComponentTBuilder<DemoUIButton>());
	State::AddComponentBuilder(eComponentTypes::ShootBulletController,
		new ComponentTBuilder<ShootBulletController>());
	State::AddComponentBuilder(eComponentTypes::TutorialController,
		new ComponentTBuilder<TutorialController>());
		State::AddComponentBuilder(eComponentTypes::Level4Controller,
		new ComponentTBuilder<Level4Controller>());
}

void UnregisterComponents()
{
    State::RemoveComponentBuilder(eComponentTypes::DemoUIButton);
	State::RemoveComponentBuilder(eComponentTypes::ShootBulletController);
	State::RemoveComponentBuilder(eComponentTypes::TutorialController);
	State::RemoveComponentBuilder(eComponentTypes::Level4Controller);
}
