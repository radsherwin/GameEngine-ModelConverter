//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

// -----------------------------------------------------------------------------
// DO NOT MODIFY
// -----------------------------------------------------------------------------
// Warning levels turned on for Wall... that Should be supressed globally
//     Set here to avoid surpressing them in the settings
// -----------------------------------------------------------------------------

// I hate you XAudio2.h make your abstract class destructors virtual
#if _MSC_FULL_VER > 192500000
	#pragma warning( disable : 5205 ) // delete of an abstract class
#endif

// --------------------------------------
// General includes
// --------------------------------------

#pragma warning( disable : 5204 ) 
#pragma warning( disable : 5220 ) 

// --------------------------------------
// Compiler check
// --------------------------------------

#define IDEWinSDKCheck { char  winSDK_ver[13]; \
						 sprintf_s(winSDK_ver, 13, "%s", WINDOWS_TARGET_PLATFORM); \
						 assert(strcmp(winSDK_ver, "10.0.19041.0") >= 0); }

#define IDEToolsCheck { char tools_ver[12]; \
						sprintf_s(tools_ver, 12, "%s", TOOLS_VERSION); \
						assert(strcmp(tools_ver, "14.28.29910") >= 0); }

#define IDECompilerCheck { char compiler_ver[10]; \
							sprintf_s(compiler_ver, 10, "%d", _MSC_FULL_VER); \
							assert(strcmp(compiler_ver, "192829913") >= 0); }


#endif 

// ---  End of File ---------------
