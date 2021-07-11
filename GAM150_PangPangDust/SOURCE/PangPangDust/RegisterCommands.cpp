/******************************************************************************/
/*!
\file  RegisterCommand.cpp
\author Hun Yang
\modify Kim HaGyeong, Lee Ui Jin
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26

This registers commands's builders.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "RegisterCommands.h"
#include "engine/State.h"
#include "engine/CommandBuilder.h"
#include "QuitCommand.h"
#include "StartCommand.h"
#include "TutorialCommand.h"
#include "CreditCommand.h"

void RegisterCommands()
{
    State::AddCommandBuilder(eCommandTypes::QuitCommand,
                                new CommandTBuilder<QuitCommand>);
	State::AddCommandBuilder(eCommandTypes::StartCommand,
		new CommandTBuilder<StartCommand>);
	State::AddCommandBuilder(eCommandTypes::TutorialCommand,
		new CommandTBuilder<TutorialCommand>); // for tutorial
    State::AddCommandBuilder(eCommandTypes::CreditCommand,
        new CommandTBuilder<CreditCommand>); // for credit

}

void UnregisterCommands()
{
    State::RemoveCommandBuilder(eCommandTypes::QuitCommand);
	State::RemoveCommandBuilder(eCommandTypes::StartCommand);
	State::RemoveCommandBuilder(eCommandTypes::TutorialCommand);
    State::RemoveCommandBuilder(eCommandTypes::CreditCommand);
}
