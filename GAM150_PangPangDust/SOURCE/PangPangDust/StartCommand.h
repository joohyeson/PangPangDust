#pragma once

/******************************************************************************/
/*!
\file  StartCommand.h
\author Lee Ui Jin, Choi Jae Woo
\par    email: digipen.uijin@gmail.com, wod6983@gmail.com
\date   2019/06/11

start Command builder
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "Command.h"

class StartCommand : public Command
{
public:
	StartCommand();
	~StartCommand();
	virtual void Execute() override;
};
