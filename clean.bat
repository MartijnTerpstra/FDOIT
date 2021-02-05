@ECHO OFF

REM - Remove build folders
RD .\Debug /S /Q
RD .\Release /S /Q
RD .\ipch /S /Q
RD .\.vs /S /Q
RD .\.vs /S /Q

REM - remove files
ATTRIB -H /S *.suo
DEL /F /Q /S *.suo
DEL /F /Q /S *.ncb
DEL /F /Q /S *.user
DEL /F /Q /S *.ilk
DEL /F /Q /S *.exp
DEL /F /Q /S *.pdb
DEL /F /Q /S *.sdf
DEL /F /Q *.lib
DEL /F /Q *_debug.exe
DEL /F /Q Template.exe
DEL /F /Q Demo.VC.db
DEL /F /Q .\ShaderHeaders\*.*
