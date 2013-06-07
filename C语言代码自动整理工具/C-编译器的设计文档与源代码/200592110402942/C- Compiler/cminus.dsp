# Microsoft Developer Studio Project File - Name="cminus" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=cminus - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cminus.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cminus.mak" CFG="cminus - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cminus - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cminus - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cminus - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /nodefaultlib:"library" /out:"../bin/C- Compiler.exe" /libpath:"../Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "cminus - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"library" /out:"../bin/C- Compiler - debug version.exe" /pdbtype:sept /libpath:"../Lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "cminus - Win32 Release"
# Name "cminus - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Analyzer.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmCodeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmCodeView.cpp
# End Source File
# Begin Source File

SOURCE=.\AsmGrammar.cpp
# End Source File
# Begin Source File

SOURCE=.\CGrammar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\cminus.cpp
# End Source File
# Begin Source File

SOURCE=.\cminus.rc
# End Source File
# Begin Source File

SOURCE=.\cminusDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\cminusView.cpp
# End Source File
# Begin Source File

SOURCE=.\FunArgsCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuWndHook.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputBar.cpp
# End Source File
# Begin Source File

SOURCE=.\parser.cpp
# End Source File
# Begin Source File

SOURCE=.\PCodeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\PCodeGrammar.cpp
# End Source File
# Begin Source File

SOURCE=.\PCodeView.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\scaner.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SymbolTable.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TextView.cpp
# End Source File
# Begin Source File

SOURCE=.\tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\XPButton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Analyzer.h
# End Source File
# Begin Source File

SOURCE=.\AsmCodeDoc.h
# End Source File
# Begin Source File

SOURCE=.\AsmCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\AsmCodeView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\cminus.h
# End Source File
# Begin Source File

SOURCE=.\cminusDoc.h
# End Source File
# Begin Source File

SOURCE=.\cminusView.h
# End Source File
# Begin Source File

SOURCE=.\FunArgsCheck.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MenuWndHook.h
# End Source File
# Begin Source File

SOURCE=.\OutputBar.h
# End Source File
# Begin Source File

SOURCE=.\parser.h
# End Source File
# Begin Source File

SOURCE=.\PCodeDoc.h
# End Source File
# Begin Source File

SOURCE=.\PCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\PCodeView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RichEdit.h
# End Source File
# Begin Source File

SOURCE=.\scaner.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SymbolTable.h
# End Source File
# Begin Source File

SOURCE=.\TextDoc.h
# End Source File
# Begin Source File

SOURCE=.\TextView.h
# End Source File
# Begin Source File

SOURCE=.\tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\XPButton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cminus.ico
# End Source File
# Begin Source File

SOURCE=.\res\cminus.rc2
# End Source File
# Begin Source File

SOURCE=.\res\cminusDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_text.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Crystal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Crystal\CCrystalEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalEditView.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalEditView.inl
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextBuffer.inl
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView.inl
# End Source File
# Begin Source File

SOURCE=.\Crystal\CCrystalTextView2.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CEDEFS.H
# End Source File
# Begin Source File

SOURCE=.\Crystal\CEditReplaceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CEditReplaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\CFindTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Crystal\CFindTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\Crystal\EDITCMD.H
# End Source File
# Begin Source File

SOURCE=.\Crystal\EDITREG.H
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
