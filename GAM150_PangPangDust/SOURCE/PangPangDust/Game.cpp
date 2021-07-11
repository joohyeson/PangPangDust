/******************************************************************************/
/*!
\file   Game.cpp
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Game will only handle the changes of the game states (Level switching)
ie. Main Menu, Levels, Pause, etc.
No game play logic should be added here.
All content © 2019 DigiPen (USA) Corporation, all rights reserved
*/
/******************************************************************************/
#include "Game.h"
#include "engine/StateManager.h"
#include "RegisterComponents.h"
#include "RegisterCommands.h"

Game::Game()
{
	m_stateManager = new StateManager;

}

Game::~Game()
{
	if (m_stateManager) {
		delete m_stateManager;
		m_stateManager = nullptr;
	}
}

/**
 * \brief 
 * Initialize game states and window size
 * 
 * \return
 * True 
 */
bool Game::Initialize()
{
	// Set window size
	State::m_width = SCREEN_WIDTH, State::m_height = SCREEN_HEIGHT;

	// Set state ids
	mainMenu.SetId(LV_MainMenu);
	tutorial.SetId(LV_Tutorial);
	level1.SetId(LV_Level1);
	pauseLevel.SetId(LV_Pause);
    level2.SetId(LV_Level2);
	level3.SetId(LV_Level3);
	level4.SetId(LV_Level4);
    happyEnding.SetId(LV_HappyEnding);
    badEnding.SetId(LV_BadEnding);
    LogoPage.SetId(LV_LogoPage);
    creditPage.SetId(LV_CreditPage);
    gameOverScreen.SetId(LV_GameOver);
    // Register components
    RegisterComponents();
    // Register commands
    RegisterCommands();

	// Register states
    RegisterPauseState(&creditPage);
	RegisterState(&mainMenu);
	RegisterState(&tutorial);
	RegisterState(&level1);
	RegisterState(&level2);
	RegisterState(&level3);
	RegisterState(&level4);
    RegisterState(&happyEnding);
    RegisterState(&badEnding);
    RegisterState(&creditPage);
	RegisterState(&pauseLevel);
    RegisterState(&gameOverScreen);
	// Register pause state
	RegisterPauseState(&pauseLevel);
    RegisterPauseState(&LogoPage);
   
	// Set starting state
	SetFirstState(&LogoPage);

	// Initlialize current state
	GetCurrentState()->Initialize();

	return true;
}

/**
 * \brief 
 * Update state manager
 * 
 * \param dt
 * Delta time 
 */
void Game::Update(float dt)
{
	StateManager::SetWindowSize(m_width, m_height);
	m_stateManager->Update(dt);
}

/**
* \brief
* Wrap all state stacks up
*/
void Game::Close()
{
    // Unregister components
    UnregisterComponents();
    // Unregister commands
    UnregisterCommands();

	m_stateManager->Close();
}

/**
* \brief
* Set a state as a pause state
*
* \param state
* Address of state to set as the pause state
*/
void Game::RegisterPauseState(State* state)
{
	m_stateManager->RegisterPauseState(state);
}

/**
* \brief
* Stop updating current state and move to pause state
*/
void Game::Pause()
{
	m_stateManager->Change(LV_Pause);
}

/**
* \brief
* Close pause state and move back to last state
*/
void Game::Resume()
{
	m_stateManager->Resume();
}

/**
* \brief
* Restart current state
*/
void Game::Restart()
{
	m_stateManager->Restart();
}

void Game::CreditState()
{
    m_stateManager->Change(LV_CreditPage);
}

/**
* \brief
* Add a state
*
* \param state
* Address of state to add
*/
void Game::RegisterState(State* state)
{
	m_stateManager->RegisterState(state);
}

/**
* \brief
* Set a state to starting point
*
* \param state
* Address of state to set as the first state
*/
void Game::SetFirstState(State* state)
{
	m_stateManager->SetFirstState(state);
}

/**
* \brief
* Return the address of the current state
*
* \return m_stack.top()
*/
State* Game::GetCurrentState()
{
	return m_stateManager->GetCurrentState();
}

/**
* \brief
* Set game state manager to shutdown
*/
void Game::Quit()
{
	m_stateManager->Quit();
}

/**
* \brief
* Change current state to other state
*
* \param stateId
* Id of state to change
*/
void Game::Change(unsigned stateId)
{
	m_stateManager->Change(stateId);
}


/**
 * \brief 
 * Check either if the app gets ready to quit
 * 
 * \return m_stateManager->IsQuit()
 */ 
bool Game::IsQuit()
{
	return m_stateManager->IsQuit();
}
