//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameManager.h"

namespace Azul
{
	GameManager* GameManager::pInstance = nullptr;

	void GameManager::Create(const char* windowName, const int Width, const int Height)
	{
		GameManager::privCreate(windowName, Width, Height);
	}

	void GameManager::Destroy()
	{
		GameManager* pMan = GameManager::privInstance();
		assert(pMan);

		assert(pMan->poGame);
		delete pMan->poGame;
		pMan->poGame = nullptr;
	}

	void GameManager::privCreate(const char* windowName, const int Width, const int Height)
	{
		Game* poGame = new Game(windowName, Width, Height);

		// Storage
		static GameManager GameManager(poGame);
		GameManager::pInstance = &GameManager;
	}

	GameManager::GameManager(Game* poGame)
	{
		assert(poGame);
		this->poGame = poGame;
	}

	GameManager::~GameManager()
	{
		assert(this->poGame == nullptr);
	}

	Game* GameManager::GetGame()
	{
		GameManager* pMan = GameManager::privInstance();
		assert(pMan);
		assert(pMan->poGame);
		return pMan->poGame;
	}

	GameManager* GameManager::privInstance()
	{
		assert(GameManager::pInstance);
		return GameManager::pInstance;
	}
}

// --- End of File ---
