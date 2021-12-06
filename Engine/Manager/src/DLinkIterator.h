//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef	DLINK_ITERATOR_H
#define	DLINK_ITERATOR_H

#include "Iterator.h"

class DLinkIterator : public Iterator
{
public:
    DLinkIterator();


    virtual DLink *Next() override;
    virtual bool IsDone() override;
    virtual DLink *First() override;
    virtual DLink *Curr() override;

    virtual void Reset(DLink *pHead) override;

private:
    void privClear();

public:
    DLink *pHead;
    DLink *pCurr;
    bool bDone;
};

#endif

