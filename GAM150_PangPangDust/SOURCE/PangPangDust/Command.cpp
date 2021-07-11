/******************************************************************************/
/*!
\file   Command.cpp
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26

This registers commands's builders.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "CommandTypes.h"
#include "Command.h"

Command::Command(eCommandTypes type) :
    mType(type)
{
}
