/******************************************************************************/
/*!
\file   DigipenLogo.h
\author Son Ju Hye
\par    email: juhye.son990902@gamil.com
\par    GAM150 demo
\date   5/15

logo page
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class DigipenLogoPage : public State
{
    friend class Game;

protected:

    DigipenLogoPage() : State() {};
    ~DigipenLogoPage() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;


private:
    const int period = 180;
    float ellapsedtime = 0.0f;

    Object background;


};


