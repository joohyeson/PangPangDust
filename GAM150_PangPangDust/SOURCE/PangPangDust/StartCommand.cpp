/******************************************************************************/
/*!
\file  StartCommand.cpp
\author Lee Ui Jin, Choi Jae Woo
\par    email: digipen.uijin@gmail.com, wod6983@gmail.com
\date   2019/06/11

start Command builder
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "StartCommand.h"
#include "engine/State.h"
#include "CommonLevel.h"

StartCommand::StartCommand() :
	Command(eCommandTypes::StartCommand)
{
}

StartCommand::~StartCommand()
{
	
}

void StartCommand::Execute()
{
	
	State::sCurrentState->m_game-> Change(LV_Level1);
}
