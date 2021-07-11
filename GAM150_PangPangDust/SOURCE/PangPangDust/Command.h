/******************************************************************************/
/*!
\file   Command.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26

This registers commands's builders.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once
#include "CommandTypes.h"

class Command
{
public:
    Command(eCommandTypes type);
    virtual ~Command() {};
    virtual void Execute() = 0;
private:
    eCommandTypes mType;
};
