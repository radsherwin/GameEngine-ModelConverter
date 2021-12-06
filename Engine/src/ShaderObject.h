//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

// for GLu stuff
#include "sb7.h"
#include "DLink.h"

class ShaderObject : public DLink
{
public: 
	enum class Name
	{
		NULL_SHADER,
		COLOR_POSITION,
		TEXTURE_SIMPLE,
		TEXTURE_POINT_LIGHT,
		CONST_COLOR,
		COLOR_SINGLE,
		SPEC_LIGHTING,
		UNINITIALIZED
	};
public:
	ShaderObject();
	ShaderObject(const ShaderObject&) = delete;
	ShaderObject& operator = (ShaderObject&) = delete;
	virtual ~ShaderObject();

	void Set(ShaderObject::Name name, const char* const pName);
	void SetActive() const;
	GLint GetLocation(const char* const pUniformName) const;

	virtual void Wash() override;
	virtual char* GetName() override;
	virtual bool Compare(DLink* pTargetNode) override;
	virtual void Dump() override;

private:
	void privClear();
	bool privCreateShader(GLuint& programObject, const char* const pShaderBaseFileName);
	bool privLoadNCompile(GLuint& shaderObject, const char* const pShaderFileName, GLenum shader_type);

public:
	// data
	Name  name;
	GLuint		programObject;
	GLuint fs;
	GLuint vs;

};


#endif

// --- End of File ---