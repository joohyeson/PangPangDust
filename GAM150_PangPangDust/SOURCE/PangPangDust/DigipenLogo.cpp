/******************************************************************************/
/*!
\file   DigipenLogo.cpp
\author Son Ju Hye
\par    email: juhye.son990902@gamil.com
\par    GAM150
\date   5/15

logo page
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "CommonLevel.h"

#include "DigipenLogo.h"
#include "Color.h"

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

void DigipenLogoPage::Initialize()
{
	State::sCurrentState = this;
	camera.position.Set(0, 0, 0);

	background.SetName("Start");
	background.transform.SetScale(500, 250);
	m_backgroundColor = { 0,0,0,0 };
	background.sprite.LoadImage("texture/DigiPen_WHITE_1024px.png", State::m_renderer);

	// This is the actual rendering order
	AddObject(&background);	

	InitializeObjects();
}

void DigipenLogoPage::Update(float dt)
{

	/******************* State ******************/
	UpdateObjects(dt);
	static float time = 0;
	time += dt;
	// Pause current state and move to pause state

	if (time > 2)
	{
		background.sprite.Free();
		background.sprite.LoadImage("texture/99Logo.png", State::m_renderer);
		if (time > 4)
		{
			static float time2 = 0;
			time2 += dt;

			if (time2 > 2)
			{
				background.sprite.Free();
				background.sprite.LoadImage("texture/intro0.png", State::m_renderer);
				if (time2 > 4)
				{
					background.sprite.Free();
					background.sprite.LoadImage("texture/intro1.png", State::m_renderer);
					if (time2 > 7)
					{
						background.sprite.Free();
						background.sprite.LoadImage("texture/intro2.png", State::m_renderer);
						if (time2 > 9)
						{

							m_game->Change(LV_MainMenu);
						}
					}
				}
			}
		}
	}
	UpdatePhysics(dt);
	Render(dt);
}

void DigipenLogoPage::Close()
{
	ClearBaseState();
}
