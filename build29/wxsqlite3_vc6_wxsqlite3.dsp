# Microsoft Developer Studio Project File - Name="wxsqlite3_vc6_wxsqlite3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=wxsqlite3 - Win32 Static Release Multilib Static
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxsqlite3_vc6_wxsqlite3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxsqlite3_vc6_wxsqlite3.mak" CFG="wxsqlite3 - Win32 Static Release Multilib Static"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wxsqlite3 - Win32 DLL Debug Monolithic DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 DLL Debug Monolithic Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 DLL Debug Multilib DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 DLL Debug Multilib Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 DLL Release Monolithic DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 DLL Release Monolithic Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 DLL Release Multilib DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 DLL Release Multilib Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 Static Debug Monolithic DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 Static Debug Monolithic Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 Static Debug Multilib DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 Static Debug Multilib Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 Static Release Monolithic DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 Static Release Monolithic Static" (based on "Win32 (x86) Static Library")
!MESSAGE "wxsqlite3 - Win32 Static Release Multilib DLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wxsqlite3 - Win32 Static Release Multilib Static" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxsqlite3 - Win32 DLL Debug Monolithic DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_dll"
# PROP Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Debug Monolithic Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswud\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswud\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Debug Multilib DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_dll"
# PROP Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_dll\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Debug Multilib Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswud\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswud\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Release Monolithic DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_dll"
# PROP Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Release Monolithic Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswu\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswu\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Release Multilib DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_dll"
# PROP Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "WXUSINGDLL" /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_dll\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_dll" /libpath:"..\lib\vc_dll" /implib:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_dll\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 DLL Release Multilib Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswu\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswu\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_dll\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "WXUSINGDLL" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Debug Monolithic DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Debug Monolithic Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswud\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswud\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Debug Multilib DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswud_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXDEBUG__" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswud" /i "$(WXWIN)\include" /i "..\include" /d "_DEBUG" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29ud_core.lib wxbase29ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib" /debug /pdb:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Debug Multilib Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswud\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswud\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MDd /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswud" /I "$(WXWIN)\include" /Od /Gm /W4 /I "..\include" /Zi /Fd..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXDEBUG__" /D "__WXMSW__" /D "_DEBUG" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29ud_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Release Monolithic DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Release Monolithic Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswu\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswu\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Release Multilib DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswu_dll\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_UNICODE" /D "__WXMSW__" /D "WXMAKINGDLL_WXSQLITE3" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
# ADD RSC /l 0x409 /d "_UNICODE" /d "__WXMSW__" /i "$(WXWIN)\lib\vc_lib\mswu" /i "$(WXWIN)\include" /i "..\include" /d "WXMAKINGDLL_WXSQLITE3" /d wxUSE_DYNAMIC_SQLITE3_LOAD=0 /d WXSQLITE3_HAVE_METADATA=0 /d WXSQLITE3_HAVE_CODEC=0 /d WXSQLITE3_HAVE_LOAD_EXTENSION=0 /i ..\sqlite3\include
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sqlite3.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"
# ADD LINK32 sqlite3.lib wxmsw29u_core.lib wxbase29u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib /nologo /dll /machine:i386 /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.dll" /libpath:"$(WXWIN)\lib\vc_lib" /libpath:"..\lib\vc_lib" /implib:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib" /pdb:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb" /libpath:"..\sqlite3\lib"

!ELSEIF  "$(CFG)" == "wxsqlite3 - Win32 Static Release Multilib Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vcmswu\wxsqlite3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\vc_lib"
# PROP Intermediate_Dir "vcmswu\wxsqlite3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD CPP /nologo /FD /MD /GR /EHsc /I "$(WXWIN)\lib\vc_lib\mswu" /I "$(WXWIN)\include" /O2 /W4 /I "..\include" /Fd..\lib\vc_lib\wxcode_msw29u_wxsqlite3.pdb /I "..\sqlite3\include" /D "WIN32" /D "_LIB" /D "_UNICODE" /D "__WXMSW__" /D wxUSE_DYNAMIC_SQLITE3_LOAD=0 /D WXSQLITE3_HAVE_METADATA=0 /D WXSQLITE3_HAVE_CODEC=0 /D WXSQLITE3_HAVE_LOAD_EXTENSION=0 /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"
# ADD LIB32 /nologo /out:"..\lib\vc_lib\wxcode_msw29u_wxsqlite3.lib"

!ENDIF

# Begin Target

# Name "wxsqlite3 - Win32 DLL Debug Monolithic DLL"
# Name "wxsqlite3 - Win32 DLL Debug Monolithic Static"
# Name "wxsqlite3 - Win32 DLL Debug Multilib DLL"
# Name "wxsqlite3 - Win32 DLL Debug Multilib Static"
# Name "wxsqlite3 - Win32 DLL Release Monolithic DLL"
# Name "wxsqlite3 - Win32 DLL Release Monolithic Static"
# Name "wxsqlite3 - Win32 DLL Release Multilib DLL"
# Name "wxsqlite3 - Win32 DLL Release Multilib Static"
# Name "wxsqlite3 - Win32 Static Debug Monolithic DLL"
# Name "wxsqlite3 - Win32 Static Debug Monolithic Static"
# Name "wxsqlite3 - Win32 Static Debug Multilib DLL"
# Name "wxsqlite3 - Win32 Static Debug Multilib Static"
# Name "wxsqlite3 - Win32 Static Release Monolithic DLL"
# Name "wxsqlite3 - Win32 Static Release Monolithic Static"
# Name "wxsqlite3 - Win32 Static Release Multilib DLL"
# Name "wxsqlite3 - Win32 Static Release Multilib Static"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\wxsqlite3.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\wx\wxsqlite3.h
# End Source File
# Begin Source File

SOURCE=..\include\wx\wxsqlite3def.h
# End Source File
# Begin Source File

SOURCE=..\include\wx\wxsqlite3dyn.h
# End Source File
# Begin Source File

SOURCE=..\include\wx\wxsqlite3opt.h
# End Source File
# End Group
# End Target
# End Project

