//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "vboData.h"

vboData::~vboData()
{
	delete[] this->poData;
	this->poData = nullptr;
}

vboData::vboData(  bool _enabled,
				   VBO_TARGET     _targetType,
	               VBO_COMPONENT  _componentType,
	               VBO_TYPE       _vboType,
	               unsigned int   _attribIndex,
	               unsigned int   _count,
	               unsigned int   _dataSize,
	               unsigned char *_poData)
{
	this->enabled = _enabled;
	this->targetType = _targetType;
	this->componentType = _componentType;
	this->vboType = _vboType;
	this->attribIndex = _attribIndex;
	this->count = _count;
	this->dataSize = _dataSize;
	this->poData = new unsigned char[this->dataSize]();
	assert(this->poData);
	memcpy_s(this->poData, this->dataSize, _poData, _dataSize);
}

vboData::vboData()
{
	this->enabled = false;
	targetType = VBO_TARGET::DEFAULT;
	componentType = VBO_COMPONENT::DEFAULT;
	vboType = VBO_TYPE::DEFAULT;
	attribIndex = 0;
	count = 0;
	dataSize = 0;
	poData = nullptr;
}

vboData::vboData(const vboData &r)
{
	this->enabled = r.enabled;
	this->targetType = r.targetType;
	this->componentType = r.componentType;
	this->vboType = r.vboType;
	this->attribIndex = r.attribIndex;
	this->count = r.count;
	this->dataSize = r.dataSize;

	this->poData = new unsigned char[this->dataSize]();
	assert(this->poData);
	memcpy_s(this->poData, this->dataSize, r.poData, r.dataSize);
}

vboData & vboData::operator = (const vboData &r)
{
	if(this != &r)
	{
		delete[] this->poData;
		this->poData = nullptr;
		this->enabled = r.enabled;
		this->targetType = r.targetType;
		this->componentType = r.componentType;
		this->vboType = r.vboType;
		this->attribIndex = r.attribIndex;
		this->count = r.count;
		this->dataSize = r.dataSize;

		this->poData = new unsigned char[this->dataSize]();
		assert(this->poData);
		memcpy_s(this->poData, this->dataSize, r.poData, r.dataSize);
	}

	return *this;
}


void vboData::Serialize(vboData_proto &out) const
{
	out.set_enabled(this->enabled);
	out.set_targettype((vboData_proto_VBO_TARGET)this->targetType);
	out.set_componenttype((vboData_proto_VBO_COMPONENT)this->componentType);
	out.set_vbotype((vboData_proto_VBO_TYPE)this->vboType);
	out.set_attribindex(this->attribIndex);
	out.set_count(this->count);
	out.set_datasize(this->dataSize);

	// BinaryData 
	// First place "raw" into a string
	//     http://www.cplusplus.com/reference/string/string/string/
	//     from sequence(5): 	string(const char *s, size_t n);
	//     serialize the string
	std::string s((const char *)this->poData, this->dataSize);
	out.set_podata(s);

}

void vboData::Deserialize(const vboData_proto &in)
{
	this->enabled = (bool)in.enabled();
	this->targetType = (VBO_TARGET)in.targettype();
	this->componentType = (VBO_COMPONENT)in.componenttype();
	this->vboType = (VBO_TYPE)in.vbotype();
	this->attribIndex = in.attribindex();
	this->count = in.count();
	this->dataSize = in.datasize();

	// release memory incase its been allocated
	delete[] this->poData;
	this->poData = nullptr;
	if(this->dataSize > 0)
	{
		this->poData = new unsigned char[this->dataSize]();
		assert(this->poData);
		memcpy(this->poData, in.podata().data(), this->dataSize);
	}
	

}

void vboData::Print(const char *const pName) const
{
	if (this != nullptr && this->enabled)
	{
		Trace::out("%s: \n", pName);
		Trace::out("       dataSize: %d \n", this->dataSize);
		if (poData != nullptr)
		{
			if (this->componentType == vboData::VBO_COMPONENT::FLOAT)
			{
				float* pX = (float*)&poData[0];
				float* pY = &pX[1];
				float* pZ = &pX[2];
				Trace::out(" poBuff: %f %f %f \n", *pX, *pY, *pZ);
			}
			else if (this->componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
			{
				int* pX = (int*)&poData[0];
				int* pY = &pX[1];
				int* pZ = &pX[2];
				Trace::out(" poBuff: %d %d %d \n", *pX, *pY, *pZ);
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			Trace::out(" poBuff: ------ \n");
		}
		Trace::out("    attribIndex: %d\n", this->attribIndex);
		Trace::out("          count: %d \n", this->count);
		Trace::out("  componentType: %d\n", this->componentType);
		Trace::out("        vboType: %d \n", this->vboType);
		Trace::out("     targetType: %d \n", this->targetType);

		Trace::out("\n");
	}
}

void vboData::Print(const char* const pName, int _count) const
{
	if (this != nullptr && this->enabled)
	{
		Trace::out("%s: %d\n", pName, _count);
		Trace::out("       dataSize: %d \n", this->dataSize);
		if (poData != nullptr)
		{
			if (this->componentType == vboData::VBO_COMPONENT::FLOAT)
			{
				float* pX = (float*)&poData[0];
				float* pY = &pX[1];
				float* pZ = &pX[2];
				Trace::out(" poBuff: %f %f %f \n", *pX, *pY, *pZ);
			}
			else if (this->componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
			{
				int* pX = (int*)&poData[0];
				int* pY = &pX[1];
				int* pZ = &pX[2];
				Trace::out(" poBuff: %d %d %d \n", *pX, *pY, *pZ);
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			Trace::out(" poBuff: ------ \n");
		}
		Trace::out("    attribIndex: %d\n", this->attribIndex);
		Trace::out("          count: %d \n", this->count);
		Trace::out("  componentType: %d\n", this->componentType);
		Trace::out("        vboType: %d \n", this->vboType);
		Trace::out("     targetType: %d \n", this->targetType);

		Trace::out("\n");
	}
}

// --- End of File ---


