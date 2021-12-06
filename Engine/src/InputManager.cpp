//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "InputManager.h"

InputManager* InputManager::poInputMan = nullptr;

void InputManager::Create()
{
	InputManager::privCreate();
}

void InputManager::Destroy()
{
	InputManager* pMan = InputManager::privInstance();
	assert(pMan);

	delete pMan->poInputMan;

}

InputManager::InputManager()
{
	this->poKeyboard = new Keyboard();
	assert(this->poKeyboard);

	this->poMouse = new Mouse();
	assert(this->poMouse);
}

void InputManager::privCreate()
{
	InputManager::poInputMan = new InputManager();
	assert(poInputMan);
}

InputManager::~InputManager()
{
	delete this->poKeyboard;
	delete this->poMouse;
}

Keyboard* InputManager::GetKeyboard()
{
	InputManager* pMan = InputManager::privInstance();
	return pMan->poKeyboard;
}

Mouse* InputManager::GetMouse()
{
	InputManager* pMan = InputManager::privInstance();
	return pMan->poMouse;
}

InputManager* InputManager::privInstance()
{
	assert(poInputMan);
	return poInputMan;
}

// --- End of File ---