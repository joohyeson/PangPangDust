/******************************************************************************/
/*!
\file  PauseState.h
\author Son Ju Hye
\par    email: juhye.son990902@gmail.com
\date   2019/06/11

transition for next stage

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class PauseState : public State
{
	friend class Game;

protected:

	PauseState() : State() {};
	~PauseState() override {};

	void Initialize() override;
	void Update(float dt) override;
	void Close() override;

private:

	Object	text, text2, image, clapSound;
};

