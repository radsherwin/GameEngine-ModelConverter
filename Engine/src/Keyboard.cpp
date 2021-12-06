//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameManager.h"
#include "Keyboard.h"

using namespace Azul;

// Use this to read keyboard
bool Keyboard::GetKeyState(Keyboard::Key key)
{
	bool value;

	Game* pGame = GameManager::GetGame();
	if (pGame->GetKey(key) == GLFW_PRESS)
	{
		
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}

bool Keyboard::GetKeyReleaseState(Keyboard::Key key)
{
	bool value;

	Game* pGame = GameManager::GetGame();
	if (pGame->GetKey(key) == GLFW_RELEASE)
	{

		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}

// --- End of File ---