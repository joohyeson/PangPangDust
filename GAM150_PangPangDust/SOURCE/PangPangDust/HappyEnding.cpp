/******************************************************************************/
/*!
\file  HappyEnding.cpp
\author Lee Ui Jin, Choi Jae Woo
\par    email: digipen.uijin@gmail.com, wod6983@gmail.com
\date   2019/06/11

HappyEnding page

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include "Color.h"

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

class Object& HappyEnding::CreateHudText(class Object& textObject, const char* name, float positionX, float positionY, float scaleX, float scaleY, _TTF_Font* font, const char* textContents, struct SDL_Color color)
{
	textObject.SetName(name);
	textObject.transform.position.Set(positionX, positionY, 0);
	textObject.transform.SetScale(scaleX, scaleY);
	textObject.text.SetText(State::m_renderer, textContents, font);
	textObject.text.color = color;
	textObject.text.isHud = true;

	State::sCurrentState->AddObject(&textObject);
	return textObject;
}
void HappyEnding::Initialize()
{
	State::sCurrentState = this;
	camera.position.Set(0, 0, 0);
	mainFont = TTF_OpenFont("font/BMDOHYEON_ttf.ttf", 48);
	CreateHudText(titleText1, "Title", 0, 300.f, 1200.f, 130.f, mainFont, "You could save the world from fine dust by your bravery", Color::WHITE);
	CreateHudText(titleText2, "Title", 0, -300.f, 1200.f, 130.f, mainFont, "You have become a hero for Koreans", Color::WHITE);

	animation.transform.rotation = 0;

	background.SetName("Start");
	background.transform.SetScale(State::m_width, State::m_height);
	background.sprite.LoadImage("texture/Hero.png", State::m_renderer);
	background.sprite.SetFrame(2);
	background.sprite.SetSpeed(12.f);
        background.SetName("HeroSound");
        background.sound.LoadSound("sound/Ending_Hero.mp3");
        background.sound.SetVolume(100);
	background.sprite.activeAnimation = true;
	background.sound.Play();
	letters.SetName("Text");
	letters.transform.position.Set(0, -200, 0);
	letters.transform.SetScale(650, 128);

	AddObject(&titleText1);
	AddObject(&titleText2);
	AddObject(&background);	
	AddObject(&letters);		
	AddObject(&animation);
	
	InitializeObjects();
}

void HappyEnding::Update(float dt)
{

    
	TransformObjects();
	//SetAnimation();
	/******************* State ******************/
	UpdateObjects(dt);
	auto MousePos = State::m_input->GetMousePos();

	static float time = 0;
	time += dt;

	if (time > 4)
	{
		background.sprite.Free();
		titleText1.text.SetText(State::m_renderer, " ", mainFont);
		titleText2.text.SetText(State::m_renderer, " ", mainFont);
		background.sprite.LoadImage("texture/thumbs.png", State::m_renderer);
		background.sprite.activeAnimation = false;
		
		if (State::m_input->IsPressed((SDL_SCANCODE_SPACE)))
		{
			m_game->Quit();
		}
		

	}

	animation.transform.position.Set(MousePos.x - 650, -MousePos.y + 300, 0);
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();
	if (m_input->IsTriggered(SDL_SCANCODE_M))
		m_game->Change(LV_MainMenu);
	UpdatePhysics(dt);
	Render(dt);
}

void HappyEnding::Close()
{
	// Wrap up state
	ClearBaseState();
}

void HappyEnding::TransformObjects()
{
	static const float pixels_per_second = 64.0f;
	static bool scaleUp = true;
}

void HappyEnding::CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id)
{
	textObject->SetName(id);
	textObject->transform.SetScale(650, 130);
	textObject->text.SetText(State::m_renderer, textContents, mainFont);
	textObject->text.color = WHITE;
	textObject->text.isHud = true;
	AddObject(textObject);
}


