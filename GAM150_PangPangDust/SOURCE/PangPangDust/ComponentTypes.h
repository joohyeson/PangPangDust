/******************************************************************************/
/*!
\file   ComponentTypes.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/30

All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#pragma once

#include <string>

/**
 * \brief 
 * This is enum class for component types
 */
enum class eComponentTypes
{
	INVALID = 0,
	ShootBulletController,
	TutorialController,
	Level4Controller,
    DemoUIButton,
	//DemoReposition,
	//DemoWrapPosition,
	///*DemoPlatformerController,*/
	NUM_COMPONENTS,
};

/**
 * \brief 
 * Convert string to eComponentTypes's component
 * 
 * \param string
 * String to be  converted for component type
 * 
 * \return 
 * Converted component type
 */
inline eComponentTypes StringToComponent(const std::string& string)
{
	if (string == "ShootBulletController")				return eComponentTypes::ShootBulletController;
	if(string == "TutorialController")					return eComponentTypes::TutorialController;
	if (string == "Level4Controller")					return eComponentTypes::Level4Controller;
	//if (string == "DemoReposition")				    return eComponentTypes::DemoReposition;
	//if (string == "DemoWrapPosition")				return eComponentTypes::DemoWrapPosition;
    if (string == "DemoUIButton")			        return eComponentTypes::DemoUIButton;
	//if (string == "DemoPlatformerController")			        return eComponentTypes::DemoPlatformerController;
	return eComponentTypes::INVALID;
}

/**
 * \brief 
 * Convert eComponentTypes's component to string
 * 
 * \param type 
 * Component type to be converted for string
 * 
 * \return 
 * Converted string
 */
inline std::string ComponentToString(eComponentTypes type)
{
    if (type == eComponentTypes::DemoUIButton)		            return "DemoUIButton";
	if (type == eComponentTypes::ShootBulletController)				return " ShootBulletController";
	if(type ==eComponentTypes::TutorialController)					return "TutorialController";
	if (type == eComponentTypes::Level4Controller)					return "Level4Controller";
	//if (type == eComponentTypes::DemoReposition)				        return "DemoReposition";
	//if (type == eComponentTypes::DemoWrapPosition)				return "DemoWrapPosition";
	//if (type == eComponentTypes::DemoPlatformerController)				return "DemoPlatformerController";
	return "Invalid";
}