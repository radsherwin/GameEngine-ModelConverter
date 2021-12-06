#ifndef ANIM_DATA_H
#define ANIM_DATA_H

#include "animData.pb.h"
#include "boneData.h"

class animData
{
public:
	animData();
	animData(const animData&);
	animData& operator=(const animData&);
	~animData();

	animData(boneData* bone_data, signed int _parent, unsigned int _frameBucketCount);

	//Serialization
	void Serialize(animData_proto& out) const;
	void Deserialize(const animData_proto& in);

	void Print(const char* const pName, int count) const;

public:
	boneData*		bone_data;
	signed int		parent;
	unsigned int	frameBucketCount;
	
};

#endif
