/******************************************************************************/
/*!
\file   RegisterComponents.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\*modify Kim Ha Gyeong, Son Ju Hye, Lee Ui Jin
\par    GAM150 demo
\date   2019/03/26

This function register every component builder to State.
Every component must be addded here.
This will be executed in Game::Initialize() only once.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once


void RegisterComponents(void);

void UnregisterComponents(void);