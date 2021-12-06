//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObject.h"
#include "MathEngine.h"
#include "File.h"
#include "ShaderObject.h"
#include "Game.h"
#include "StringThis.h"

using namespace Azul;

ShaderObject::ShaderObject()
	: name(ShaderObject::Name::UNINITIALIZED),
	programObject(0),
	fs(0),
	vs(0)
{

}

void ShaderObject::privClear()
{
	if (this->programObject)
	{
		glUseProgram(0);
		glDeleteProgram(this->programObject);
		glDeleteShader(this->fs);
		glDeleteShader(this->vs);

		this->name = Name::UNINITIALIZED;
		this->programObject = 0;
		this->fs = 0;
		this->vs = 0;
	}
}

ShaderObject::~ShaderObject()
{
	this->privClear();
}

void ShaderObject::Set(ShaderObject::Name _name, const char* const pName)
{
	this->name = _name;
	assert(pName);
	this->privCreateShader(this->programObject, pName);
}

GLint ShaderObject::GetLocation(const char* const pUniformName) const
{
	assert(pUniformName);
	GLint loc = glGetUniformLocation(this->programObject, pUniformName);
	assert(loc != -1);

	return loc;
}

void ShaderObject::SetActive() const
{
	// Setup for shader
	glUseProgram(this->programObject);
}

bool ShaderObject::privLoadNCompile(GLuint& shaderObject, const char* const pShaderFileName, GLenum shader_type)
{
	File::Handle fh;
	File::Error  ferror;

	assert(pShaderFileName);
	ferror = File::Open(fh, pShaderFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::END, 0);
	assert(ferror == File::Error::SUCCESS);

	DWORD numBytesInFile;
	ferror = File::Tell(fh, numBytesInFile);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	char* data = new char[numBytesInFile + 1];
	assert(data);

	ferror = File::Read(fh, data, numBytesInFile);
	assert(ferror == File::Error::SUCCESS);

	// null termination character
	data[numBytesInFile] = 0;

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	// create a shader object
	shaderObject = glCreateShader(shader_type);
	assert(shaderObject);

	//load shader
	glShaderSource(shaderObject, 1, &data, 0);
	delete[] data;

	glCompileShader(shaderObject);

	// check for errors
	GLint status = 0;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);

	// found one
	if (!status)
	{
		char buffer[4096];
		glGetShaderInfoLog(shaderObject, 4096, NULL, buffer);

		Trace::out("Error(ShaderLoadNCompile.cpp) %s: %s\n", pShaderFileName, buffer);

		glDeleteShader(shaderObject);

		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}

bool ShaderObject::privCreateShader(GLuint& inProgramObject, const char* const pShaderBaseFileName)
{
	bool status;
	char nameBuff[300];

	assert(pShaderBaseFileName);

	strcpy_s(nameBuff, 300, pShaderBaseFileName);
	strcat_s(nameBuff, 300, ".fs.glsl");

	status = privLoadNCompile(this->fs, nameBuff, GL_FRAGMENT_SHADER);
	assert(status == true);

	strcpy_s(nameBuff, 300, pShaderBaseFileName);
	strcat_s(nameBuff, 300, ".vs.glsl");

	status = privLoadNCompile(this->vs, nameBuff, GL_VERTEX_SHADER);
	assert(status == true);

	// Creates an empty program object
	inProgramObject = glCreateProgram();

	//Attaches a shader object to a program object
	glAttachShader(inProgramObject, this->vs);
	glAttachShader(inProgramObject, this->fs);

	// Links a program object
	glLinkProgram(inProgramObject);

	return true;
}

void ShaderObject::Wash()
{
	this->privClear();
}

char* ShaderObject::GetName()
{
	// todo - Hack understand why is this needed for print and fix...
	static char pTmp[300];
	strcpy_s(pTmp, 300, StringMe(this->name));
	return pTmp;
}

bool ShaderObject::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget);

	ShaderObject* pDataB = (ShaderObject*)pTarget;

	bool status = false;

	if (this->name == pDataB->name)
	{
		status = true;
	}

	return status;
}

void ShaderObject::Dump()
{
	Trace::out("      ShaderObject(%p)\n", this);

	// Data:
	Trace::out("      Name: %s \n", StringMe(this->name));


	DLink::Dump();
}

// --- End of File ---