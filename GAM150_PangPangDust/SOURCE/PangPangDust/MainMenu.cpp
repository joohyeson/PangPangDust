/******************************************************************************/
/*!
\file   MainMenu.cpp
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\modify Son Ju Hye
\par    GAM150 demo
\par	v0
\date   2018/03/11

Conaining examples how to use engine
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommonLevel.h"
#include "DemoUIButton.h"

extern  int tutorialCount;

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

void MainMenu::Initialize()
{
	tutorialCount = 0;
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
	background.sprite.LoadImage("texture/START_SCREEN.png", State::m_renderer);

	letters.SetName("Text");
	letters.transform.position.Set(0, -200, 0);
	letters.transform.SetScale(650, 128);

	AddObject(&background);
	AddObject(&letters);	
	AddObject(&animation);
    CreateButton();
	
    InitializeObjects();
}

void MainMenu::Update(float dt)
{
	TransformObjects(dt);
	SetAnimation();
	/******************* State ******************/
    UpdateObjects(dt);
	auto MousePos = State::m_input->GetMousePos();
	animation.transform.position.Set(MousePos.x-650, -MousePos.y+300, 0);
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();

	UpdatePhysics(dt);
	Render(dt);
}

void MainMenu::Close()
{
	ClearBaseState();
}

void MainMenu::TransformObjects(float dt)
{
	static const float pixels_per_second = 64.0f;
	static bool scaleUp = true;
	float newDt = dt * pixels_per_second;
	animation.transform.position.x += newDt;
}

void MainMenu::SetAnimation()
{
	if (m_input->IsTriggered(SDL_SCANCODE_SPACE)) {
		static bool toggle = true;
		animation.sprite.stopAnimation = toggle;
		toggle = !toggle;
	}

	else if (m_input->IsTriggered(SDL_SCANCODE_BACKSPACE)) {
		static bool toggle = true;
		animation.sprite.rewindAnimation = toggle;
		toggle = !toggle;
	}

	if (m_input->IsTriggered(SDL_SCANCODE_1))
		animation.sprite.SetCurrentFrame(true, 3);

	else if (m_input->IsTriggered(SDL_SCANCODE_2))
		animation.sprite.SetCurrentFrame(true, 5);

	else if (m_input->IsTriggered(SDL_SCANCODE_3))
		animation.sprite.SetCurrentFrame(true, 7);

	else if (m_input->IsTriggered(SDL_SCANCODE_4))
		animation.sprite.SetCurrentFrame(false, 2);

	else if (m_input->IsTriggered(SDL_SCANCODE_5))
		animation.sprite.SetCurrentFrame(false, 4);

	else if (m_input->IsTriggered(SDL_SCANCODE_6))
		animation.sprite.SetCurrentFrame(false, 7);

	else if (m_input->IsTriggered(SDL_SCANCODE_RETURN))
		animation.sprite.SetCurrentFrame(false, 0);
}void MainMenu::CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id)
{
	textObject->SetName(id);

	textObject->transform.SetScale(650, 130);

	textObject->text.SetText(State::m_renderer, textContents, mainFont);

	textObject->text.color = WHITE;

	textObject->text.isHud = true;

	AddObject(textObject);
}

void MainMenu::CreateButton()
{

    exitButton.SetName("ExitButton");
	startButton.SetName("StartButton");
	tutorialButton.SetName("TutorialButton");
    CreditButton.SetName("CreditButton");


    startButton.transform.position.Set(200, -100, 0.f);
    exitButton.transform.position.Set(200, -250, 0.f);
	
	tutorialButton.transform.position.Set(-250, -100, 0.f);
    CreditButton.transform.position.Set(-250 ,-250, 0.f);

  
    exitButton.transform.SetScale(150.f, 150.f);
	startButton.transform.SetScale(150.f, 150.f);
	tutorialButton.transform.SetScale(150.f, 150.f);
    CreditButton.transform.SetScale(150.f, 150.f);

    exitButton.sprite.LoadImage("texture/ExitGame.png", State::m_renderer);
	startButton.sprite.LoadImage("texture/StartGame.png", State::m_renderer);
	tutorialButton.sprite.LoadImage("texture/StartGame.png", State::m_renderer);
    CreditButton.sprite.LoadImage("texture/Credit.png", State::m_renderer);

    exitButton.sprite.isHud = true;
	startButton.sprite.isHud = true;
	tutorialButton.sprite.isHud = true;
    CreditButton.sprite.isHud = true;

    DemoUIButton* Exitbutton = dynamic_cast<DemoUIButton*>(AddComponentToObject(&exitButton, eComponentTypes::DemoUIButton));
	DemoUIButton* Startbutton = dynamic_cast<DemoUIButton*>(AddComponentToObject(&startButton, eComponentTypes::DemoUIButton));
	DemoUIButton* Tutorialbutton = dynamic_cast<DemoUIButton*>(AddComponentToObject(&tutorialButton, eComponentTypes::DemoUIButton));
    DemoUIButton* Creditbutton = dynamic_cast<DemoUIButton*>(AddComponentToObject(&CreditButton, eComponentTypes::DemoUIButton));

	Exitbutton->mDefaultSpriteFile = "texture/ExitGame.png";
	Exitbutton->mHoveredSpriteFile = "texture/ExitGameHover.png";

	Startbutton->mDefaultSpriteFile = "texture/StartGame.png";
	Startbutton->mHoveredSpriteFile = "texture/StartGameHover.png";

	Tutorialbutton->mDefaultSpriteFile = "texture/Tutorial.png";
	Tutorialbutton->mHoveredSpriteFile = "texture/TutorialHover.png";

    Creditbutton->mDefaultSpriteFile = "texture/Credit.png";
    Creditbutton->mHoveredSpriteFile = "texture/CreditHover.png";

	Exitbutton->mButtonEvent = CreateCommand(eCommandTypes::QuitCommand);
	Startbutton->mButtonEvent = CreateCommand(eCommandTypes::StartCommand);
	Tutorialbutton->mButtonEvent = CreateCommand(eCommandTypes::TutorialCommand);
    Creditbutton->mButtonEvent = CreateCommand(eCommandTypes::CreditCommand);

	
    AddObject(&exitButton);
	AddObject(&startButton);
	AddObject(&tutorialButton);
    AddObject(&CreditButton);
}
