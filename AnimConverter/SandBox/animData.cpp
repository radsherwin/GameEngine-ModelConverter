#include "animData.h"

animData::animData()
	: bone_data(nullptr), parent(-1), frameBucketCount(0)
{
	
}

animData::animData(const animData& r)
{
	this->bone_data = r.bone_data;
	this->parent = r.parent;
	this->frameBucketCount = r.frameBucketCount;
}

animData& animData::operator=(const animData& r)
{
	if(this != &r)
	{
		this->bone_data = r.bone_data;
		this->parent = r.parent;
		this->frameBucketCount = r.frameBucketCount;
	}

	return *this;
}

animData::~animData()
{
	delete[] this->bone_data;
}

animData::animData(	boneData* _bonedata, signed int _parent, unsigned int _frameBucketCount)
{
	this->bone_data = _bonedata;
	this->parent = _parent;
	this->frameBucketCount = _frameBucketCount;
}

void animData::Serialize(animData_proto& out) const
{
	out.set_parent(this->parent);
	out.set_framebucketcount(this->frameBucketCount);

	for(int i =0; i < this->frameBucketCount; i++)
	{
		boneData_proto* pBone = new boneData_proto();
		this->bone_data[i].Serialize(*pBone);
		out.mutable_bone_data()->AddAllocated(pBone);
	}
	
	
}

void animData::Deserialize(const animData_proto& in)
{
	this->frameBucketCount = in.framebucketcount();
	this->parent = in.parent();
	if(this->frameBucketCount == 0)
	{
		this->bone_data = nullptr;
	}
	else
	{
		this->bone_data = new boneData[this->frameBucketCount];
		for(int i = 0; i < this->frameBucketCount; i++)
		{
			this->bone_data[i].Deserialize(in.bone_data(i));
		}
	}
	

	
}

void animData::Print(const char* const pName, int count) const
{
	Trace::out("pName: %s %d\n", pName, count);
	Trace::out("FrameBucket Count: %d\n", this->frameBucketCount);

	if(this->frameBucketCount != 0)
	{
		for (int i = 0; i < this->frameBucketCount; i++)
		{
			this->bone_data[i].Print("bone_Data", i);
		}
	}
	


}
