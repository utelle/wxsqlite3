# Microsoft Developer Studio Project File - Name="wxsqlite3_vc6_dbadmin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dbadmin - Win32 Static Release Static
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxsqlite3_vc6_dbadmin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxsqlite3_vc6_dbadmin.mak" CFG="dbadmin - Win32 Static Release Static"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbadmin - Win32 DLL Debug DLL" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 DLL Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 DLL Release DLL" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 DLL Release Static" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 Static Debug DLL" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 Static Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 Static Release DLL" (based on "Win32 (x86) Application")
!MESSAGE "dbadmin - Win32 Static Release Static" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dbadmin - Win32 DLL Debug DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswud_dll\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswud_dll\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD BASE MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 DLL Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswud\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswud\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD BASE MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 DLL Release DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswu_dll\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswu_dll\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 DLL Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswu\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswu\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 Static Debug DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswud_dll\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswud_dll\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 Static Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswud\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswud\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Zi /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_WINDOWS" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i "..\sqlite3\include" /d _DEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib sqlite3.lib wxmsw29ud_stc.lib wxscintillad.lib wxmsw29ud_richtext.lib wxmsw29ud_aui.lib wxmsw29ud_adv.lib wxbase29ud_net.lib wxbase29ud_xml.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /debug /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 Static Release DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswu_dll\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswu_dll\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"

!ELSEIF  "$(CFG)" == "dbadmin - Win32 Static Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\dbadmin"
# PROP BASE Intermediate_Dir "vcmswu\dbadmin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\dbadmin"
# PROP Intermediate_Dir "vcmswu\dbadmin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /I "..\dbadmin" /I "..\sqlite3\include" /Fd..\dbadmin\dbadmin.pdb /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "__WXMSW__" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "_WINDOWS" /i "..\dbadmin" /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"
# ADD LINK32 ..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib sqlite3.lib wxmsw29u_stc.lib wxscintilla.lib wxmsw29u_richtext.lib wxmsw29u_aui.lib wxmsw29u_adv.lib wxbase29u_net.lib wxbase29u_xml.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /machine:i386 /out:"..\dbadmin\dbadmin.exe" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /subsystem:windows /libpath:"..\sqlite3\lib" /pdb:"..\dbadmin\dbadmin.pdb"

!ENDIF

# Begin Target

# Name "dbadmin - Win32 DLL Debug DLL"
# Name "dbadmin - Win32 DLL Debug Static"
# Name "dbadmin - Win32 DLL Release DLL"
# Name "dbadmin - Win32 DLL Release Static"
# Name "dbadmin - Win32 Static Debug DLL"
# Name "dbadmin - Win32 Static Debug Static"
# Name "dbadmin - Win32 Static Release DLL"
# Name "dbadmin - Win32 Static Release Static"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\dbadmin\aboutdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\addcolumn.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\attachdbdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\backrestdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\blobdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createindex.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createtable.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createtrigger.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createview.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\dbbook.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\describedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\detachdbdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\dropobject.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\encrypkeydlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\filterdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\indexbook.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\ipcframe.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\paneldata.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\preferences.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sortdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\specgrid.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlbook.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqleditor.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlhistory.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlite3table.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqliteplusframe.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlparameters.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\tablebook.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\triggerbook.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\triggerparser.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\viewbook.cpp
# End Source File
# Begin Source File

SOURCE=..\dbadmin\wxsqliteplus.rc
# End Source File
# Begin Source File

SOURCE=..\dbadmin\wxsqliteplusapp.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\dbadmin\aboutdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\addcolumn.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\attachdbdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\backrestdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\blobdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createindex.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createtable.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createtrigger.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\createview.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\dbbook.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\describedlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\detachdbdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\dropobject.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\encrypkeydlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\filterdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\indexbook.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\ipcframe.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\paneldata.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\preferences.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sortdlg.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\specgrid.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlbook.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqleditor.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlhistory.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlite3table.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqliteplusdef.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqliteplusframe.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\sqlparameters.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\tablebook.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\triggerbook.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\triggerparser.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\viewbook.h
# End Source File
# Begin Source File

SOURCE=..\dbadmin\wxsqliteplusapp.h
# End Source File
# End Group
# End Target
# End Project
