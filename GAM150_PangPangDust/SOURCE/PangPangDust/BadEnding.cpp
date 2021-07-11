/******************************************************************************/
/*!
\file   BadEnding.cpp
\author Kim Ha Gyeong
\secoun author Son Ju Hye
\par    email: digipen.hagyeong@gmail.com
\par    GAM150 
\date   5/15
Bad ending page

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include "Color.h"

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

class Object& BadEnding::CreateHudText(class Object& textObject, const char* name, float positionX, float positionY, float scaleX, float scaleY, _TTF_Font* font, const char* textContents, struct SDL_Color color)
{

	// Set the object's name
	textObject.SetName(name);
	// Set the position of the object
	textObject.transform.position.Set(positionX, positionY, 0);
	// Set the scale of the object
	textObject.transform.SetScale(scaleX, scaleY);

	// Set the text to render out
	textObject.text.SetText(State::m_renderer, textContents, font);
	// Set the colors r,g,b,a (0~255)
	textObject.text.color = color;
	// Set either if the object to be hud or not
	textObject.text.isHud = true;

	// Register the object to the state
	State::sCurrentState->AddObject(&textObject);
	return textObject;
}

void BadEnding::Initialize()
{
	State::sCurrentState = this;
	camera.position.Set(0, 0, 0);
	mainFont = TTF_OpenFont("font/Default.ttf", 48);
	mainFont = TTF_OpenFont("font/BMDOHYEON_ttf.ttf", 48);
	CreateHudText(titleText1, "Title", 0, 300.f, 1200.f, 130.f, mainFont, "You failed to save the world", Color::WHITE);
	CreateHudText(titleText2, "Title", 0, -300.f, 1200.f, 130.f, mainFont, "Look outside... people are suffering from fine dust", Color::WHITE);

	background.SetName("Start");
	background.transform.SetScale(State::m_width, State::m_height);
	background.sprite.LoadImage("texture/BadEndingBack.png", State::m_renderer);

	letters.SetName("Text");
	letters.transform.position.Set(0, -200, 0);
	letters.transform.SetScale(650, 128);

	// This is the actual rendering order
	AddObject(&background);	
	AddObject(&letters);		
	AddObject(&animation);


	InitializeObjects();
}

void BadEnding::Update(float dt)
{
	TransformObjects(dt);
	/******************* State ******************/
	UpdateObjects(dt);
	auto MousePos = State::m_input->GetMousePos();
	animation.transform.position.Set(MousePos.x - 650, -MousePos.y + 300, 0);
	// Pause current state and move to pause state
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();

	static float time1 = 0;
	time1 += dt;
	//// Pause current state and move to pause state
	if (time1 > 4) // to show next picture
	{
		background.sprite.Free();
		background.sprite.LoadImage("texture/sadending.png", State::m_renderer);
		titleText1.text.Free();
		titleText2.text.Free();
		titleText1.text.SetText(State::m_renderer, " ", mainFont);
		titleText2.text.SetText(State::m_renderer, "Why don't you give it another try?", mainFont);
		titleText2.text.color = Color::BLACK;
		if (State::m_input->IsPressed((SDL_SCANCODE_SPACE)))
		{
			m_game->Quit();
		}
	}
	UpdatePhysics(dt);
	Render(dt);
}

void BadEnding::Close()
{
	ClearBaseState();
}

void BadEnding::TransformObjects(float dt)
{
	static const float pixels_per_second = 64.0f;
	static bool scaleUp = true;
	float newDt = dt * pixels_per_second;
	animation.transform.position.x += newDt;
}

void BadEnding::CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id)
{
	// Set the object's name
	textObject->SetName(id);

	// Set the scale of the object
	textObject->transform.SetScale(650, 130);

	// Set the text to render out
	textObject->text.SetText(State::m_renderer, textContents, mainFont);

	// Set the colors r,g,b,a (0~255)
	textObject->text.color = WHITE;

	// Set either if the object to be hud or not
	textObject->text.isHud = true;

	// Register the object to the state
	AddObject(textObject);
}

