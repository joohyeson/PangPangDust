#pragma once
/******************************************************************************/
/*!
\file   QuitCommand.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26

Quit commands's builders.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "Command.h"

class QuitCommand : public Command
{
public:
    QuitCommand();
    ~QuitCommand();
    virtual void Execute() override;
public:
};
