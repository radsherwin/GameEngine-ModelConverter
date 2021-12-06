#include "boneData.h"

boneData::boneData()
{
	float* tmpFloats = new float[3];
	tmpFloats[0] = 0;
	tmpFloats[1] = 0;
	tmpFloats[2] = 0;
	this->pTranslation = new unsigned char[sizeof(float) * 3];
	memcpy(this->pTranslation, tmpFloats, sizeof(float) * 3);
	delete[] tmpFloats;

	tmpFloats = new float[4];
	tmpFloats[0] = 0;
	tmpFloats[1] = 0;
	tmpFloats[2] = 0;
	tmpFloats[3] = 1;
	this->pRotation = new unsigned char[sizeof(float) * 4];
	memcpy(this->pRotation, tmpFloats, sizeof(float) * 4);
	delete[] tmpFloats;

	tmpFloats = new float[3];
	tmpFloats[0] = 1;
	tmpFloats[1] = 1;
	tmpFloats[2] = 1;
	this->pScale = new unsigned char[sizeof(float) * 3];
	memcpy(this->pScale, tmpFloats, sizeof(float) * 3);
	delete[] tmpFloats;
}

boneData::boneData(const boneData& r)
{
	this->pTranslation = r.pTranslation;
	this->pRotation = r.pRotation;
	this->pScale =r.pScale;
}

boneData& boneData::operator=(const boneData& r)
{
	if(this!= &r)
	{
		this->pTranslation = r.pTranslation;
		this->pRotation = r.pRotation;
		this->pScale = r.pScale;
	}

	return *this;
}

boneData::~boneData()
{
	delete[] pTranslation;
	delete[] pRotation;
	delete[] pScale;
}

boneData::boneData(unsigned char* translation, unsigned char* rotation, unsigned char* scale)
{
	this->pTranslation = translation;
	this->pRotation = rotation;
	this->pScale = scale;
}

void boneData::Serialize(boneData_proto& out) const
{

	if(this->pTranslation != nullptr)
	{
		std::string s((const char*)this->pTranslation, sizeof(float)*3);
		out.set_translation(s);
	}

	if (this->pRotation != nullptr)
	{
		std::string s((const char*)this->pRotation, sizeof(float) * 4);
		out.set_rotation(s);
	}

	if (this->pScale != nullptr)
	{
		std::string s((const char*)this->pScale, sizeof(float) * 3);
		out.set_scale(s);
	}
}

void boneData::Deserialize(const boneData_proto& in)
{

	delete[] this->pTranslation;
	this->pTranslation = nullptr;
	
	this->pTranslation = new unsigned char[sizeof(float) * 3]();
	assert(this->pTranslation);
	memcpy(this->pTranslation, in.translation().data(), sizeof(float)*3);

	delete[] this->pRotation;
	this->pRotation = nullptr;

	this->pRotation = new unsigned char[sizeof(float) * 4]();
	assert(this->pRotation);
	memcpy(this->pRotation, in.rotation().data(), sizeof(float) * 4);

	delete[] this->pScale;
	this->pScale = nullptr;

	this->pScale = new unsigned char[sizeof(float) * 3]();
	assert(this->pScale);
	memcpy(this->pScale, in.scale().data(), sizeof(float) * 3);
	
}

void boneData::Print(const char* const pName, int count) const
{
	Trace::out("pName: %s %d\n", pName, count);

	float*p = (float*)(this->pTranslation);
	Trace::out("\tT[%d]: %5.4f %5.4f %5.4f\n", count, *&p[0], *&p[1], *&p[2]);

	p = (float*)(this->pRotation);
	Trace::out("\tR[%d]: %5.4f %5.4f %5.4f %5.4f\n", count, *&p[0], *&p[1], *&p[2], *&p[3]);

	p = (float*)(this->pScale);
	Trace::out("\tS[%d]: %5.4f %5.4f %5.4f\n", count, *&p[0], *&p[1], *&p[2]);

}
