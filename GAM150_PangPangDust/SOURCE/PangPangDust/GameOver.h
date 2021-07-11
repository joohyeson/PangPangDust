#pragma once
/******************************************************************************/
/*!
\file   GameOver.h
\author Choi Jae Woo
\par    email: wod6983@gamil.com
\date   5/15

gameoverpage
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "engine\State.h"
#include "engine\Object.h"

class GameOver : public State
{
    friend class Game;
    friend class HappyEnding;
protected:

    GameOver() : State() {};
    ~GameOver() override {};

    void Initialize() override;
    void Update(float dt) override;
    void Close() override;
    class Object& CreateHudText(class Object& textObject, const char* name, float positionX, float positionY, float scaleX, float scaleY, _TTF_Font* font, const char* textContents, struct SDL_Color color);

private:
    const int period = 180;
    float ellapsedtime = 0.0f;
    Object titleText1;
    Object titleText2;
    Object instructionsText;
    Object exitButton;
    Object animation, background, letters;
    Object startButton;
    void TransformObjects(float dt);
    void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id);

};
