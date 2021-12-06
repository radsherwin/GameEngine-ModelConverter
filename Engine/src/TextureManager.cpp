//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TextureManager.h"
#include "TGA.h"
#include "textureDataHelper.h"

TextureManager* TextureManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
TextureManager::TextureManager(int reserveNum, int reserveGrow)
    : ManBase(reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new Texture();
}

TextureManager::~TextureManager()
{
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Texture* pDeleteMe = (Texture*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Texture* pDeleteMe = (Texture*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void TextureManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new TextureManager(reserveNum, reserveGrow);
    }

}

void TextureManager::Destroy()
{
    TextureManager* pMan = TextureManager::privGetInstance();
    assert(pMan != nullptr);
    AZUL_UNUSED_VAR(pMan);

    delete TextureManager::posInstance;
    TextureManager::posInstance = nullptr;
}

Texture* TextureManager::Add(const char* const pName, Texture::Name name)
{
    TextureManager* pMan = TextureManager::privGetInstance();

    GLuint* pTextureID = new GLuint;

    // Load the texture and get the textureID
    assert(pName);
    pMan->privLoadTexture(pName, pTextureID);

    Texture* pNode = (Texture*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    pNode->Set(pName, name, pTextureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

    return pNode;
}
Texture* TextureManager::Add(meshData& mB, Texture::Name _name)
{
    TextureManager* pMan = TextureManager::privGetInstance();
    GLuint* pTextureID = new GLuint[mB.texCount];
    

    //Load the texture and get the textureID
    pMan->privLoadTexture(mB, pTextureID);
    //std::vector<Texture*> pNode(mB.texCount);

    Texture* pNode = (Texture*)pMan->baseAddToFront();

    //Initialize the date
    for(unsigned int i = 0; i < mB.texCount; i++)
    {
        pNode->Set
        (
            mB.text_color[i].pFileName,
            _name,
            pTextureID,
            textureDataHelper::Get(mB.text_color[i].minFilter),
            textureDataHelper::Get(mB.text_color[i].magFilter),
            textureDataHelper::Get(mB.text_color[i].wrapS),
            textureDataHelper::Get(mB.text_color[i].wrapT)
        );
    }

    return pNode;
}

Texture* TextureManager::Add(textureData& tB, Texture::Name _name)
{
    TextureManager* pMan = TextureManager::privGetInstance();
    GLuint* pTextureID = new GLuint[1];


    //Load the texture and get the textureID
    pMan->privLoadTexture(tB, pTextureID);
    //std::vector<Texture*> pNode(mB.texCount);

    Texture* pNode = (Texture*)pMan->baseAddToFront();

    //Initialize the date
    pNode->Set
    (
        tB.pFileName,
        _name,
        pTextureID,
        textureDataHelper::Get(tB.minFilter),
        textureDataHelper::Get(tB.magFilter),
        textureDataHelper::Get(tB.wrapS),
        textureDataHelper::Get(tB.wrapT)
    );


    return pNode;
}

Texture* TextureManager::Find(Texture::Name _name)
{
    TextureManager* pMan = TextureManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->name = _name;

    Texture* pData = (Texture*)pMan->baseFind(pMan->poNodeCompare);
    if(pData == nullptr) pData = pMan->Find(Texture::Name::PINK_ERROR);
    return pData;
}

GLuint* TextureManager::FindID(Texture::Name name)
{
    TextureManager* pMan = TextureManager::privGetInstance();
    assert(pMan != nullptr);

    Texture* pTexture = pMan->Find(name);
    assert(pTexture);

    return pTexture->textureID;
}

GLuint TextureManager::FindID(Texture::Name name, int _index)
{
    TextureManager* pMan = TextureManager::privGetInstance();
    assert(pMan != nullptr);

    Texture* pTexture = pMan->Find(name);
    assert(pTexture);

    return pTexture->textureID[_index];
}

void TextureManager::Remove(Texture* pNode)
{
    assert(pNode != nullptr);

    TextureManager* pMan = TextureManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void TextureManager::Dump()
{
    TextureManager* pMan = TextureManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
TextureManager* TextureManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* TextureManager::derivedCreateNode()
{
    DLink* pNodeBase = new Texture();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}



void TextureManager::privLoadTexture(const char* const _assetName, GLuint*& textureID)
{
    // Get an ID, for textures (OpenGL poor man's handle)
    glGenTextures(1, textureID);

    // Bind it.
    glBindTexture(GL_TEXTURE_2D, *textureID);

    // Loat the texture
    this->privLoadTGATexture(_assetName, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

void TextureManager::privLoadTexture(meshData& mB, GLuint*& textureID)
{
    //Get an ID, for textures (OpenGL poor man's handle)
    glGenTextures(mB.texCount, textureID);

    //Bind it
    for(int i = 0; i < (int)mB.texCount; i++)
    {
        this->privLoadRawTexture(mB.text_color[i], textureID[i]);
    }   
}

void TextureManager::privLoadTexture(textureData& tB, GLuint*& textureID)
{
    //Get an ID, for textures (OpenGL poor man's handle)
    glGenTextures(1, textureID);

    //Bind it
	this->privLoadRawTexture(tB, textureID[0]);
}

bool TextureManager::privLoadRawTexture(textureData& tD, GLuint texture)
{

    glBindTexture(GL_TEXTURE_2D, texture);
    assert(tD.as_is == false);
    void* pBits = tD.poData;
    assert(pBits);

    int nWidth = (int)tD.width;
    int nHeight = (int)tD.height;

    // Hard to verify.. best guess.. input RGBA, output RGBA
    int nComponents = this->privGetOpenGLValue(tD.nComponent);
    GLenum eFormat = this->privGetOpenGLValue(tD.eFormat);

    GLint minFilter = (GLint)textureDataHelper::Get(tD.minFilter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)textureDataHelper::Get(tD.wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)textureDataHelper::Get(tD.wrapT));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)textureDataHelper::Get(tD.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)textureDataHelper::Get(tD.magFilter));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

    if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
        minFilter == GL_LINEAR_MIPMAP_NEAREST ||
        minFilter == GL_NEAREST_MIPMAP_LINEAR ||
        minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

// Load a TGA as a 2D Texture. Completely initialize the state
bool TextureManager::privLoadTGATexture(const char* szFileName, GLint minFilter, GLint magFilter, GLint wrapMode)
{
    GLbyte* pBits;
    int nWidth, nHeight, nComponents;
    GLenum eFormat;

    // Read the texture bits
    pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
    if (pBits == nullptr)
    {
        return false;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrapMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

    free(pBits);

    if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
        minFilter == GL_LINEAR_MIPMAP_NEAREST ||
        minFilter == GL_NEAREST_MIPMAP_LINEAR ||
        minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}


//-----------------------------------------------------------------------------
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
//-----------------------------------------------------------------------------
GLbyte* TextureManager::gltReadTGABits(const char* szFileName, GLint* iWidth, GLint* iHeight, GLint* iComponents, GLenum* eFormat)
{
    FILE* pFile;			// File pointer
    TGAHEADER tgaHeader;		// TGA file header
    unsigned long lImageSize;		// Size in bytes of image
    short sDepth;			// Pixel depth;
    GLbyte* pBits = NULL;          // Pointer to bits

    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_RGB;
    *iComponents = GL_RGB;

    // Attempt to open the file
    fopen_s(&pFile, szFileName, "rb");
    if (pFile == NULL)
        return NULL;

    // Read in header (binary)
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);


    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;

    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;

    // Calculate size of image buffer
    lImageSize = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height * (unsigned int)sDepth;

    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if (pBits == NULL)
        return NULL;

    // Read in the bits
    // Check for read error. This should catch RLE or other 
    // weird formats that I don't want to recognize
    if (fread(pBits, lImageSize, 1, pFile) != 1)
    {
        free(pBits);
        return NULL;
    }

    // Set OpenGL format expected
    switch (sDepth)
    {

    case 3:     // Most likely case
        *eFormat = GL_BGR;
        *iComponents = GL_RGB;
        break;

    case 4:
        *eFormat = GL_BGRA;
        *iComponents = GL_RGBA;
        break;
    case 1:
        assert(false);
        // bad case - keenan
        // i commented out
      //  *eFormat = GL_LUMINANCE;
      //  *iComponents = GL_LUMINANCE;
        break;
    default:        // RGB
        // If on the iPhone, TGA's are BGR, and the iPhone does not 
        // support BGR without alpha, but it does support RGB,
        // so a simple swizzle of the red and blue bytes will suffice.
        // For faster iPhone loads however, save your TGA's with an Alpha!

        break;
    }


    // Done with File
    fclose(pFile);

    // Return pointer to image data
    return pBits;
}

GLenum TextureManager::privGetOpenGLValue(textureData::TEXTURE_EFORMAT eFormat) const
{
    GLenum val = 0;

    switch (eFormat)
    {
    case textureData::TEXTURE_EFORMAT::EFORMAT_BGR:
        val = GL_BGR;
        break;

    case textureData::TEXTURE_EFORMAT::EFORMAT_BGRA:
        val = GL_BGRA;
        break;

    case textureData::TEXTURE_EFORMAT::EFORMAT_RGB:
        val = GL_RGB;
        break;

    case textureData::TEXTURE_EFORMAT::EFORMAT_RGBA:
        val = GL_RGBA;
        break;

    default:
        assert(false);
    }

    return val;
}

GLint TextureManager::privGetOpenGLValue(textureData::TEXTURE_NCOMPONENT nComponent) const
{
    GLint val = 0;

    switch (nComponent)
    {
    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR:
        val = GL_BGR;
        break;

    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA:
        val = GL_BGRA;
        break;

    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB:
        val = GL_RGB;
        break;

    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA:
        val = GL_RGBA;
        break;

    default:
        assert(false);
    }

    return val;
}
