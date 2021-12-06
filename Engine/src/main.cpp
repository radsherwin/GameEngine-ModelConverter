//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


#include "GameManager.h"
#include "google\protobuf\message_lite.h"

using namespace Azul;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Game is inside a singleton
	GameManager::Create("Animation", 1600, 1200);

	Game* pGame = GameManager::GetGame();
	pGame->Run();

	GameManager::Destroy();

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// ---  End of File ---
