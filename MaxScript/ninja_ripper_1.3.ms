/* 
Ninja Ripper 1.1.2 3D Max Importer
Importer version 1.3 beta7

changes:

2013.01.09 (1.3 beta7):
- added uv Scale function
- improved model Scale function
 */

try (destroydialog nr_rollout) catch()

-- allow ~ 40 MB instead of just 7.5 MB. Prevents "Runtime Error: Out of scripter memory"
if (heapSize < 200000) then
	heapSize = 2000000
		
-- force useing one CPU core
if SysInfo.CPUCount == 1 then
     TargetAffinity = 1
    else (
     TargetAffinity = 0
     for CoreID = 2 to SysInfo.CPUCount do
      TargetAffinity = (Bit.Set TargetAffinity CoreID true)
    )
    SysInfo.ProcessAffinity = TargetAffinity


---Constants
global RipSignature   = 0xDEADC0DE
global RipFileVersion = 4


---Global vars
global g_ImportType = 1       --- Group/Single/List  (0,1,2)
global g_InputSrc   = ""      --- Source Dir/File
global g_VertexFormatRecog = 0 --- Auto/Manual  (0,1)
global g_Tex0_FileLev = 0

global g_PosX_Idx = 0
global g_PosY_Idx = 0
global g_PosZ_Idx = 0
global g_NormX_Idx = 0
global g_NormY_Idx = 0
global g_NormZ_Idx = 0
global g_Tc0_U_Idx = 0
global g_Tc0_V_Idx = 0

--Globals additional 
global g_ninjaScale = 100
global g_ninjarotX = 90
global g_ninjarotY = 0
global g_ninjarotZ = 0
global g_flipUV = 1
--global g_scaleUV = 1
global uvscaler = 1
global mdlscaler = 100

global g_enabler = true

-- fn NinjaRotationMatrix =
-- (
-- 	local angles = eulerAngles 0 -0 -90
-- 	--local angles = eulerAngles g_ninjarotZ -g_ninjarotY -g_ninjarotX
-- 	return angles as matrix3
-- )

fn isNumSeqNR str = ((trimLeft str ".0123456789").count == 0)

fn ReadStr bstream =
(
   local str = ""
   while true do
   (
      str0 = ReadByte bstream #unsigned
	  if str0 == 0 then exit
      str+= bit.intAsChar str0
   )
   str
)


fn  StringClear OrigStr =
(
	local Str = ""
	
	for j = 1 to OrigStr.count do (
		if OrigStr[ j ] != " " then( 
			Str = Str + OrigStr[ j ] 
		) 
	)
   Str
)


fn  CreateMeshName Num =
(
	local Str = "Mesh_"
	local StrNum = ""
	r0 = Num as Integer
	StrNum = formattedPrint r0 format:"#04u"

	Str = Str + StrNum as String
	Str = Str + ".rip"
	
	Str
)

