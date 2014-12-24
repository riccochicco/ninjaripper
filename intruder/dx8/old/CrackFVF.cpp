///////////////////////////////////////////////////////////////////////
// File : CrackFVF.cpp
// Description : Flexible-Vertex-Format (FVF) Cracking Functions
//                 Implementation
//
// Author : Wessam Bahnassi
///////////////////////////////////////////////////////////////////////


/////////////////// #includes ///////////////////
#include "PreComp.h"
#include "KRipper8.h"

//////////////////////////////// Global Functions Implementations ////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Function Name : GetTexCoordSetsCount
//
// Purpose : Returns the number of Texture Coordinates Sets defined in
//             a Flexible-Vertex-Format.
//
// Params :
//    DWORD dwFVF : An FVF code that contains the Texture Coordinate Sets definition.
//
// Return Value : The number of Texture Coordinate Sets defined within the passed FVF code.
//                  Valid values range from 1 to 8. If no textures sets were defined within
//                  'dwFVF', then the return value is 0.
//
// Author : Craig Peeper (Microsoft)
/////////////////////////////////////////////////////////////////////////////////////////////
DWORD KRipper8::GetTexCoordSetsCount(DWORD dwFVF)
{
    return ((dwFVF & D3DFVF_TEXCOUNT_MASK)>>D3DFVF_TEXCOUNT_SHIFT);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Function Name : GetTexCoordSetSize
//
// Purpose : Returns the size (in Bytes) of a Texture Coordinates Set defined in
//             a Flexible-Vertex-Format.
//
// Params :
//    DWORD dwFVF : An FVF code that contains Texture Coordinate Sets definitions.
//    BYTE Index : The index of the requested Texture Coordinates Set. Valid values range
//                   from 0 to 7 (inclusive). More precisely, 'Index' must be in the range
//                   from 0 to the number of textures defined minus one.
//
// Return Value : The size (in Bytes) of the requested Texture Coordinates Set. If the
//                  Set wasn't defined in 'dwFVF', then the function returns an error value
//                  that is 0.
//
// Author : Craig Peeper (Microsoft) (Additional Code by: Wessam Bahnassi)
/////////////////////////////////////////////////////////////////////////////////////////////
DWORD KRipper8::GetTexCoordSetSize(DWORD dwFVF,BYTE Index)
{
    // Check if there are any textures defined
    if ( !(dwFVF & D3DFVF_TEXCOUNT_MASK) )
        return 0;    // Error Code

    const DWORD x_rgdwTexCoordSize[] = { 8, 12, 16, 4};
    return x_rgdwTexCoordSize[(dwFVF >> (16 + Index * 2)) & 0x3];
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Function Name : GetFVFComponentOffset
//
// Purpose : Returns the offset (in Bytes) of a vertex component within the structure that
//             resembles its Flexible-Vertex-Format (FVF) code.
//
// Params :
//    DWORD dwFVF : A valid FVF code that expresses the whole vertex structure.
//    DWORD dwFVFComponent : The FVF Code of the component that you want to recieve
//                             its offset inside the vertex structure. Pass single codes
//                             only. Combined codes are invalid and might fail or return
//                             undefined results. Also, the following FVF flags are invalid :
//                                    D3DFVF_TEX0 through D3DFVF_TEX8,
//                                    D3DFVF_POSITION_MASK,
//                                    D3DFVF_RESERVED0 through D3DFVF_RESERVED2,
//                                    D3DFVF_TEXCOUNT_MASK,
//                                    D3DFVF_LASTBETA_UBYTE4,
//                                    D3DFVF_TEXCOUNT_SHIFT.
//    BYTE iTexCoordIndex : The index of the requested Texture Coordinates Set.
//                            If 'dwFVFComponent' is a Texture Coordinates Set FVF, then
//                            this parameter must be set to the same index passed to the
//                            D3DFVF_TEXCOORDSIZEn macro used to build 'dwFVFComponent'.
//                            If 'dwFVFComponent' is not a Texture Coordinates Set FVF, then
//                            this parameter is ignored.
//
// Return Value : The offset (in Bytes) of the requested component inside the vertex
//                  structure. If one of the parameters were invalid, or 'dwFVFComponent' is
//                  not part of 'dwFVF', then the function fails and the return value
//                  is 0xFFFFFFFF.
//
// Notes : This function cannot find the offset of a 2D Texture Coordinates Set if more
//           than one 2D Set is defined in 'dwFVF'. The function will find only the first
//           2D Set, and ignores the rest, returning the offset of the first 2D Set even
//           if another 2D Set was requested. However, this doesn't affect other Texture
//           Coordinates Sets. Please read the complete documentation of this function for
//           more details.
//
// Author : Wessam Bahnassi (Original Code by: Craig Peeper (Microsoft))
/////////////////////////////////////////////////////////////////////////////////////////////
DWORD KRipper8::GetFVFComponentOffset(DWORD dwFVF,DWORD dwFVFComponent,BYTE iTexCoordIndex)
{
    if (dwFVF == 0)
        return 0xFFFFFFFF;    // Error Code

    // If the component isn't part of the vertex definition then return error
    // with one exception, the D3DFVF_TEXTUREFORMAT2 flag
    if (((dwFVFComponent & dwFVF) != dwFVFComponent) && (dwFVFComponent != 0))
        return 0xFFFFFFFF;    // Error Code

// Internal Macro for checking whether we arrived to
// the required component, and returning the offset if so
#define RETURN_IF_MATCH_FVF(FVFCode) if(dwFVFComponent==FVFCode){return oCur;}

    DWORD oCur;
    DWORD dwPosition;
    BYTE FloatSize = sizeof(float);
    BYTE DWORDSize = sizeof(DWORD);

    // Start from Zero. Since this is a general function, it doesn't
    // require a strictly valid FVF. For example, we might recieve an
    // FVF code without D3DFVF_XYZ and process it succesfully.
    oCur = 0;

    // Mask position
    dwPosition = dwFVF & D3DFVF_POSITION_MASK;

    // Position is always at the start
    if (dwFVFComponent != 0)
        RETURN_IF_MATCH_FVF(dwPosition);

    // Increase the offset
    switch (dwPosition)
    {
    case D3DFVF_XYZ:
        oCur+=3*FloatSize;    // X,Y and Z
        break;

    case D3DFVF_XYZRHW:
        oCur+=4*FloatSize;    // X,Y,Z and RHW
        break;

    case D3DFVF_XYZB1:
        oCur+=3*FloatSize+FloatSize;    // X,Y,Z and 1 Blending Weight (Beta)
        break;

    case D3DFVF_XYZB2:
        oCur+=3*FloatSize+2*FloatSize;    // X,Y,Z and 2 Betas
        break;

    case D3DFVF_XYZB3:
        oCur+=3*FloatSize+3*FloatSize;    // X,Y,Z and 3 Betas
        break;

    case D3DFVF_XYZB4:
        oCur+=3*FloatSize+4*FloatSize;    // X,Y,Z and 4 Betas
        break;

    case D3DFVF_XYZB5:
        oCur+=3*FloatSize+5*FloatSize;    // X,Y,Z and 5 Betas
        break;
    }

    // Normals come next
    RETURN_IF_MATCH_FVF(D3DFVF_NORMAL);
    if ( dwFVF & D3DFVF_NORMAL )
        oCur += 3*FloatSize;    // X,Y and Z

    // Point Size
    RETURN_IF_MATCH_FVF(D3DFVF_PSIZE);
    if ( dwFVF & D3DFVF_PSIZE )
        oCur += FloatSize;    // A single float

    // Vertex Diffuse
    RETURN_IF_MATCH_FVF(D3DFVF_DIFFUSE);
    if ( dwFVF & D3DFVF_DIFFUSE )
        oCur += DWORDSize;    // BGRA encoded in one DWORD

    // Vertex Specular
    RETURN_IF_MATCH_FVF(D3DFVF_SPECULAR);
    if ( dwFVF & D3DFVF_SPECULAR )
        oCur += DWORDSize;    // BGRA encoded in one DWORD

    // Finally, Texture Coordinate Sets
    // Eight sets, each one might have 1,2,3 or 4 floats
    BYTE cTexCoords;

    // Get the number of Coordinate Sets
    cTexCoords = (BYTE)GetTexCoordSetsCount(dwFVF);
    if ( cTexCoords == 0 )
    {
        // If we arrived here, then we recieved an invalid
        // (unsupported) FVF component code (e.g. D3DFVF_LASTBETA_UBYTE4)
        return 0xFFFFFFFF;    // Error Code
    }

    // There are Texture Coordinate Sets, we'll loop around
    // the number of sets defined, with each loop, we'll
    // construct several FVFs and compare them to the passed FVF
    // component 'dwFVFComponent'. If one matches, then we return
    // the final offset value, otherwise, we'll just increase the
    // offset by the size of the set at current index.
    for (BYTE i=0;i<cTexCoords;i++)
    {
        // Get the size of this coordinate set
        BYTE Size = (BYTE)GetTexCoordSetSize(dwFVF,i);

        if (Size == 0)    // Invalid Texture Coordinate Set
            return 0xFFFFFFFF;    // Error Code

        if (Size == FloatSize)
        {
            // 1D Texture Coordinate Set
            RETURN_IF_MATCH_FVF((DWORD)D3DFVF_TEXCOORDSIZE1(i));
            oCur += FloatSize;
        }

        if (Size == FloatSize*2)
        {
            // 2D Texture Coordinate Set
            if (i == iTexCoordIndex)
            {
                RETURN_IF_MATCH_FVF((DWORD)D3DFVF_TEXCOORDSIZE2(i));
            }
            oCur += FloatSize*2;
        }

        if (Size == FloatSize*3)
        {
            // 3D Texture Coordinate Set
            RETURN_IF_MATCH_FVF((DWORD)D3DFVF_TEXCOORDSIZE3(i));
            oCur += FloatSize*3;
        }

        if (Size == FloatSize*4)
        {
            // 4D Texture Coordinate Set
            RETURN_IF_MATCH_FVF((DWORD)D3DFVF_TEXCOORDSIZE4(i));
            oCur += FloatSize*4;
        }
    }    // For each coordinate set Loop

    // If we arrived here, then we recieved an invalid
    // (unsupported) FVF component code that contains
    // an invalid Texture-Coordinate-Set definition.
    return 0xFFFFFFFF;    // Error Code
}


////////////////// End of File : CrackFVF.cpp //////////////////