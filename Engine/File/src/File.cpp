//--------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "File.h"

namespace Azul
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{
		BY_HANDLE_FILE_INFORMATION hr;
		if (GetFileInformationByHandle(fh, &hr)) return true;
		else return false;

	}

	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
		DWORD dMode;
		switch (mode)
		{
		case File::Mode::WRITE:
			dMode = GENERIC_WRITE;
			break;
		case File::Mode::READ:
			dMode = GENERIC_READ;
			break;
		case File::Mode::READ_WRITE:
			dMode = (GENERIC_READ | GENERIC_WRITE);
			break;
		default:
			dMode = GENERIC_READ;
		}

		if (FAILED(fh = CreateFile(fileName, dMode, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, fh)))
		{
			return File::Error::OPEN_FAIL;
		}
		else return File::Error::SUCCESS;
	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		if (!IsHandleValid(fh)) return File::Error::CLOSE_FAIL;
		if (CloseHandle(fh))
		{
			return File::Error::SUCCESS;
		}
		else return File::Error::CLOSE_FAIL;
		
	}

	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{
		if (WriteFile(fh, buffer, inSize, NULL, NULL)) return File::Error::SUCCESS;
		else return File::Error::WRITE_FAIL;
	}

	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{
		
		if (ReadFile(fh, buffer, inSize, NULL, NULL)) return File::Error::SUCCESS;
		else return File::Error::READ_FAIL;
	}

	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		//if (offset < 0) return File::Error::SEEK_FAIL;

		DWORD dwMoveLocation;
		switch (location)
		{
		case File::Position::BEGIN:
			dwMoveLocation = FILE_BEGIN;
			break;
		case File::Position::CURRENT:
			dwMoveLocation = FILE_CURRENT;
			break;
		case File::Position::END:
			dwMoveLocation = FILE_END;
			break;
		default:
			dwMoveLocation = FILE_CURRENT;
		}


		if (SetFilePointer(fh, offset, NULL, dwMoveLocation) != INVALID_SET_FILE_POINTER) return File::Error::SUCCESS;
		else return File::Error::SEEK_FAIL;
	}

	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
		DWORD currDWORD;
		File::Handle tmp = fh;
		if ((currDWORD = SetFilePointer(tmp, 0, NULL, FILE_CURRENT)) == INVALID_SET_FILE_POINTER) return File::Error::TELL_FAIL;

		//DWORD fileOffset = lowDWORD << 32 | (DWORD)highDWORD;

		offset = currDWORD;

		return 	File::Error::SUCCESS;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		if (!IsHandleValid(fh)) return File::Error::FLUSH_FAIL;
		if (FlushFileBuffers(fh)) return File::Error::SUCCESS;
		else return File::Error::FLUSH_FAIL;

	}

}

// ---  End of File ---------------
