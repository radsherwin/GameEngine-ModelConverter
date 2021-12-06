#ifndef BONE_DATA_H
#define BONE_DATA_H

#include "boneData.pb.h"

class boneData
{
public:
	boneData();
	boneData(const boneData&);
	boneData& operator=(const boneData&);
	~boneData();

	boneData(	unsigned char* translation,
				unsigned char* rotation,
				unsigned char* scale);
	//Serialization
	void Serialize(boneData_proto& out) const;
	void Deserialize(const boneData_proto& in);

	void Print(const char* const pName, int count) const;

public:
	unsigned char* pTranslation;
	unsigned char* pRotation;
	unsigned char* pScale;

};

#endif
