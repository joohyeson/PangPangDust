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

#include "TutorialCommand.h"
#include "engine/State.h"
#include "CommonLevel.h"

TutorialCommand::TutorialCommand() :
	Command(eCommandTypes::TutorialCommand)
{

}

TutorialCommand::~TutorialCommand()
{

}

void TutorialCommand::Execute()
{
	State::m_game->Change(LV_Tutorial);
}
