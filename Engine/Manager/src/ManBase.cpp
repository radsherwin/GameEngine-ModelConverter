//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ManBase.h"
#include "ListBase.h"
#include "DLinkMan.h"

//----------------------------------------------------------------------
 // Constructor
 //----------------------------------------------------------------------
ManBase::ManBase(int DeltaGrow)
{
    // Check now or pay later
    assert(DeltaGrow > 0);

    // Initialize all variables
    this->mDeltaGrow = DeltaGrow;
    this->mNumReserved = 0;
    this->mNumActive = 0;
    this->mTotalNumNodes = 0;
    this->poActive  = new DLinkMan();
    this->poReserve = new DLinkMan();
    assert(poActive != nullptr);
    assert(poReserve != nullptr);
}

ManBase::~ManBase()
{
    delete this->poActive;
    delete this->poReserve;

    this->poActive = nullptr;
    this->poReserve = nullptr;
}
//----------------------------------------------------------------------
// Base methods - called in Derived class but lives in Base
//----------------------------------------------------------------------

DLink * ManBase::baseAddToFront()
{
    Iterator *pIt = poReserve->GetIterator();
    assert(pIt != nullptr);

    // Are there any nodes on the Reserve list?
    if(pIt->First() == nullptr)
    {
        // refill the reserve list by the DeltaGrow
        this->proFillReservedPool(this->mDeltaGrow);
    }

    // Always take from the reserve list
    DLink *pNodeBase = poReserve->RemoveFromFront();
    assert(pNodeBase != nullptr);

    // Wash it
    pNodeBase->Wash();

    // Update stats
    this->mNumActive++;
    this->mNumReserved--;

    // copy to active
    poActive->AddToFront(pNodeBase);

    // YES - here's your new one (may its reused from reserved)
    return pNodeBase;
}

DLink * ManBase::baseAddToEnd()
{
    Iterator *pIt = poReserve->GetIterator();
    assert(pIt != nullptr);

    // Are there any nodes on the Reserve list?
    if(pIt->First() == nullptr)
    {
        // refill the reserve list by the DeltaGrow
        this->proFillReservedPool(this->mDeltaGrow);
    }

    // Always take from the reserve list
    DLink *pNodeBase = poReserve->RemoveFromFront();
    assert(pNodeBase != nullptr);

    // Wash it
    pNodeBase->Wash();

    // Update stats
    this->mNumActive++;
    this->mNumReserved--;

    // copy to active
    poActive->AddToEnd(pNodeBase);

    // YES - here's your new one (may its reused from reserved)
    return pNodeBase;
}

Iterator *ManBase::baseGetActiveIterator()
{
    return poActive->GetIterator();
}
Iterator *ManBase::baseGetReserveIterator()
{
    return poReserve->GetIterator();
}

DLink *ManBase::baseFind(DLink *pNodeTarget)
{
    // search the active list
    Iterator *pIt = poActive->GetIterator();

    DLink *pNode = pIt->First();

    // Walk through the nodes
    while(!pIt->IsDone())
    {
        if(pNode->Compare(pNodeTarget))
        {
            // found it
            break;
        }
        pNode = pIt->Next();
    }

    return pNode;
}

 void ManBase::baseRemove(DLink *pNodeBase)
{
   assert(pNodeBase != nullptr);

    // Don't do the work here... delegate it
    poActive->Remove(pNodeBase);

    // wash it before returning to reserve list
    pNodeBase->Wash();

    // add it to the return list
    poReserve->AddToFront(pNodeBase);

    // stats update
    this->mNumActive--;
    this->mNumReserved++;
}

void ManBase::baseDump()
{
    Trace::out("   --- %s: Begin --- \n", STRING_ME(ManBase));
    Trace::out("\n");

    Trace::out("         mDeltaGrow: %d \n", mDeltaGrow);
    Trace::out("     mTotalNumNodes: %d \n", mTotalNumNodes);
    Trace::out("       mNumReserved: %d \n", mNumReserved);
    Trace::out("         mNumActive: %d \n", mNumActive);
    Trace::out("\n");

    Iterator *pItActive = poActive->GetIterator();
    assert(pItActive != nullptr);

    DLink *pNodeActive = pItActive->First();
    if(pNodeActive == nullptr)
    {
        Trace::out("    Active Head: null\n");
    }
    else
    {
        Trace::out("    Active Head: (%p)\n", pNodeActive);
    }

    Iterator *pItReserve = poReserve->GetIterator();
    assert(pItReserve != nullptr);

    DLink *pNodeReserve = pItReserve->First();
    if(pNodeReserve == nullptr)
    {
        Trace::out("   Reserve Head: null\n");
    }
    else
    {
        Trace::out("   Reserve Head: (%p)\n", pNodeReserve);
    }
    Trace::out("\n");

    Trace::out("   ------ Active List: -----------\n");


    int i = 0;
    DLink *pData = pItActive->First();
    while(!pItActive->IsDone())
    {
        Trace::out("   %d: -------------\n", i);
        pData->Dump();
        i++;
        pData = pItActive->Next();
    }

    Trace::out("\n");
    Trace::out("   ------ Reserve List: ----------\n");

    i = 0;
    pData = pItReserve->First();
    while(!pItReserve->IsDone())
    {
        Trace::out("   %d: -------------\n", i);
        pData->Dump();
        i++;
        pData = pItReserve->Next();
    }
    Trace::out("\n");
    Trace::out("   --- %s: End--- \n", STRING_ME(ManBase));
    Trace::out("\n");
}


//----------------------------------------------------------------------
// Private methods - helpers
//----------------------------------------------------------------------
void ManBase::proFillReservedPool(int count)
{
    // doesn't make sense if its not at least 1
    assert(count >= 0);

    this->mTotalNumNodes += count;
    this->mNumReserved += count;

    // Preload the reserve
    for(int i = 0; i < count; i++)
    {
        DLink *pNode = this->derivedCreateNode();
        assert(pNode != nullptr);

        poReserve->AddToFront(pNode);
    }
}

