//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef MESH_DATA_H
#define MESH_DATA_H

#include "meshData.pb.h"
#include "vboData.h"
#include "textureData.h"
#include "animData.h"

class meshData
{
public:
	static const unsigned int FILE_NAME_SIZE = 64;

	static constexpr const char *PROTO_VERSION = "1.0.9"; //Major.Version.Rev
	static const unsigned int VERSION_NUM_BYTES = 8;

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
	meshData();
	meshData(const meshData&) = delete;
	meshData&operator = (const meshData&) = delete;
	~meshData();
	
	// Serialization 
	void Serialize(meshData_proto &out) const;
	void Deserialize(const meshData_proto &in);

	void Print(const char *const pName) const;

public:
	char				pVersion[VERSION_NUM_BYTES];

	char**				pName;
	RENDER_MODE*		mode;
	unsigned int*		nodeNumber;
	unsigned int*		triCount;
	unsigned int*		vertCount;
	vboData*			vbo_vert;	//Engine Attribute: 0
	vboData*			vbo_norm;	//Engine Attribute: 1
	vboData*			vbo_uv;		//Engine Attribute: 2
	vboData*			vbo_index;	//Engine Attribute: 3
	vboData*			vbo_color;	//Engine Attribute: 4
	textureData*		text_color;
	animData*			anim_data;
	unsigned int*		materialIndex;
	unsigned int		meshCount;
	unsigned int		texCount;
	unsigned int		nameCount;
	unsigned int		animCount;

};

#endif

// --- End of File ---
