/******************************************************************************/
/*!
\file  CreditCommand.cpp
\author Son Ju Hye
\par    email: juhye.son990902@gmail.com
\date   2019/06/10

Credit Command builder
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "engine/State.h"
#include "CommonLevel.h"
#include "CreditCommand.h"

CreditCommand::CreditCommand() :
    Command(eCommandTypes::CreditCommand)
{
}

CreditCommand::~CreditCommand()
{
}

void CreditCommand::Execute()
{

    State::sCurrentState->m_game->Change(LV_CreditPage);
}
