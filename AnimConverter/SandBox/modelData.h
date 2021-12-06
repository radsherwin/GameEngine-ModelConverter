//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "modelData.pb.h"
#include "vboData.h"
#include "textureData.h"

class modelData
{
public:
	static const unsigned int FILE_NAME_SIZE = 64;

	enum class RENDER_MODE
	{
		MODE_POINTS = 0,
		MODE_LINE,
		MODE_LINE_LOOP,
		MODE_LINE_STRIP,
		MODE_TRIANGLES,
		MODE_TRIANGLE_STRIP,
		MODE_TRIANGLE_FAN,
		DEFAULT = MODE_TRIANGLES
	};

public:
	modelData();
	modelData(const modelData &) = delete;
	modelData &operator = (const modelData &) = delete;
	~modelData();

	//Static
	static RENDER_MODE GetMode(int GLTF_TINY_VAL);

	
	// Serialization 
	void Serialize(modelData_proto &out) const;
	void Deserialize(const modelData_proto &in);

	void Print(const char *const pName) const;

public:

	char         pModelName[FILE_NAME_SIZE];
	RENDER_MODE	 mode;
	unsigned int triCount;

	vboData      vbo_vert;
	vboData      vbo_norm;
	vboData      vbo_uv;
	vboData      vbo_trilist;
	textureData  text_color;
	textureData  text_normal;
	textureData  text_rough;
};

#endif

// --- End of File ---
