
#include "PreComp.h"
#include "textures.h"
#include "savetexture.h"
#include "predisp.h"


#define MAX_TEXTURES_SAVE_CNT    0x1000
#define    MAX_MESHSTEX_CNT        0x1000


static IDirect3DBaseTexture9* SavedTextures[MAX_TEXTURES_SAVE_CNT];
static TMESHTEXRIP    MeshTextures[MAX_MESHSTEX_CNT];


static wchar_t* D3DUSAGE2Text( DWORD x ){
    switch( x ){
        case D3DUSAGE_RENDERTARGET:
            return TEXT("D3DUSAGE_RENDERTARGET");
        case D3DUSAGE_DEPTHSTENCIL:
            return TEXT( "D3DUSAGE_DEPTHSTENCIL" );
        default:
            return TEXT( "Unknown usage" );
    }
}

static wchar_t* D3DPOOL2Text( D3DPOOL x ){
    switch( x ){
        case D3DPOOL_DEFAULT:
            return TEXT("D3DPOOL_DEFAULT" );
        case D3DPOOL_MANAGED:
            return TEXT( "D3DPOOL_MANAGED" );
        case D3DPOOL_SYSTEMMEM:
            return TEXT( "D3DPOOL_SYSTEMMEM" );
        case D3DPOOL_SCRATCH:
            return TEXT( "D3DPOOL_SCRATCH" );
        default:
            return TEXT( "Unknown pool type" );
    }
}

static wchar_t* D3DRESOURCETYPE2Text( D3DRESOURCETYPE x ){
    switch( x ){
        case D3DRTYPE_SURFACE:
            return TEXT( "D3DRTYPE_SURFACE" );
        case D3DRTYPE_VOLUME:
            return TEXT( "D3DRTYPE_VOLUME" );
        case D3DRTYPE_TEXTURE:
            return TEXT( "D3DRTYPE_TEXTURE" );
        case D3DRTYPE_VOLUMETEXTURE:
            return TEXT( "D3DRTYPE_VOLUMETEXTURE" );
        case D3DRTYPE_CUBETEXTURE:
            return TEXT( "D3DRTYPE_CUBETEXTURE" );
        case D3DRTYPE_VERTEXBUFFER:
            return TEXT( "D3DRTYPE_VERTEXBUFFER" );
        case D3DRTYPE_INDEXBUFFER:
            return TEXT( "D3DRTYPE_INDEXBUFFER" );
        default:
            return TEXT( "Unknown resource type" );
    }
};


static void LogTextureSaveError( IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture){

    /*
    HRESULT hr;
    D3DRESOURCETYPE Type = pTexture->GetType();
    g_log.Write(TEXT("Texture type: %d\n"), Type);
    if(Type == D3DRTYPE_TEXTURE){
        LPDIRECT3DTEXTURE9 pTex = static_cast <LPDIRECT3DTEXTURE9>( pTexture );
        D3DSURFACE_DESC desc;
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) ){
            g_log.Write(TEXT("Desc.Format: 0x%08X\n"), desc.Format );
            g_log.Write(TEXT("Desc.Type  : %d -> %s\n"), desc.Type, D3DRESOURCETYPE2Text( desc.Type ) );
            g_log.Write(TEXT("Desc.Usage : 0x%08X -> %s\n"), desc.Usage, D3DUSAGE2Text( desc.Usage ) );
            g_log.Write(TEXT("Desc.Pool  : %d -> %s\n"), desc.Pool, D3DPOOL2Text( desc.Pool ) );
            g_log.Write(TEXT("Desc.MultiSampleType : %d\n"), desc.MultiSampleType );
            g_log.Write(TEXT("Desc.Width : 0x%08X\n"), desc.Width );
            g_log.Write(TEXT("Desc.Height: 0x%08X\n"), desc.Height );
        }

    }
    */
}


