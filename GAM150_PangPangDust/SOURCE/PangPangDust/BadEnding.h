#pragma once
/******************************************************************************/
/*!
\file   BadEnding.h
\author Kim Ha Gyeong
\secoun author Son Ju Hye
\par    email: digipen.hagyeong@gmail.com
\par    GAM150
\date   5/15
Bad ending page

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "engine\State.h"
#include "engine\Object.h"

class BadEnding : public State
{
	friend class Game;
	friend class HappyEnding;
protected:

	BadEnding() : State() {};
	~BadEnding() override {};

	void Initialize() override;
	void Update(float dt) override;
	void Close() override;
	class Object& CreateHudText(class Object& textObject, const char* name, float positionX, float positionY, float scaleX, float scaleY, _TTF_Font* font, const char* textContents, struct SDL_Color color);

private:
	const int period = 180;
	float ellapsedtime = 0.0f;
	Object titleText1;
	Object titleText2;

	Object instructionsText;
	Object exitButton;
	Object animation, background, letters;
	Object startButton;
	void TransformObjects(float dt);
	void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id);

};