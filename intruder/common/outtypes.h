#pragma once



struct TCOLOR{
    float r;
    float g;
    float b;
    float a;
};


struct TMATERIAL {
    TCOLOR   Diffuse;        /* Diffuse color RGBA */
    TCOLOR   Ambient;        /* Ambient color RGB */
    TCOLOR   Specular;       /* Specular 'shininess' */
    TCOLOR   Emissive;       /* Emissive color RGB */
    float    Power;          /* Sharpness if specular highlight */
};


struct TSHADERS{
    char vsh[16];
    char psh[16];
};


struct TMESHTEXTURES{
    char texture_0[16];
    char texture_1[16];
    char texture_2[16];
    char texture_3[16];
    char texture_4[16];
    char texture_5[16];
    char texture_6[16];
    char texture_7[16];
};


struct TVERTEX{
    float v0;
    float v1;
    float v2;
    float v3;//new

    float n0;
    float n1;
    float n2;
    float n3;//new

    float tu;
    float tv;
};

struct TFACE{
    DWORD i0;
    DWORD i1;
    DWORD i2;
};


struct TRIPFILE2{
    DWORD         sign;
    DWORD         cSize;
    DWORD         dwVertices;
    DWORD         dwFaces;
    TMESHTEXTURES textures;
    TMATERIAL     material;
    TSHADERS      shaders;
};
