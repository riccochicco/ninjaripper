/*
+===========================================================================+
|                          Copyright (c) 1997-2000                          |
+---------------------------------------------------------------------------+
| File Name:                                                                |
|                                                                           |
|    CComPtr.h                                                              |
|                                                                           |
+---------------------------------------------------------------------------+
| Descriptions:                                                             |
|                                                                           |
|    Class CComPtr is a thin wrapper, which provides safe manipulation on   |
|    any interface pointers. It has several OPERATORs to make it like a     |
|    PURE interface pointer. It will AddRef() and Release() interface       |
|    pointer without your concern.                                          |
|                                                                           |
|    Actaully ATL has already provided such Smart Pointer from version 2.0. |
|    I just borrow its concept and implement it in PURE C++ so that it can  |
|    be compiled under any ANSI C/C++ Compliant compiler.                   |
|                                                                           |
+---------------------------------------------------------------------------+
| Developer(s):                                                             |
|                                                                           |
|    Xu Wen Bin                                                             |
|                                                                           |
+===========================================================================+
|                           C H A N G E    L O G                            |
+---------------------------------------------------------------------------+
|                                                                           |
|    09-16-2001    Created.                                                 |
|    09-17-2001    Modified.                                                |
|    02-21-2006    Modified.                                                |
|                                                                           |
+---------------------------------------------------------------------------+
| Note(s):                                                                  |
|                                                                           |
|    CComPtr does not support IUnknown interface. That is, you CAN'T use    |
|    CComPtr<IUnknown> to wrap an IUnknown interface pointer. Under most    |
|    conditions, IUnknown pointer will be provided by OS or HIGH layer code.|
|    So this is a reasonable LIMITATION.                                    |
|                                                                           |
+---------------------------------------------------------------------------+
*/

#ifndef _COMPTR_H_
#define _COMPTR_H_

template<class INTERFACE, const IID* piid = NULL>
class CComPtr
{
public:
    CComPtr()
    {
        m_Ptr = NULL;
    }
    CComPtr(INTERFACE* lPtr)
    {
        m_Ptr = NULL;

        if (lPtr != NULL)
        {
            m_Ptr = lPtr;
            m_Ptr->AddRef();
        }
    }
    CComPtr(const CComPtr<INTERFACE, piid>& RefComPtr)
    {
        m_Ptr = NULL;
        m_Ptr = (INTERFACE*)RefComPtr;

        if (m_Ptr)
        {
            m_Ptr->AddRef();
        }
    }
    CComPtr(IUnknown* pIUnknown, IID iid)
    {
        m_Ptr = NULL;

        if (pIUnknown != NULL)
        {
            pIUnknown->QueryInterface(iid, (void**)&m_Ptr);
        }
    }
    ~CComPtr()
    {
        if (m_Ptr)
        {
            m_Ptr->Release();
            m_Ptr = NULL;
        }
    }

public:
    operator INTERFACE*() const
    {
        ASSERT(m_Ptr != NULL);
        return m_Ptr;
    }
    INTERFACE& operator*() const
    {
        ASSERT(m_Ptr != NULL);
        return *m_Ptr;
    }
    INTERFACE** operator&()
    {
        ASSERT(m_Ptr != NULL);
        return &m_Ptr;
    }
    INTERFACE* operator->() const
    {
        ASSERT(m_Ptr != NULL);
        return m_Ptr;
    }
    INTERFACE* operator=(INTERFACE* lPtr)
    {
        ASSERT(lPtr != NULL);
        if (IsEqualObject(lPtr))
        {
            return m_Ptr;
        }
        m_Ptr->Release();
        lPtr->AddRef();
        m_Ptr = lPtr;
        return m_Ptr;
    }
    INTERFACE* operator=(IUnknown* pIUnknown)
    {
        ASSERT(pIUnknown != NULL);
        ASSERT(piid != NULL);
        pIUnknown->QueryInterface(*piid, (void**)&m_Ptr);
        ASSERT(m_Ptr != NULL);
        return m_Ptr;
    }
    INTERFACE* operator=(const CComPtr<INTERFACE, piid>& RefComPtr)
    {
        ASSERT(&RefComPtr != NULL);
        m_Ptr = (INTERFACE*)RefComPtr;

        if (m_Ptr)
        {
            m_Ptr->AddRef();
        }
        return m_Ptr;
    }
    void Attach(INTERFACE* lPtr)
    {
        if (lPtr)
        {
            m_Ptr->Release();
            m_Ptr = lPtr;
        }
    }
    INTERFACE* Detach()
    {
        INTERFACE* lPtr = m_Ptr;
        m_Ptr = NULL;
        return lPtr;
    }
    void Release()
    {
        if (m_Ptr)
        {
            m_Ptr->Release();
            m_Ptr = NULL;
        }
    }
    BOOL IsEqualObject(IUnknown* pOther)
    {
        ASSERT(pOther != NULL);
        IUnknown* pUnknown = NULL;
        m_Ptr->QueryInterface(IID_IUnknown, (void**)&pUnknown);
        BOOL Result = (pOther == pUnknown) ? TRUE : FALSE;
        pUnknown->Release();
        return Result;
    }

private:
    INTERFACE* m_Ptr;
};

#endif // _COMPTR_H_
