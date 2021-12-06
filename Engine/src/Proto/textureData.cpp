//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "textureData.h"

textureData::~textureData()
{
	delete[] this->poData;
	this->poData = nullptr;
}

textureData::textureData(   bool				_enabled,
							TEXTURE_TYPE        _textType,
							TEXTURE_MAG_FILTER  _magFilter,
							TEXTURE_MIN_FILTER  _minFilter,
							TEXTURE_WRAP        _wrapS,
							TEXTURE_WRAP        _wrapT,
							TEXTURE_PIXEL_TYPE	_pixel_type,
							TEXTURE_EFORMAT		_eFormat,
							TEXTURE_NCOMPONENT	_nComponent,
							unsigned int		_width,
							unsigned int		_height,
							unsigned int		_component,
							unsigned int		_bits,
							bool				_as_is,
							const char         *_pName,
							unsigned int        _dataSize,
							unsigned int		_hash,
							unsigned char      *_poData)
	: pFileName{0}
{
	this->enabled = _enabled;
	this->textType = _textType;
	this->magFilter = _magFilter;
	this->minFilter = _minFilter;
	this->wrapS = _wrapS;
	this->wrapT = _wrapT;
	this->pixel_type = _pixel_type;
	this->eFormat = _eFormat;
	this->nComponent = _nComponent;
	this->width = _width;
	this->height = _height;
	this->component = _component;
	this->bits = _bits;
	this->as_is = _as_is;
	this->hash = _hash;
	memcpy_s(this->pFileName, FILE_NAME_SIZE, _pName, FILE_NAME_SIZE - 1);
	this->dataSize = _dataSize;
	this->poData = new unsigned char[this->dataSize]();
	assert(this->poData);
	memcpy_s(this->poData, this->dataSize, _poData, _dataSize);
}

textureData::textureData()
	:pFileName{0}
{
	this->enabled = false;
	this->textType = TEXTURE_TYPE::DEFAULT;
	this->magFilter = TEXTURE_MAG_FILTER::DEFAULT;
	this->minFilter = TEXTURE_MIN_FILTER::DEFAULT;
	this->wrapS = TEXTURE_WRAP::DEFAULT;
	this->wrapT = TEXTURE_WRAP::DEFAULT;
	this->pixel_type = TEXTURE_PIXEL_TYPE::DEFAULT;
	this->eFormat = TEXTURE_EFORMAT::DEFAULT;
	this->nComponent = TEXTURE_NCOMPONENT::DEFAULT;
	this->width = 0;
	this->height = 0;
	this->component = 0;
	this->bits = 0;
	this->as_is = false;
	this->dataSize = 0;
	this->hash = 0;
	this->poData = nullptr;
}

textureData::textureData(const textureData &r)
{
	this->enabled = r.enabled;
	this->textType = r.textType;
	this->magFilter = r.magFilter;
	this->minFilter = r.minFilter;
	this->wrapS = r.wrapS;
	this->wrapT = r.wrapT;
	this->pixel_type = r.pixel_type;
	this->eFormat = r.eFormat;
	this->nComponent = r.nComponent;
	this->width = r.width;
	this->height = r.height;
	this->component = r.component;
	this->bits = r.bits;
	this->as_is = r.as_is;
	this->dataSize = r.dataSize;
	this->hash = r.hash;
	memcpy_s(this->pFileName, FILE_NAME_SIZE, r.pFileName, FILE_NAME_SIZE);

	this->poData = new unsigned char[this->dataSize]();
	assert(this->poData);
	memcpy_s(this->poData, this->dataSize, r.poData, r.dataSize);

}

textureData &textureData::operator = (const textureData &r)
{
	if(this != &r)
	{
		delete[] this->poData;
		this->poData = nullptr;

		this->enabled = r.enabled;
		this->textType = r.textType;
		this->magFilter = r.magFilter;
		this->minFilter = r.minFilter;
		this->wrapS = r.wrapS;
		this->wrapT = r.wrapT;
		this->pixel_type = r.pixel_type;
		this->eFormat = r.eFormat;
		this->nComponent = r.nComponent;
		this->width = r.width;
		this->height = r.height;
		this->component = r.component;
		this->bits = r.bits;
		this->as_is = r.as_is;
		this->dataSize = r.dataSize;
		this->hash = r.hash;
		memcpy_s(this->pFileName, FILE_NAME_SIZE, r.pFileName, FILE_NAME_SIZE);

		this->poData = new unsigned char[this->dataSize]();
		assert(this->poData);
		memcpy_s(this->poData, this->dataSize, r.poData, r.dataSize);
	}

	return *this;
}



