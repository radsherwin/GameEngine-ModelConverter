//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Game.h"

namespace Azul
{
	class GameManager
	{
	public:
		GameManager() = delete;
		GameManager(const GameManager&) = delete;
		GameManager& operator = (const GameManager&) = delete;

		static void Create(const char* windowName, const int Width, const int Height);
		static void Destroy();

		static Game* GetGame();

	private:
		GameManager(Game* pGame);
		~GameManager();

		static GameManager* pInstance;
		static void privCreate(const char* windowName, const int Width, const int Height);

		static GameManager* privInstance();
		// Data
		Game* poGame;

	};

}


#endif

// --- End of File ---
