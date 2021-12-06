//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameManager.h"
#include "Mouse.h"

using namespace Azul;

Mouse::Mouse()
{

}

// Use this to read mouse buttons
bool Mouse::GetKeyState(Button button)
{
	bool value;
	Game* pGame = GameManager::GetGame();
	if (pGame->GetMouseButton(button) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}
	return value;
}

void Mouse::GetCursor(float& xPos, float& yPos)
{
	// get mouse position
	Game* pGame = GameManager::GetGame();
	pGame->GetCursorPos(xPos, yPos);

}

// --- End of File ---