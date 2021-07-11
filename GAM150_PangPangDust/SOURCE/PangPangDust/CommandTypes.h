#pragma once
/******************************************************************************/
/*!
\file  CommnadTypes.h
\author Hun Yang
\modify Kim HaGyeong, Lee Ui Jin
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26

This registers commands's builders.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include <string>

enum class eCommandTypes
{
    INVALID = 0,
    QuitCommand,
	StartCommand,
	TutorialCommand,
    CreditCommand,
    Count
};


inline eCommandTypes StringToCommand(const std::string& string)
{
    if (string == "QuitCommand")				    return eCommandTypes::QuitCommand;
	if (string == "StartCommand")				    return eCommandTypes::StartCommand;
	if (string == "TutorialCommand")				    return eCommandTypes::TutorialCommand;
    if (string == "CreditCommand")				    return eCommandTypes::CreditCommand;
    return eCommandTypes::INVALID;
}

inline std::string CommandToString(eCommandTypes type)
{
    if (type == eCommandTypes::QuitCommand)				        return "QuitCommand";
	if (type == eCommandTypes::StartCommand)				        return "StartCommand";
	if (type == eCommandTypes::TutorialCommand)				        return "TutorialCommand";
    if (type == eCommandTypes::CreditCommand)				        return "CreditCommand";
    return "Invalid";
}