----------------------------
fn ImportRip RipFilePath =
(
	f = fopen RipFilePath "rb"

	Signature     = readlong f #unsigned
	Version       = readlong f #unsigned

	if Version != RipFileVersion do(
		print "Not RIP file"
		---print ( "FileSig: " + Version as String )
		---print ( "Sig : " + RipFileVersion as String )
		return 0
	)

	dwFacesCnt    = readlong f #unsigned
	dwVertexesCnt = readlong f #unsigned
	VertexSize    = readlong f #unsigned
	TextureFilesCnt= readlong f #unsigned
	ShaderFilesCnt= readlong f #unsigned
	VertexAttributesCnt= readlong f #unsigned

	
	print ( "*****ImportRip() File: " + RipFilePath as String )
	print ( "dwFacesCnt=" + dwFacesCnt as String )
	print ( "dwVertexesCnt=" + dwVertexesCnt as String )
	print ( "VertexAttributesCnt=" + VertexAttributesCnt as String )
		
	
	VertexAttribTypesArray= #()   ---Contain all types
	TextureFiles = #()
	ShaderFiles  = #()
	
	Face_array = #()
	Normal_array = #()
	Vert_array = #()
	UV_array = #()		
		
	
	TempPosIdx = 0      ---Get only first index attribute flag
	TempNormalIdx = 0
	TempTexCoordIdx = 0

	---Read vertex attributes
	for i = 1 to VertexAttributesCnt do (
		Semantic = ReadStr f
		SemanticIndex = readlong f #unsigned
		Offset = readlong f #unsigned
		Size   = readlong f #unsigned
		TypeMapElements = readlong f #unsigned
		for j = 1 to TypeMapElements do (
			TypeElement = readlong f #unsigned
			append VertexAttribTypesArray TypeElement
		)
		print "------------"
		print( "Semantic="+ Semantic )
		print( "SemanticIndex=" + SemanticIndex as String )
		print( "Offset=" + Offset as String )
		print( "Size=" + Size as String )
		print( "TypeMapElements=" + TypeMapElements as String )

		---Recognize semantic if "AUTO" set
		if g_VertexFormatRecog == 0 do ( ---AUTO recognition	
			if Semantic == "POSITION" do (  --- Get as "XYZ_"
				if TempPosIdx == 0 do (
					g_PosX_Idx = Offset / 4
					g_PosY_Idx = g_PosX_Idx + 1
					g_PosZ_Idx = g_PosX_Idx + 2
					
					TempPosIdx = TempPosIdx + 1
				)
			)
			
			if Semantic == "NORMAL" do (
				if TempNormalIdx == 0 do (
					g_NormX_Idx = Offset / 4
					g_NormY_Idx = g_NormX_Idx + 1
					g_NormZ_Idx = g_NormX_Idx + 2
					
					TempNormalIdx = TempNormalIdx + 1
				)
			)
			
			if Semantic == "TEXCOORD" do (
				if TempTexCoordIdx == 0 do(
					g_Tc0_U_Idx = Offset / 4
					g_Tc0_V_Idx = g_Tc0_U_Idx + 1
					
					TempTexCoordIdx = TempTexCoordIdx + 1
				)
			)
		)
		
		
	)
	print "-----------------------------"
	
	---Read texture files list to array ( if present )
	for i = 1 to TextureFilesCnt do (
		TexFile = ReadStr f
		append TextureFiles ( TexFile as String )
	)
	
	
	---Read shader files list to array ( if present )
	for i = 1 to ShaderFilesCnt do (
		ShaderFile = ReadStr f
		append ShaderFiles ( ShaderFile as String )
	)	
		
	
	print ( "Texture Files:" )
	for i = 1 to TextureFiles.count do (
		print ( TextureFiles[ i ] as String )
	)
	print ( "------------" )
		
	
	---Read indexes
	for x = 1 to dwFacesCnt do(
		i0 = readlong f #unsigned
		i1 = readlong f #unsigned
		i2 = readlong f #unsigned
		append Face_array[i0+1,i1+1,i2+1]
		
---		print( "idx0: " + i0 as String + " idx1: " + i1 as String + " idx2: " + i2 as String )
	)
	
	
	print( "PosX idx: " + g_PosX_Idx as String )
	print( "PosY idx: " + g_PosY_Idx as String )
	print( "PosZ idx: " + g_PosZ_Idx as String )
	print( "NormX idx: " + g_NormX_Idx as String )
	print( "NormY idx: " + g_NormY_Idx as String )
	print( "NormZ idx: " + g_NormZ_Idx as String )
	print( "Tu0 idx: " + g_Tc0_U_Idx as String )
	print( "Tv0 idx: " + g_Tc0_V_Idx as String )
	
	
	---Read vertexes
	for k = 1 to dwVertexesCnt do(
	
	---print ( "VertexIdx : " + (k-1) as String )
	
		vx = 0.0
		vy = 0.0
		vz = 0.0
		vw = 0.0
		nx = 0.0
		ny = 0.0
		nz = 0.0
		nw = 0.0
		tu = 0.0
		tv = 0.0
	
		for j = 0 to VertexAttribTypesArray.count - 1 do(
		
---			print ( "VertAttr Idx: " + j as String )
			ElementType = VertexAttribTypesArray[ j + 1 ]
			if ElementType == 0 then (  --- EFLOAT
				z = readfloat f
			)
			else if ElementType == 1 then (  ---EUINT
				z = readlong f #unsigned
			)
			else if ElementType == 2 then (  ---ESINT
				z = readlong f #signed
			)
			else (
				z = readlong f #unsigned
			)
			
			if j == g_PosX_Idx do vx = z
			if j == g_PosY_Idx do vy = z
			if j == g_PosZ_Idx do vz = z
			
			if j == g_NormX_Idx do nx = z
			if j == g_NormY_Idx do ny = z
			if j == g_NormZ_Idx do nz = z
			
			if j == g_Tc0_U_Idx do tu = z
			if j == g_Tc0_V_Idx do tv = z
			
			
			vx = vx as Float
			vy = vy as Float
			vz = vz as Float
			
			nx = nx as Float
			ny = ny as Float
			nz = nz as Float
			
			tu = tu as Float
			tv = 1-tv as Float
		)
		append Vert_array[(vx * mdlscaler),(vy * mdlscaler),(vz * mdlscaler)]
		append Normal_array [nx,ny,nz]
		append UV_array[tu * uvscaler,tv * g_flipUV * uvscaler,0]
		--append UV_array[tu * g_scaleUV,tv * g_flipUV * g_scaleUV,0]uvscaler
		--append UV_array[tu * 0.00001,tv * g_flipUV * 0.00001,0]
		
		--print( "vx: " + vx as String + " vy: " + vy as String + " vz: " + vz as String )
		--print( "tu: " + tu as String + " tv: " + tv as String )
	)
	
	TexFile = TextureFiles [ 1 + g_Tex0_FileLev ]
	if TexFile == undefined do ( TexFile = "setka.png" )
	
	TexFileName = getFilenamePath RipFilePath 
	TexFileName = TexFileName + TexFile
	print ( "TEXTURE FILE: " + TexFileName )
	
	---Material
-- 	thenewmaterial = multimaterial numsubs:1
-- 	thenewsubmaterial = standardmaterial name:TexFile
-- 	thenewsubmaterial.diffusemap = bitmaptexture name:TexFile
-- 	thenewsubmaterial.diffusemap.filename = TexFileName
-- 	thenewmaterial.materiallist[1] = thenewsubmaterial
-- 	showtexturemap thenewsubmaterial thenewsubmaterial.diffusemap true
		
	thenewmaterial = standardmaterial name:TexFile
	thenewmaterial.diffusemap = bitmaptexture name:TexFile
	thenewmaterial.diffusemap.filename = TexFileName
-- 	thenewmaterial.bumpmap = bitmaptexture name:TexFile
-- 	thenewmaterial.bumpmap.filename = TexFileName
	showtexturemap thenewmaterial thenewmaterial.diffusemap true
	
	msh = mesh vertices:Vert_array faces:Face_array
	setNumTVerts msh UV_array.count
		
	for i = 1 to UV_array.count do (setTVert msh i UV_array[i]) 
	buildTVFaces msh false
	for i = 1 to Face_array.count do (setTVFace msh i Face_array[i])
	--for i = 1 to Normal_array.count do (setNormal msh j Normal_array[j])
		
	--Aplly mesh rotation
	currentMatrix = msh.transform
	preRotate currentMatrix (eulertoquat (eulerAngles g_ninjarotX g_ninjarotY g_ninjarotZ))
	msh.transform = currentMatrix
	resetxform msh
	maxOps.CollapseNode msh off
		
	msh.name = getFilenameFile RipFilePath
	msh.material = thenewmaterial	
	
	--Redraw screen
	completeredraw()
	gw.updateScreen()
)


