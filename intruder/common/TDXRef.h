#pragma once

#include <vector>

// Very simple COM ptr wrapper
template < class T >
class TDXRef
{
public:
    TDXRef():
    ptr( NULL )
    {

    }
    ~TDXRef(){
        if( ptr )
        {
            ptr->Release();
            ptr = NULL;
        }
    }

    T* get()
    {
        return ptr;
    }

    T** operator&()
    {
        return &ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    // Non copy
    TDXRef( const TDXRef& );
    TDXRef& operator=( const TDXRef& ) ;
private:
    T* ptr;
};





template < class T >
class TDXRefVec
{
public:
    TDXRefVec()
    {

    }

    
    TDXRefVec(size_t Size)
    {
        setSize(Size);
    }
    

    ~TDXRefVec(){
        for (size_t i = 0; i < refVec.size(); i++)
        {
            if (refVec[i])
                refVec[i]->Release();
        }
    }

    void setSize(size_t Size)
    {
        refVec.resize( Size );
        for (size_t i = 0; i < refVec.size(); i++)
        {
            refVec[i] = NULL;
        }
    }


    T** operator&()
    {
        return &refVec[0];
    }

    // Non copy
    TDXRefVec(const TDXRefVec&);
    TDXRefVec& operator=(const TDXRefVec&);
private:
    std::vector <T*> refVec;
};

