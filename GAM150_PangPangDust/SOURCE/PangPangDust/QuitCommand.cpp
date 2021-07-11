/******************************************************************************/
/*!
\file   QuitCommand.cpp
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26

Quit commands's builders.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "QuitCommand.h"
#include "engine/State.h"
#include "CommonLevel.h"

QuitCommand::QuitCommand():
    Command(eCommandTypes::QuitCommand)
{
}

QuitCommand::~QuitCommand()
{
}

void QuitCommand::Execute()
{
    State::sCurrentState->m_game->Quit();
}
