/******************************************************************************/
/*!
\file   Credit.h
\author Son Ju Hye
\second author Kim Ha Gyeong
\par    email: juhye.son990902@gamil.com
\par    GAM150 demo
\date   5/15

Credint page
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class CreditPage : public State
{
    friend class Game;

protected:

    CreditPage() : State() {};
    ~CreditPage() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;


private:
    const int period = 180;
    float ellapsedtime = 0.0f;
    Object titleText;
    Object instructionsText;
    Object exitButton;
    Object animation, background, letters;
    Object startButton;
    Object tutorialButton;

    void TransformObjects(float dt);
};


