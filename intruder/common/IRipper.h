#pragma once


enum ERIP_ERR{
    E_UNK_ERR     = 0x88885000,
    E_MALLOC_ERR,
    E_UNK_INDEX_FORMAT_ERR ,
    E_FUNC_NOT_FOUND,
    E_INPUT_LAYOUT_NOT_FOUND,
    E_INPUT_TYPE_ERR,
    E_UNS_PRIM_TOPOLOGY,
    E_NULL_BUFF,
    E_COPY_BUFFER_ERR,
    E_MAP_ERR,
    E_VERTEXDECL_NOT_SET,
    E_FVF_NULL,
    E_NOTREALIZED,
    E_TEXTURE_FORMAT_ERR,
    E_NULL_TEXTURE,
    ERIP_FORCE_DWORD = 0xFFFFFFFFUL
};


class IRipper{

public:
    virtual ~IRipper(){}
    virtual void FrameStart() = 0;
    virtual void FrameEnd() = 0;
    virtual void TextureRipStart() = 0;
    virtual void TextureRipEnd() = 0;
};

