//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ITERATOR_H
#define ITERATOR_H

#include "DLink.h"

class Iterator
{
public:
        virtual DLink *Next() = 0;
        virtual bool IsDone() = 0;
        virtual DLink *First() = 0;
        virtual DLink *Curr() = 0;

        virtual void Reset(DLink *pHead) = 0;
};

#endif
