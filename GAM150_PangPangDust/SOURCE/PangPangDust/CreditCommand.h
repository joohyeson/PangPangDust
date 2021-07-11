#pragma once

/******************************************************************************/
/*!
\file  CreditCommand.h
\author Son Ju Hye
\par    email: juhye.son990902@gmail.com
\date   2019/06/10

Credit Command builder
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/

#include "Command.h"

class CreditCommand : public Command
{
public:
    CreditCommand();
    ~CreditCommand();
    virtual void Execute() override;
};
