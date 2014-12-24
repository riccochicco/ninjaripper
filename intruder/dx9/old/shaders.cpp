
#include "PreComp.h"
#include "shaders.h"
#include "predisp.h"
#include "intruder.h"

#define    MAX_VS_TO_SAVE 0x1000
#define MAX_PS_TO_SAVE 0x1000


static TVSRIP SavedVS[MAX_VS_TO_SAVE];
static TPSRIP SavedPS[MAX_PS_TO_SAVE];

static IDirect3DVertexShader9*    XShaderVS[MAX_VS_TO_SAVE]={0};
static DWORD VSNum=0;
static IDirect3DPixelShader9*    XShaderPS[MAX_PS_TO_SAVE]={0};
static DWORD PSNum=0;


static char *IsVSExist(IDirect3DVertexShader9 *pVsh, char *szFileName){

/*
    for(DWORD i=0; i<dwMeshsVS; i++){
        if(SavedVS[i].pVSH==pVsh) return SavedVS[i].vsh_name;
    }
    if(i<MAX_VS_TO_SAVE){
        SavedVS[i].pVSH=pVsh;
        strcpy(SavedVS[i].vsh_name, szFileName);
        dwMeshsVS++;
    }
    return 0;
    */
    return 0;
}

static char *IsPSExist(IDirect3DPixelShader9 *pPsh, char *szFileName){
    /*
    for(DWORD i=0; i<dwMeshsPS; i++){
        if(SavedPS[i].pPSH==pPsh) return SavedPS[i].psh_name;
    }
    if(i<MAX_PS_TO_SAVE){
        SavedPS[i].pPSH=pPsh;
        strcpy(SavedPS[i].psh_name, szFileName);
        dwMeshsPS++;
    }
    return 0;
    */
    return 0;
}



DWORD SaveVS(wchar_t *szFileName, IDirect3DVertexShader9 *pVsh){
    UINT    DataSize=0;
    void    *pData=0;
    ID3DXBuffer *DXBuffer=0;
    FILE*    fOutFile=0;
    DWORD    status=-1;
    HRESULT foo=0;
/*
    for(;;){
        foo = pVsh->GetFunction(0, &DataSize);
        if( FAILED(foo) ){
            g_log.Write(TEXT("IDirect3DVertexShader9::GetFunction Error: 0x%08X\n"), foo);
            break;
        }
        
        pData=malloc(DataSize);
        if(pData==0){
            g_log.Write(TEXT("malloc Error\n"));
            break;
        }

        foo = pVsh->GetFunction(pData, &DataSize);
        if( FAILED(foo) ){
            g_log.Write(TEXT("IDirect3DVertexShader9::GetFunction Error: 0x%08X\n"), foo);
            break;
        }

        foo = D3D9_D3DXDisassembleShader((DWORD*)pData, FALSE, 0, &DXBuffer);
        if( FAILED(foo) ){
            g_log.Write(TEXT("D3DXDisassembleShader Error: 0x%08X\n"), foo);
            break;
        }
        free(pData);

        fOutFile=_tfopen(szFileName, TEXT("w"));
        if(fOutFile==0){
            g_log.Write(TEXT("Can't Open File: %s"), szFileName);
            break;
        }
        fprintf(fOutFile, "%s", DXBuffer->GetBufferPointer());
        fclose(fOutFile);
        DXBuffer->Release();

        status=0;
        break;
    }

    return status;
    */
    return 0;
}