rollout nr_rollout "Ninja Ripper Importer v1.3 beta7" width:300 height:430
(
	-- Source select
	groupBox grp1 "Source Select" pos:[5,5] width:289 height:113
	radioButtons RadioImport "" pos:[58,27] width:201 height:16 labels:#("Group", "Single", "List File") default:2 columns:3

	label lblInputFile "Input .rip File:" pos:[12,58] width:68 height:17 visible:true
	label lblInputDir "Input Dir:" pos:[12,58] width:68 height:17 visible:false
	label lblInputLst "Input .lst File:" pos:[12,58] width:68 height:17 visible:false
	editText InputSrc "" pos:[84,55] width:169 height:20
	button SelectSrc "..." pos:[260,56] width:26 height:19 toolTip:""
	
	label lbl10 "RIP File Nums" pos:[13,85] width:69 height:18 enabled:false
	editText RipList "" pos:[84,82] width:202 height:20 enabled:false
		
	-- Vertex Format
	groupBox grp2 "Vertex Layout" pos:[5,125] width:175 height:168 columns:2
	
	--imgTag theImgTag "Bitmap" pos:[5,150] width:168 height:20 bitmap:(bitmap 80 50 color:gray) align:#right

	radioButtons RadioVertexFormat "" pos:[38,144] width:48 height:32 enabled:true labels:#("Auto", "Manual") default:1 columns:2
		
	label lbl4 "Position" pos:[24,170] width:41 height:14 enabled:false
	spinner pos_x "x" pos:[21,195] width:38 height:20 type:#integer enabled:false
	spinner pos_y "y" pos:[21,225] width:38 height:20 type:#integer enabled:false
	spinner pos_z "z" pos:[21,256] width:38 height:20 type:#integer enabled:false
	
	label lbl7 "Normal" pos:[78,170] width:37 height:14 enabled:false
	spinner norm_x "x" pos:[73,195] width:38 height:20 type:#integer enabled:false
	spinner norm_y "y" pos:[73,225] width:38 height:20 type:#integer enabled:false
	spinner norm_z "z" pos:[73,256] width:38 height:20 type:#integer enabled:false
	
	label lbl5 "UV Coord" pos:[124,170] width:48 height:14 enabled:false
	spinner tc0_u "u" pos:[125,195] width:38 height:16 range:[0,500,0] type:#integer enabled:false
	spinner tc0_v "v" pos:[125,225] width:38 height:16 range:[0,500,0] type:#integer enabled:false
	--editText tc0_u "u" pos:[176,195] width:42 height:20
	--editText tc0_v "v" pos:[176,225] width:42 height:20
	--button plusUVone "+1" pos:[233,204] width:40 height:30 enabled:false
	
	--Transform
	groupBox grp4 "Transformations" pos:[185,125] width:109 height:168
	
	label lblscale "Scale" pos:[192,149] width:77 height:15 enabled:true
	edittext etscale "" pos:[221,149] width:65 height:16 enabled:true
	
	label lblrotateX "Rotate X" pos:[192,180] width:77 height:15 enabled:true
	spinner spnrotateX "" pos:[241,180] width:45 height:16 range:[0,360,g_ninjarotX] type:#float scale:90 type:#integer enabled:true
	
	label lblrotateY "Rotate Y" pos:[192,206] width:77 height:15 enabled:true
	spinner spnrotateY "" pos:[241,206] width:45 height:16 range:[0,360,g_ninjarotY] type:#float scale:90 type:#integer enabled:true
	
	label lblrotateZ "Rotate Z" pos:[192,232] width:77 height:15 enabled:true
	spinner spnrotateZ "" pos:[241,232] width:45 height:16 range:[0,360,g_ninjarotZ] type:#float scale:90 type:#integer enabled:true
	
	label uvscale "UV  x" pos:[192,260] width:77 height:15 enabled:true
	edittext etuvscale "" pos:[221,260] width:65 height:16 enabled:true
	
	label lbl6 "Tex.Num" pos:[15,309] width:70 height:15
 	spinner spnTex0Lev "" pos:[65,309] width:45 height:16 range:[0,7,0] type:#integer
	
	label lblflipuv "Flip UV Vertical" pos:[15,331] width:70 height:15
 	checkbox checkerUV pos:[97,331] checked:false
	
	-- Import button
	button BtnImport "IMPORT" pos:[185,301] width:109 height:52
	
	--on spnscale changed val do g_ninjaScale = val
	on spnrotateX changed val do g_ninjarotX = val
	on spnrotateY changed val do g_ninjarotY = val	
	on spnrotateZ changed val do g_ninjarotZ = val
	on g_enabler changed val do g_enabler = val

	--on nr_rollout open do etuvscale.text = "1"
	on etuvscale changed txt do
	(
		if not isNumSeqNR txt do
		(
			messagebox "You can write only numbers!"
			etuvscale.text = "1"
		)
	)
	
	on etscale changed txt do
	(
		if not isNumSeqNR txt do
		(
			messagebox "You can write only numbers!"
			etscale.text = "1"
		)
	)
	
	on etuvscale entered txt do
	uvscaler = etuvscale.text as float
	
	on etscale entered txt do
	mdlscaler = etscale.text as float

	on nr_rollout open  do (
		
		---Init values
		pos_x.value = 0
		pos_y.value = 1
		pos_z.value = 2
		
		norm_x.value = 3
		norm_y.value = 4
		norm_z.value = 5
		
		tc0_u.value  = 6
		tc0_v.value  = 7
		
		etuvscale.text = "1"
		etscale.text = "100"
	)
	
	-- 	on checkerUV changed UVstate do g_flipUV  = -1
	
	on checkerUV changed UVstate do (
		if checkerUV.checked == false do (
			g_flipUV  = 1
		)

		if checkerUV.checked == true then (
			g_flipUV  = -1
		)
	)
	
	on RadioVertexFormat changed state do
	(
		lbl4.enabled = not lbl4.enabled
		pos_x.enabled = not pos_x.enabled
		pos_y.enabled = not pos_y.enabled
		pos_z.enabled = not pos_z.enabled
		
		lbl5.enabled = not lbl5.enabled
		tc0_u.enabled = not tc0_u.enabled
		tc0_v.enabled = not tc0_v.enabled
	)
	
	on RadioImport changed state do
	(
		if RadioImport.state == 1 then (
			lbl10.enabled = true
			RipList.enabled = true
			lblInputFile.visible = false
			lblInputDir.visible = true
			lblInputLst.visible = false
			)
		else if RadioImport.state == 2 then (
			lbl10.enabled = false
			RipList.enabled = false
			lblInputFile.visible = true
			lblInputDir.visible = false
			lblInputLst.visible = false
			)
		else if RadioImport.state == 3 then (
			lbl10.enabled = false
			RipList.enabled = false
			lblInputFile.visible = false
			lblInputDir.visible = false
			lblInputLst.visible = true
			)
	)
	
	on SelectSrc pressed  do (
		if RadioImport.state == 1 then (	---Group
			g_InputSrc   = getSavePath caption:"Choose directory with .rip files" initialDir:"$scripts"
			if g_InputSrc != undefined do (
				g_InputSrc = g_InputSrc + "\\"
				g_ImportType  = 0
				InputSrc.text = g_InputSrc
				print ( "Dir selected: " + g_InputSrc )
			)
		)
		else if RadioImport.state == 2 then (   ---Single
			g_InputSrc = getOpenFileName \ 
							caption:"Ninja Ripper File Select" \
							types:"Ninja Ripper File(*.rip)|*.rip" \
							historyCategory:"Ninja Ripper"
			if g_InputSrc != undefined do (
				g_ImportType = 1
				InputSrc.text = g_InputSrc
				print ( "Single File selected: " + g_InputSrc )
			)
		)
		else if RadioImport.state == 3 then ( ---List file
			g_InputSrc = getOpenFileName \ 
							caption:"Ninja Ripper List File Select" \
							types:"Ninja Ripper List File(*.lst)|*.lst" \
							historyCategory:"Ninja Ripper"
			if g_InputSrc != undefined do(
				g_ImportType = 2
				InputSrc.text = g_InputSrc
				print ( "List File selected: " + g_InputSrc )
			)
		)
	)
	
	--Import button
	on BtnImport pressed  do (
		
		if RadioVertexFormat.state == 1 then ( ---Auto
			print "***Auto***"
			g_VertexFormatRecog = 0
			---Set default values
			g_PosX_Idx = 0
			g_PosY_Idx = 1
			g_PosZ_Idx = 2
						
			g_ninjarotX = spnrotateX.value
			g_ninjarotY = spnrotateY.value
			g_ninjarotZ = spnrotateZ.value
		)
		
		else ( ---Manual
			print "***Manual***"
			g_VertexFormatRecog = 1
			
			---Position
			g_PosX_Idx = ( pos_x.value as Integer )
			g_PosY_Idx = ( pos_y.value as Integer )
			g_PosZ_Idx = ( pos_z.value as Integer )
			
			---Normals
			g_NormX_Idx = ( norm_x.value as Integer )
			g_NormY_Idx = ( norm_y.value as Integer )
			g_NormZ_Idx = ( norm_z.value as Integer )

			---Tex coords
			g_Tc0_U_Idx = ( tc0_u.value as Integer )
			g_Tc0_V_Idx = ( tc0_v.value as Integer )
						
			g_ninjarotX = spnrotateX.value
			g_ninjarotY = spnrotateY.value
			g_ninjarotZ = spnrotateZ.value
		)
		
		g_Tex0_FileLev = spnTex0Lev.value as Integer
		
		
		---Import part
		if g_ImportType == 1 then ( ---Single file import
			if g_InputSrc.count > 0 then (  ImportRip g_InputSrc )
			else ( print "Select RIP file" )
		)
		else if g_ImportType == 0 then ( ---Group import
			
			if InputSrc.text.count > 0 then (
				if RipList.text.count > 0 then ( 
					RipDir = getFilenamePath InputSrc.text
					---print ( "RipDir: " + RipDir as String )
				
					tokens = filterString RipList.text ","
					FilteredTokens = #()
					
					---Remove token whitespaces
					for i = 1 to tokens.count do (
						---print ( "Tokens: " + tokens[i] as String )
						local Str = StringClear tokens[i]
						append FilteredTokens ( Str as String )
					)
					
					---Import loop. Split tokens with "-"
					for i = 1 to FilteredTokens.count do (
						print ( "Filtered Tokens: " + FilteredTokens[i] as String )
						RangeTokens = filterString FilteredTokens[ i ] "-"
						if RangeTokens.count == 1 then (  --Single element
							RipDir1 = RipDir
							ss = CreateMeshName RangeTokens[ 1 ]
							RipDir1 = RipDir1 + ss;
							print ( "Single Import:" + RipDir1 as String )
							ImportRip RipDir1
						)
						else(  ---Range element
							r0 = RangeTokens[1] as Integer
							r1 = RangeTokens[2] as Integer
							if r0 < r1 then (
								for j = r0 to r1 do(
									RipDir1 = RipDir
									ss = CreateMeshName j
									RipDir1 = RipDir1 + ss;
									print ( "Group Import:" + RipDir1 as String )
									ImportRip RipDir1
								)
							)
							else (
								print( "Incorrect range: " + r0 as String + " to " + r1 as String )
							)
						)
					)
						
				)
				else(
					print "Type file list"
				)
			)
			else (
				print "Select dir"
			)
		)
		else(
			print "Import from list file not realized"
		)
	)
)

createDialog nr_rollout 300 362 50 60