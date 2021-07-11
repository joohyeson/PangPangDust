#pragma once
/******************************************************************************/
/*!
\file  HappyEnding.h
\author Lee Ui Jin, Choi Jae Woo
\par    email: digipen.uijin@gmail.com, wod6983@gmail.com
\date   2019/06/11

HappyEnding page

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "engine\State.h"
#include "engine\Object.h"

class HappyEnding : public State
{
	friend class Game;
	friend class BadEnding;
protected:

	HappyEnding() : State() {};
	~HappyEnding() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;
	Object& CreateHudText(Object& textObject, const char* name, float positionX, float positionY,
		float scaleX, float scaleY, TTF_Font* font, const char* textContents, SDL_Color color);

private:
	const int period = 180;
	float ellapsedtime = 0.0f;
	Object titleText1;
	Object titleText2;

	Object instructionsText;
	Object exitButton;
	Object animation, background, letters;
	Object startButton;
	void TransformObjects();
	void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id);

};