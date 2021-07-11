/******************************************************************************/
/*!
\file   Credit.cpp
\author Son Ju Hye
\second author Kim Ha Gyeong
\par    email: juhye.son990902@gamil.com
\par    GAM150 
\date   5/15

Credit page
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"


const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

void CreditPage::Initialize()
{
    State::sCurrentState = this;
    camera.position.Set(0, 0, 0);
    mainFont = TTF_OpenFont("font/Default.ttf", 48);
    animation.SetName("Walking boy");
    animation.transform.position.Set(-300.f, 0.f, 0.f);
    animation.transform.SetScale(128, 200);
    animation.transform.rotation = 45.F;
    animation.sprite.LoadImage("texture/1.png", State::m_renderer);
    animation.sprite.activeAnimation = true;
    animation.sprite.SetFrame(6);
    animation.sprite.SetSpeed(12.f);

    animation.transform.rotation = 0;

    background.SetName("Start");
    background.transform.SetScale(State::m_width, State::m_height);
    background.sprite.LoadImage("texture/creditending.png", State::m_renderer);

    letters.SetName("Text");
    letters.transform.position.Set(0, -200, 0);
    letters.transform.SetScale(650, 128);

    AddObject(&background);	
    AddObject(&letters);	
    AddObject(&animation);


    InitializeObjects();
}

void CreditPage::Update(float dt)
{
    TransformObjects(dt);
    UpdateObjects(dt);
    auto MousePos = State::m_input->GetMousePos();
    animation.transform.position.Set(MousePos.x - 650, -MousePos.y + 300, 0);
    static float time = 0;
    time += dt;

	printf("%f\n", time);

    if (time > 8) // if 8 seconds passes
    {
		background.sprite.Free();
		background.sprite.LoadImage("texture/credit2.png", State::m_renderer);
		if (time > 15)
		{
			time = 0;
			m_game->Change(LV_MainMenu);
		}
    }
    UpdatePhysics(dt);
    Render(dt);
}

void CreditPage::Close()
{
    ClearBaseState();
}

void CreditPage::TransformObjects(float dt)
{
    static const float pixels_per_second = 64.0f;
    static bool scaleUp = true;
    float newDt = dt * pixels_per_second;
    animation.transform.position.x += newDt;
}

