//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ShaderManager.h"
#include "ShaderObject.h"

ShaderManager* ShaderManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
ShaderManager::ShaderManager(int reserveNum, int reserveGrow)
    : ManBase(reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new ShaderObject();
}

ShaderManager::~ShaderManager()
{
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        ShaderObject* pDeleteMe = (ShaderObject*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        ShaderObject* pDeleteMe = (ShaderObject*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void ShaderManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum >= 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new ShaderManager(reserveNum, reserveGrow);
    }

}

void ShaderManager::Destroy()
{
    ShaderManager* pMan = ShaderManager::privGetInstance();
    assert(pMan != nullptr);
    AZUL_UNUSED_VAR(pMan);

    delete ShaderManager::posInstance;
    ShaderManager::posInstance = nullptr;
}

ShaderObject* ShaderManager::Add(ShaderObject::Name name, const char* const pName)
{
    ShaderManager* pMan = ShaderManager::privGetInstance();

    ShaderObject* pNode = (ShaderObject*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    assert(pName);
    pNode->Set(name, pName);

    return pNode;
}

ShaderObject* ShaderManager::Find(ShaderObject::Name _name)
{
    ShaderManager* pMan = ShaderManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->name = _name;

    ShaderObject* pData = (ShaderObject*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void ShaderManager::Remove(ShaderObject* pNode)
{
    assert(pNode != nullptr);

    ShaderManager* pMan = ShaderManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void ShaderManager::Dump()
{
    ShaderManager* pMan = ShaderManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
ShaderManager* ShaderManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* ShaderManager::derivedCreateNode()
{
    DLink* pNodeBase = new ShaderObject();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}


