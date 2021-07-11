#pragma once
/******************************************************************************/
/*!
\par    GAM150 demo
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
namespace MathUtils
{
    float   RadianToDegree    (float radian);
    float   DegreeToRadian    (float degree);
    float   Lerp              (float start, float end, float value);
    float   Wrap              (float value, float min, float max);

    int     GetRandomInt      (int min, int max);
    float   GetRandomFloat    (float min, float max);
}