//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H 

#include "ManBase.h"
#include "ShaderObject.h"

class ShaderManager : public ManBase
{
    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 0, int reserveGrow = 1);
    static void Destroy();
    static ShaderObject* Add(ShaderObject::Name name, const char* const pName);
    static ShaderObject* Find(ShaderObject::Name name);
    static void Remove(ShaderObject* pNode);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static ShaderManager* privGetInstance();

    ShaderManager() = delete;
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& oparator(const ShaderManager&) = delete;
    virtual ~ShaderManager();
    ShaderManager(int reserveNum, int reserveGrow);

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink* derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    ShaderObject* poNodeCompare;
    static ShaderManager* posInstance;

};


#endif