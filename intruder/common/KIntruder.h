#pragma once

#include "IRipper.h"


class KIntruder{
public:

    //General ripper options
    //Keys, start flags, etc
    struct KSettings{
        //Control Keys
        DWORD TexturesRipKey;
        DWORD MeshsRipKey;

        UINT dwMinPrimitives;//Const==16
        UINT dwMinIndicies;
        UINT dwMinVertexCount;
        DWORD minFrameIntervalUs;
    };

    enum ETextureExt{
        EBMP,
        EDDS
    };

    enum EShaderExt{
        EVS,
        EPS
    };

    virtual ~KIntruder(){}
    KIntruder(HINSTANCE hIntruderDLL);
    
    BOOL Init();
    void Uninit();


    DWORD IsMeshRipEnabled()const{
        return fRipEnabled;
    }


    DWORD IsMeshsRipKeyPressed()const{
        return fMeshRipKeyPressed;
    }


    DWORD IsTexturesRipKeyPressed()const{
        return fTexturesKeyPressed;
    }
    
    void KeyHandler( IRipper* pRipper );

    void IncTextureIdx(){//Forced texture idx
        TextureIdx++;
    }

    void FrameHandler( IRipper* pRipper );
    
    const KSettings* GetSettings()const{
        return &Settings;
    }

    std::wstring GetFrameTextureSavePath( std::string& FileName, DWORD Ext, DWORD Level );
    
    std::wstring GetFrameMeshSavePath();

    std::wstring GetTextureSavePath( ETextureExt );//Forced to save texture path
    

    std::wstring GetTextureSavePath();//Forced to save texture path v2.0


    void IncFrameTextureIdx(){
        FrameTextureIdx++;
    }

    void IncFrameMeshIdx(){
        FrameMeshIdx++;
    }
    
    std::wstring GetIntruderDir(){
        return IntruderDir;
    }

    std::wstring GetOutputDir();  // "c:/asaasda/adadad/_Ripper/"


protected:
private:
    std::wstring GetFrameDir();   // "c:/aaasdd/sdad/fdassf_Ripper/Frames/Frame000/"
    
    std::wstring LastCreatedDir;

    void ReadSettings();

    KSettings Settings;
    HINSTANCE hIntruderDLL;
    std::wstring IntruderDir;//INTRUDER.DLL dir

    std::wstring OutDir;//Base out dir (from registry)
    std::wstring RipperDir;// XXXXX/_Ripper/ dir
    std::wstring TargetDir;//EXE directory
    std::wstring TexturesDir;//Forced to save textures path
    std::wstring FramesDir;//Frames

    DWORD fRipEnabled;
    
    DWORD fMeshRipKeyPressed;
    DWORD fTexturesKeyPressed;


    DWORD TextureIdx;//Forced texture idx "_ripper/textures/tex_NN"


    DWORD RipperDirCreated;
    DWORD FramesDirCreated;
    DWORD TexturesDirCreated;


    DWORD FrameIdx;            //Frame idx "_ripper/frames/frameNN"
    DWORD FrameMeshIdx;        //          "_ripper/frames/frameNN/mesh_XX"
    DWORD FrameTextureIdx;     //          "_ripper/frames/frameNN/tex_YY"

    //????????????????????????????
    DWORD FrameVertexShaderIdx;//          "_ripper/frames/frameNN/shaderZZ.vs"
    DWORD FramePixelShaderIdx;

    LARGE_INTEGER TimerFreq;
    LARGE_INTEGER frameStartTime;
};