HRESULT __stdcall mine_IDirect3DDevice9_SetTexture(IDirect3DDevice9 *pDev, DWORD Sampler, IDirect3DBaseTexture9 *pTexture){
    static    DWORD fOutDirCreated=0;
/*

    PFN_IDirect3DDevice9_SetTexture e=(PFN_IDirect3DDevice9_SetTexture)phook_IDirect3DDevice9_SetTexture->exec;
//    __asm _emit 0xCC


    SHORT KeyState = GetAsyncKeyState( Options.TexturesRipKey );
    if(KeyState!=0){
        Options.fTextureRipOn ^= 1;//Trigger
        Sleep(2000);
    }
    
    if( ( Options.fTextureRipOn != 0 ) && ( dwTexturesSaved < MAX_TEXTURES_SAVE_CNT ) ){
        wchar_t    szDirName[MAX_PATH] = {0};
        if(fOutDirCreated++==0){
            //Create Out Dirs
            lstrcpy(szDirName, szTargetDir);
            lstrcat(szDirName, szRipDir);        //Add "ripper\\" string
            CreateDirectory(szDirName, 0);
            lstrcat(szDirName, szTexDir);        //Add "textures\\" string
            CreateDirectory(szDirName, 0);
        }

        //Save Texture
        DWORD i, fExist=0;
        for(i=0; i<dwTexturesSaved; i++){
            if(SavedTextures[i]==pTexture){fExist=1; break;}
        }
        if(fExist==0){
            _stprintf(szDirName, TEXT( "%s%s%s%s%04d%s"), szTargetDir, szRipDir, szTexDir ,szTex ,dwTexturesSaved, szTexExt);
            DWORD res = SaveTexture(szDirName, pDev, pTexture);
            if( res == 0 ){
                g_log.Write(TEXT("Texture Saved: %s\n"), szDirName );
                SavedTextures[dwTexturesSaved]=pTexture;
                dwTexturesSaved++;
            }
            else{
                g_log.Write(TEXT("Texture Save Error: 0x%08X\n"), res);
                //LogTextureSaveError( pDev, pTexture );
            }
        }
    }
    //g_log.Write("SetTexture(0x%08X, 0x%08X, 0x%08X)\n", pDev, Sampler, pTexture);
    return e(pDev, Sampler, pTexture);

    */
    return 0;
}


void SaveMeshTextures(IDirect3DDevice9 *pDev, TMESHTEXTURES *pTexHead){

/*
    wchar_t    szTextureFileName[MAX_PATH];
    char    szTextureNameA[16];
    IDirect3DBaseTexture9 *pTexture;
    DWORD foo;

    for(DWORD i=0; i<8; i++){
        pTexture=0;

        HRESULT res=pDev->GetTexture(i, &pTexture);
        if(res!=D3D_OK){
            g_log.Write(TEXT("GetTexture Error: 0x%08X\n"), res);
        }
        else{
            if(pTexture!=0){
                sprintf(szTextureNameA, "%s%04d_%d%s", szMeshTexA, dwMeshsInFrame, i, szTexExtA);

                char *szExistedTexture=IsTextureExist(pTexture, szTextureNameA);

                _stprintf(szTextureFileName, TEXT("%s%s%s%s%02d\\%s%04d_%d%s"), szTargetDir, szRipDir, szFramesDir , szFrame, dwFrames, szMeshTex, dwMeshsInFrame, i, szTexExt);


                if(szExistedTexture!=0){
                    //Already Saved Texture
                    //Copy Texture Name To Header
                    strcpy((char *)(pTexHead->texture_0+16*i), szExistedTexture);

                    g_log.Write("Texture Stage #%d Already Saved As: %s\n", i, szExistedTexture);
                }
                else{
                    //New Texture In Model.
                    //Copy Texture Name To Header
                    strcpy((char *)(pTexHead->texture_0+16*i), szTextureNameA);

                    foo = SaveTexture(szTextureFileName, pDev, pTexture);
                    if(!foo){
                        g_log.Write(TEXT("Texture Stage #%d Saved: %s\n"), i, szTextureFileName);
                    }
                    else{
                        g_log.Write(TEXT("Texture Save Error: 0x%08X\n"), foo);
                        //LogTextureSaveError( pDev, pTexture );
                    }
                }
                pTexture->Release();
            }
            else{
                g_log.Write(TEXT("Texture Stage #%d Not Exist\n"), i);
            }
        }
    }

    */
}

static char * IsTextureExist(IDirect3DBaseTexture9 *pTexture, char *szFileName){
    /*
    for(DWORD i=0; i<dwMeshsTextures; i++){
        if(MeshTextures[i].pTex==pTexture) return MeshTextures[i].texname;
    }
    if(i<MAX_MESHSTEX_CNT){
        MeshTextures[i].pTex=pTexture;
        strcpy(MeshTextures[i].texname, szFileName);
        dwMeshsTextures++;
    }
    return 0;
    */
    return 0;
}
