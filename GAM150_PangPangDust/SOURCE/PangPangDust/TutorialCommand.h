#pragma once
/******************************************************************************/
/*!
\file  TutorialCommand.h
\author Kim Ha Gyeong
\par    email: digiepn.hagyeong@gmail.com
\date   2019/06/11

tutorial Command builder
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "Command.h"

class TutorialCommand : public Command
{
public:
	TutorialCommand();
	~TutorialCommand();
	virtual void Execute() override;
public:
};