DWORD SavePS(wchar_t *szFileName, IDirect3DPixelShader9 *pPsh){
    UINT    DataSize=0;
    void    *pData=0;
    ID3DXBuffer *DXBuffer=0;
    FILE*    fOutFile=0;
    DWORD    status=-1;
    HRESULT foo=0;
/*
    for(;;){
        foo = pPsh->GetFunction(0, &DataSize);
        if( FAILED(foo) ){
            g_log.Write(TEXT("IDirect3DPixelShader9::GetFunction Error: 0x%08X\n"), foo);
            break;
        }

        pData=malloc(DataSize);
        if(pData==0){
            g_log.Write(TEXT("malloc Error\n"));
            break;
        }

        foo = pPsh->GetFunction(pData, &DataSize);
        if( FAILED(foo) ){
            g_log.Write(TEXT("IDirect3DPixelShader9::GetFunction Error: 0x%08X\n"), foo);
            break;
        }

        foo = D3D9_D3DXDisassembleShader((DWORD*)pData, FALSE, 0, &DXBuffer);
        if( FAILED(foo) ){
            g_log.Write(TEXT("D3DXDisassembleShader Error: 0x%08X\n"), foo);
            break;
        }
        free(pData);

        fOutFile=_tfopen(szFileName, TEXT("w"));
        if(fOutFile==0){
            g_log.Write(TEXT("Can't Open File: %s"), szFileName);
            break;
        }
        fprintf(fOutFile, "%s", DXBuffer->GetBufferPointer());
        fclose(fOutFile);
        DXBuffer->Release();

        status=0;
        break;
    }

    return status;
    */
    return 0;
}


void SaveShaders(IDirect3DDevice9 *pDev, TSHADERS *pShaders){
    /*
    wchar_t    szShaderName[MAX_PATH];
    char    szShaderNameA[16];
    IDirect3DVertexShader9 * pVsh=0;
    IDirect3DPixelShader9  * pPsh=0;
    HRESULT foo = 0;
    */
/*
    //////////////////////////////////////////////////////////////////////////
    //Save Vertex Shader
    //////////////////////////////////////////////////////////////////////////
    foo = pDev->GetVertexShader(&pVsh);
    //pVsh = pVertexShader;//v1.3.3

    if( pVsh ){
        if(pVsh!=0){
            sprintf(szShaderNameA, "%s%04d%s", szShader_A, dwMeshsInFrame, szVSExtA);
            _stprintf(szShaderName, TEXT("%s%s%s%s%02d\\%s%04d%s"), szTargetDir, szRipDir, szFramesDir , szFrame, dwFrames, szShader, dwMeshsInFrame, szVSExt);

            char * szExistedVS=IsVSExist(pVsh, szShaderNameA);
            if(szExistedVS!=0){
                //Already Saved VS
                strcpy(pShaders->vsh, szExistedVS);

                g_log.Write("VertexShader Already Saved As: %s\n", szExistedVS);
            }
            else{
                //New VS in Frame
                if(!SaveVS(szShaderName, pVsh)){
                    strcpy(pShaders->vsh, szShaderNameA);
                    g_log.Write(TEXT("VertexShader Saved As: %s\n"), szShaderName);
                }
                else{
                    g_log.Write(TEXT("VertexShader Save Error\n"));
                }
            }
            pVsh->Release();
        }
        else{
            g_log.Write(TEXT("VertexShader Not Set\n"));
        }
    }
    else{
        g_log.Write(TEXT("GetVertexShader Error: 0x%08X\n"), foo);
    }


    //////////////////////////////////////////////////////////////////////////
    //Save Pixel Shader
    //////////////////////////////////////////////////////////////////////////
    foo = pDev->GetPixelShader(&pPsh);
    //pPsh = pPixelShader;
    if( pPsh ){
        if(pPsh!=0){
            sprintf(szShaderNameA, "%s%04d%s", szShader_A, dwMeshsInFrame, szPSExtA);
            _stprintf(szShaderName, TEXT("%s%s%s%s%02d\\%s%04d%s"), szTargetDir, szRipDir, szFramesDir , szFrame, dwFrames, szShader, dwMeshsInFrame, szPSExt);

            char * szExistedPS=IsPSExist(pPsh, szShaderNameA);
            if(szExistedPS!=0){
                //Already Saved PS
                strcpy(pShaders->psh, szExistedPS);

                g_log.Write("PixelShader  Already Saved As: %s\n", szExistedPS);
            }
            else{
                //New PS in Frame
                if(!SavePS(szShaderName, pPsh)){
                    strcpy(pShaders->psh, szShaderNameA);
                    g_log.Write(TEXT("PixelShader  Saved As: %s\n"), szShaderName);
                }
                else{
                    g_log.Write(TEXT("PixelShader Save Error\n"));
                }
            }
            pPsh->Release();
        }
        else{
            g_log.Write(TEXT("PixelShader  Not Set\n"));
        }
    }
    else{
        g_log.Write(TEXT("GetPixelShader Error: 0x%08X\n"), foo);
    }

    */
}

