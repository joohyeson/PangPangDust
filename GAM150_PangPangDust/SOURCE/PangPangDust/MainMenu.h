/******************************************************************************/
/*!
\file   MainMenu.h
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
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class MainMenu : public State
{
	friend class Game;

protected:

	MainMenu() : State() {};
	~MainMenu() override {};

	void Initialize() override;
	void Update(float dt) override;
	void Close() override;


private:
	const int period = 180;
	float ellapsedtime = 0.0f;
	Object titleText;
    Object instructionsText;
    Object exitButton;
	Object animation,background, letters;
	Object startButton;
	Object tutorialButton;
    Object CreditButton;

	void TransformObjects(float dt);
	void SetAnimation();
	void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id);
    void CreateButton();
};

