//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Keyboard.h"
#include "Mouse.h"

class InputManager
{
public:
	InputManager(const InputManager&) = delete;
	InputManager& operator = (const InputManager&) = delete;
	~InputManager();

	static void Create();
	static void Destroy();

	static Keyboard* GetKeyboard();
	static Mouse* GetMouse();

private:
	InputManager();

	static InputManager* privInstance();
	static void privCreate();

	// Data
	static InputManager* poInputMan;
	Keyboard* poKeyboard;
	Mouse* poMouse;

};


#endif

// --- End of File ---