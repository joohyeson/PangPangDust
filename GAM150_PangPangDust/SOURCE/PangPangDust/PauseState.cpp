/******************************************************************************/
/*!
\file  PauseState.cpp
\author Son Ju Hye
\par    email: juhye.son990902@gmail.com
\date   2019/06/11

transition for next stage

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"

void PauseState::Initialize()
{
	clapSound.sound.LoadSound("sound/clap.wav");
	clapSound.sound.Play();
	m_backgroundColor = {255,192,203,255};
	camera.position.Set(0, 0, 0);

	mainFont = TTF_OpenFont("font/Default.ttf", 48);
	image.sprite.LoadImage("texture/NextStage.png", m_renderer);
	image.transform.SetScale(1000,500);
	image.sprite.SetFrame(2);
	image.sprite.SetSpeed(2);
	image.sprite.activeAnimation = true;
	AddObject(&image);
}

void PauseState::Update(float dt)
{
	/******************* State ******************/
  
	// Move to level1 by pressing 'R' key
	static int i=0;
	if (m_input->IsTriggered(SDL_SCANCODE_SPACE))
		m_game->Resume();
	if (State::m_input->IsTriggered((SDL_SCANCODE_SPACE)))
	{
		if(i==0)
		{
			i++;
			State::m_game->Change(LV_Level2);
		}
		else if (i == 1)
		{
			i++;
			State::m_game->Change(LV_Level3);
		}
		else if (i == 2)
		{
			i++;
			State::m_game->Change(LV_Level4);
		}

	}
	UpdatePhysics(dt);
	Render(dt);
}

void PauseState::Close()
{
	ClearBaseState();
}