static DWORD IsVSSaved(IDirect3DVertexShader9 *pvs){
/*
    for(DWORD i=0; i<VSNum; i++){
        if(XShaderVS[i]==pvs)
            return 1;
    }
    if(VSNum < MAX_VS_TO_SAVE){
        XShaderVS[VSNum]=pvs;
        VSNum++;
    }
    else{
        g_log.Write("No empty slot for vertex shader\n");
    }
    return 0;
    */
    return 0;
}

static DWORD IsPSSaved(IDirect3DPixelShader9 *pps){
/*
    for(DWORD i=0; i<PSNum; i++){
        if(XShaderPS[i]==pps)
            return 1;
    }

    if(PSNum < MAX_PS_TO_SAVE){
        XShaderPS[PSNum]=pps;
        PSNum++;
    }
    else{
        g_log.Write("No empty slot for pixel shader\n");
    }
    return 0;
    */
}

static DWORD ShadersRipperHelper(){
    static    DWORD fOutDirCreated=0;
/*
    wchar_t    szDirName[MAX_PATH];

    SHORT KeyState = GetAsyncKeyState( Options.ShadersRipKey );
    if(KeyState!=0){
        Options.fShadersRipOn ^= 1;//Trigger
        Sleep(2000);
    }

    if( Options.fShadersRipOn!=0 && fOutDirCreated==0){
        fOutDirCreated = 1;
        //Create Out Dirs
        lstrcpy(szDirName, szTargetDir);
        lstrcat(szDirName, szRipDir);            //Add "ripper\" string
        CreateDirectory(szDirName, 0);
        lstrcat(szDirName, szShadersDir);        //Add "shaders\" string
        CreateDirectory(szDirName, 0);
    }
    return Options.fShadersRipOn;

    */
    return 0;
}


HRESULT __stdcall mine_IDirect3DDevice9_SetPixelShader(IDirect3DDevice9 *pDev, IDirect3DPixelShader9 *pShader){
/*

    wchar_t szShaderName[MAX_PATH]={0};
    static DWORD ShaderNum = 0;

    PFN_IDirect3DDevice9_SetPixelShader e = (PFN_IDirect3DDevice9_SetPixelShader)phook_IDirect3DDevice9_SetPixelShader->exec;


    DWORD KeyPressed = ShadersRipperHelper();

    if(pShader!=0 && KeyPressed!=0){
//        __asm{
//            jmp $
//        }
        DWORD AlreadySaved = IsPSSaved(pShader);
        if(AlreadySaved==0){
            _stprintf(szShaderName, TEXT("%s%s%s%04d%s"), szTargetDir, szRipDir, szShadersDir, ShaderNum, szPSExt);
            //New PS
            if(!SavePS(szShaderName, pShader)){
                g_log.Write(TEXT("PixelShader Saved As: %s\n"), szShaderName);
                ShaderNum++;
            }
            else{
                g_log.Write(TEXT("PixelShader Save Error\n"));
            }
        }
    }
    return e(pDev, pShader);
    */
    return 0;
}

HRESULT __stdcall mine_IDirect3DDevice9_SetVertexShader(IDirect3DDevice9 *pDev, IDirect3DVertexShader9 *pShader){

/*
    wchar_t szShaderName[MAX_PATH]={0};
    static DWORD ShaderNum = 0;
    PFN_IDirect3DDevice9_SetVertexShader e = (PFN_IDirect3DDevice9_SetVertexShader)phook_IDirect3DDevice9_SetVertexShader->exec;


    DWORD KeyPressed = ShadersRipperHelper();

    if(pShader!=0 && KeyPressed!=0){
        DWORD AlreadySaved = IsVSSaved(pShader);
        if(AlreadySaved==0){
            _stprintf(szShaderName, TEXT("%s%s%s%04d%s"), szTargetDir, szRipDir, szShadersDir, ShaderNum, szVSExt);
            //New VS
            if(!SaveVS(szShaderName, pShader)){
                g_log.Write(TEXT("VertexShader Saved As: %s\n"), szShaderName);
                ShaderNum++;
            }
            else{
                g_log.Write(TEXT("VertexShader Save Error\n"));
            }
        }
    }
    return e(pDev, pShader);
    */
    return 0;
}