void textureData::Serialize(textureData_proto &out) const
{
	out.set_enabled(this->enabled);
	out.set_texttype((textureData_proto_TEXTURE_TYPE)this->textType);
	out.set_magfilter((textureData_proto_TEXTURE_MAG_FILTER)this->magFilter);
	out.set_minfilter((textureData_proto_TEXTURE_MIN_FILTER)this->minFilter);
	out.set_wraps((textureData_proto_TEXTURE_WRAP)this->wrapS);
	out.set_wrapt((textureData_proto_TEXTURE_WRAP)this->wrapT);
	out.set_pixel_type((textureData_proto_TEXTURE_PIXEL_TYPE)this->pixel_type);
	out.set_eformat((textureData_proto_TEXTURE_EFORMAT)this->eFormat);
	out.set_ncomponent((textureData_proto_TEXTURE_NCOMPONENT)this->nComponent);
	out.set_width(this->width);
	out.set_height(this->height);
	out.set_component(this->component);
	out.set_bits(this->bits);
	out.set_as_is(this->as_is);
	out.set_hash(this->hash);
	// BinaryData 
	// First place "raw" into a string
	//     http://www.cplusplus.com/reference/string/string/string/
	//     from sequence(5): 	string(const char *s, size_t n);
	//     serialize the string

	out.set_filenamesize(FILE_NAME_SIZE);
	std::string s0((const char *)this->pFileName, FILE_NAME_SIZE);
	out.set_filenamedata(s0);

	out.set_datasize(this->dataSize);
	std::string s((const char *)this->poData, this->dataSize);
	out.set_podata(s);
}

void textureData::Deserialize(const textureData_proto &in)
{
	this->enabled = (bool)in.enabled();
	this->textType = (TEXTURE_TYPE)in.texttype();
	this->magFilter = (TEXTURE_MAG_FILTER)in.magfilter();
	this->minFilter = (TEXTURE_MIN_FILTER)in.minfilter();
	this->wrapS = (TEXTURE_WRAP)in.wraps();
	this->wrapT = (TEXTURE_WRAP)in.wrapt();
	this->pixel_type = (TEXTURE_PIXEL_TYPE)in.pixel_type();
	this->eFormat = (TEXTURE_EFORMAT)in.eformat();
	this->nComponent = (TEXTURE_NCOMPONENT)in.ncomponent();
	this->width = in.width();
	this->height = in.height();
	this->component = in.component();
	this->bits = in.bits();
	this->as_is = (bool)in.as_is();
	this->hash = in.hash();

	memcpy(this->pFileName, in.filenamedata().data(), in.filenamesize());

	this->dataSize = in.datasize();
	if(this->dataSize > 0)
	{
		this->poData = new unsigned char[this->dataSize]();
		assert(this->poData);
		memcpy(this->poData, in.podata().data(), this->dataSize);
	}
	
}

void textureData::Print(const char *const pName) const
{
	if (this != nullptr && this->enabled)
	{
		Trace::out("%s: \n", pName);
		Trace::out("      dataSize: %d \n", this->dataSize);
		if (poData != nullptr)
		{
			Trace::out("        poData: %2x %2x %2x %2x %2x \n",
				this->poData[0],
				this->poData[1],
				this->poData[2],
				this->poData[3],
				this->poData[4]);
		}
		Trace::out("         pName: %s\n", this->pFileName);
		Trace::out("         hash: %d\n", this->hash);
		Trace::out("      textType: %d\n", this->textType);
		Trace::out("     magFilter: %d \n", this->magFilter);
		Trace::out("     minFilter: %d\n", this->minFilter);
		Trace::out("         wrapS: %d \n", this->wrapS);
		Trace::out("         wrapT: %d \n", this->wrapT);
		Trace::out("         width: %d \n", this->width);
		Trace::out("        height: %d \n", this->height);
	}
}

void textureData::Print(const char* const pName, const int _count) const
{
	if (this != nullptr && this->enabled)
	{
		Trace::out("%s: %d\n", pName, _count);
		Trace::out("      dataSize: %d \n", this->dataSize);
		if(poData != nullptr)
		{
			Trace::out("        poData: %2x %2x %2x %2x %2x \n",
				this->poData[0],
				this->poData[1],
				this->poData[2],
				this->poData[3],
				this->poData[4]);
		}
		Trace::out("         pName: %s\n", this->pFileName);
		Trace::out("         hash: %d\n", this->hash);
		Trace::out("      textType: %d\n", this->textType);
		Trace::out("     magFilter: %d \n", this->magFilter);
		Trace::out("     minFilter: %d\n", this->minFilter);
		Trace::out("         wrapS: %d \n", this->wrapS);
		Trace::out("         wrapT: %d \n", this->wrapT);
		Trace::out("         width: %d \n", this->width);
		Trace::out("        height: %d \n", this->height);
	}
}

// --- End of File ---


