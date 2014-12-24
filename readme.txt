NINJA RIPPER
Utility to extract / ripping 3d models (mesh), textures, shaders directly from the running game.

current version: 1.1.2
-------------------------------------------------------------------------------------------------------------------------------------------
RIPPER
-------------------------------------------------------------------------------------------------------------------------------------------

RIPPER FEATURES
Extracting all available vertex information of the models (position, all the texture coordinates, normals, weights, BLENDWEIGHT, BLENDINDICES, BINORMAL, TANGENT), indices, textures, shaders. Theoretically all extracted information could be import in the 3D editor!
Support for D3D11, D3D9, D3D8 (processed, however not all methods/techniques, but should work for 95% of all games).

RIPPER FUNCTIONS DESCRIPTION 
• Target (DX8, DX9, DX11 application):

• Exe - field for a direct path for the executable file of the application/game
• Arg - field for additional settings for an executable file
• Dir - field for a direct path to the folder containing the executable file (entered automatically when you select .exe, no need to change by the default)

• No Wrapper - mode in which the ripper will try to run .exe of the application/game directly, using for ripping only intruder.dll, if this mode does not work (do not rip) then you need to select one of the wrapper modes!

• wrapper modes - a modes in which ripper will copy d3dX.dll in to a folder containing the executable file of the application/game, after this ripper windows can be closed, then you can start the game from any location, copied d3dX.dll will automatically clinging into the game. Thus no longer need to run the ripper himself for this game.

• D3D8 Wrapper - for directx8 games only
• D3D9 Wrapper - for directx9 games only
• D3D11 Wrapper - for directx11 games only

you need to delete .dll from the game folder manually (if necessary), ripper configurations is stored in the registry from now on!

• RUN - button to start the application/game

• Output Directory (directory for saving ripped models): 

• Dir - field for output folder (automatically entered), this folder can be selected manually, be sure that checkbox "Don't overwrite by EXE" is cheked
• Browse - button to explore folder with selected .exe file
• Don't overwrite by EXE - by activating this function, the choice of the executable file does not overwrite the output folder

• Settings:

• RIP - you can change rip button
• Forced to save (Textures) - activating this will forced saving only texture

-------------------------------------------------------------------------------------------------------------------------------------------
IMPORTER (for 3ds max only)
-------------------------------------------------------------------------------------------------------------------------------------------

IMPORTER FEATURES
to import models used 3ds max version 2009 and above. Importer can import models and uv-coordinates. Theoretically also possible to import any data  saved into .rip files, including the weight of the vertices, these weights are used to link models and bones. The only question in the generation of the skeleton and its connection with the model (vertices).

IMPORTER FUNCTIONS DESCRIPTION 
• Source select (source selection and the import mode):

• Group - import group files
• Single - import single files
• List File - import files from list (not implemented yet)

• Input Dir/File - import source, the file or folder (depending on the selected mode)
• RIP File Nums - field to enter the file numbers to import (Group mode only), the input format is: 0-15, 589, 67

• Vertex Format (selecting the model building settings):

• Auto - mode to automatically identify groups of data (vertices, normals, uv-coordinates), will work for most games
• Manual - mode for manual definition of groups of data, you needed to import the models of the new games (mostly directx11)

• Position (x,y,z) - fields for enter data defining the position of the vertices of the model, even in manual mode these parameters in 99% of games will not change
• Normal (x,y,z) - fields for enter data defining the normals at each vertex of the model (not implemented yet)
• TexCoord (u,v) - fields for enter data defining texture coordinates of the model, one of the most important parameters. For games, wich model imports without a proper uv-coordinates, a pair of UV always choosing by search. At the time is Identified that pairs can not exceed number 50, that is can be 6-7 or 18-19 or 24-25 or 39-40 etc. In very rare cases, a pair of uv can be 3-4 or 4-5 or 5-6, which is within the "normal field of definition", as well as 8-6 or 12-11, which is at odds with common sense, but may still be.

• Tex.0 File Level - choice of a number of the texture, which applies to the model after import
• Scale - the scale of the imported model
• Rotate - turn imported model on the selected axis 

• IMPORT - button to start the import process

-------------------------------------------------------------------------------------------------------------------------------------------
CONTACTS
-------------------------------------------------------------------------------------------------------------------------------------------

http://cgig.ru/ninjaripper/

English Instructions (author Tosyk)
http://cgig.ru/en/2012/10/ho-to-use-ninja-ripper/

Official website of the author:
http://blackninja2000.narod.ru/rus/directx_ripper.html

The official support page:
http://cgig.ru/forum/viewtopic.php?f=5&t=224
