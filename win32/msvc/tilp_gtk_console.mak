# Microsoft Developer Studio Generated NMAKE File, Based on tilp_gtk_console.dsp
!IF "$(CFG)" == ""
CFG=tilp_gtk_console - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tilp_gtk_console - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tilp_gtk_console - Win32 Release" && "$(CFG)" != "tilp_gtk_console - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tilp_gtk_console.mak" CFG="tilp_gtk_console - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tilp_gtk_console - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "tilp_gtk_console - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "tilp_gtk_console - Win32 Release"

OUTDIR=.
INTDIR=C:\msvc\Output\tilp_gtk
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tilp.exe"

!ELSE 

ALL : "tifiles - Win32 Release" "ticalcs - Win32 Release" "ticables - Win32 Release" "$(OUTDIR)\tilp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 ReleaseCLEAN" "ticalcs - Win32 ReleaseCLEAN" "tifiles - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\action.obj"
	-@erase "$(INTDIR)\clist.obj"
	-@erase "$(INTDIR)\clock.obj"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\ctree.obj"
	-@erase "$(INTDIR)\dboxes.obj"
	-@erase "$(INTDIR)\extprgms.obj"
	-@erase "$(INTDIR)\filesel.obj"
	-@erase "$(INTDIR)\general.obj"
	-@erase "$(INTDIR)\gtk_refresh.obj"
	-@erase "$(INTDIR)\labels.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\manpage.obj"
	-@erase "$(INTDIR)\pbars.obj"
	-@erase "$(INTDIR)\pbars_db.obj"
	-@erase "$(INTDIR)\popup.obj"
	-@erase "$(INTDIR)\release.obj"
	-@erase "$(INTDIR)\screenshot.obj"
	-@erase "$(INTDIR)\scroptions.obj"
	-@erase "$(INTDIR)\shell.obj"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\support.obj"
	-@erase "$(INTDIR)\tilp.obj"
	-@erase "$(INTDIR)\tilp.res"
	-@erase "$(INTDIR)\tilp_calcs.obj"
	-@erase "$(INTDIR)\tilp_error.obj"
	-@erase "$(INTDIR)\tilp_files.obj"
	-@erase "$(INTDIR)\tilp_indep.obj"
	-@erase "$(INTDIR)\tilp_main.obj"
	-@erase "$(INTDIR)\tilp_misc.obj"
	-@erase "$(INTDIR)\tilp_paths.obj"
	-@erase "$(INTDIR)\tilp_plugin.obj"
	-@erase "$(INTDIR)\tilp_prompt.obj"
	-@erase "$(INTDIR)\tilp_rcfile.obj"
	-@erase "$(INTDIR)\tilp_refresh.obj"
	-@erase "$(INTDIR)\tilp_screen.obj"
	-@erase "$(INTDIR)\tilp_slct.obj"
	-@erase "$(INTDIR)\tilp_vars.obj"
	-@erase "$(INTDIR)\toolbar.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wizard.obj"
	-@erase "$(OUTDIR)\tilp.exe"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G3 /ML /w /W0 /GX /O2 /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../../libs/files/src/" /I "../dep/win32/" /I "../../../" /D "NDEBUG" /D "_CONSOLE" /D "__WIN32__" /D "_MBCS" /D "WIN32" /D "HAVE_LIBINTL_H" /D "ENABLE_NLS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\tilp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tilp_gtk_console.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gnu-intl.lib gmodule-1.3.lib glib-1.3.lib gdk-1.3.lib gtk-1.3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\tilp.pdb" /machine:I386 /out:"$(OUTDIR)\tilp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\action.obj" \
	"$(INTDIR)\clist.obj" \
	"$(INTDIR)\clock.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\ctree.obj" \
	"$(INTDIR)\dboxes.obj" \
	"$(INTDIR)\extprgms.obj" \
	"$(INTDIR)\filesel.obj" \
	"$(INTDIR)\general.obj" \
	"$(INTDIR)\gtk_refresh.obj" \
	"$(INTDIR)\labels.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\manpage.obj" \
	"$(INTDIR)\pbars.obj" \
	"$(INTDIR)\pbars_db.obj" \
	"$(INTDIR)\popup.obj" \
	"$(INTDIR)\release.obj" \
	"$(INTDIR)\screenshot.obj" \
	"$(INTDIR)\scroptions.obj" \
	"$(INTDIR)\shell.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\support.obj" \
	"$(INTDIR)\tilp.obj" \
	"$(INTDIR)\toolbar.obj" \
	"$(INTDIR)\wizard.obj" \
	"$(INTDIR)\tilp_calcs.obj" \
	"$(INTDIR)\tilp_error.obj" \
	"$(INTDIR)\tilp_files.obj" \
	"$(INTDIR)\tilp_indep.obj" \
	"$(INTDIR)\tilp_main.obj" \
	"$(INTDIR)\tilp_misc.obj" \
	"$(INTDIR)\tilp_paths.obj" \
	"$(INTDIR)\tilp_plugin.obj" \
	"$(INTDIR)\tilp_prompt.obj" \
	"$(INTDIR)\tilp_rcfile.obj" \
	"$(INTDIR)\tilp_refresh.obj" \
	"$(INTDIR)\tilp_screen.obj" \
	"$(INTDIR)\tilp_slct.obj" \
	"$(INTDIR)\tilp_vars.obj" \
	"$(INTDIR)\tilp.res" \
	"..\..\..\libs\cables\win32\msvc\ticables.lib" \
	"..\..\..\libs\calcs\win32\msvc\ticalcs.lib" \
	"..\..\..\libs\files\win32\msvc\tifiles.lib"

"$(OUTDIR)\tilp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tilp_gtk_console - Win32 Debug"

OUTDIR=C:\msvc\tilp
INTDIR=C:\msvc\Output\tilp_gtk
# Begin Custom Macros
OutDir=C:\msvc\tilp\ 
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tilp.exe"

!ELSE 

ALL : "tifiles - Win32 Debug" "ticalcs - Win32 Debug" "ticables - Win32 Debug" "$(OUTDIR)\tilp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 DebugCLEAN" "ticalcs - Win32 DebugCLEAN" "tifiles - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\action.obj"
	-@erase "$(INTDIR)\clist.obj"
	-@erase "$(INTDIR)\clock.obj"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\ctree.obj"
	-@erase "$(INTDIR)\dboxes.obj"
	-@erase "$(INTDIR)\extprgms.obj"
	-@erase "$(INTDIR)\filesel.obj"
	-@erase "$(INTDIR)\general.obj"
	-@erase "$(INTDIR)\gtk_refresh.obj"
	-@erase "$(INTDIR)\labels.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\manpage.obj"
	-@erase "$(INTDIR)\pbars.obj"
	-@erase "$(INTDIR)\pbars_db.obj"
	-@erase "$(INTDIR)\popup.obj"
	-@erase "$(INTDIR)\release.obj"
	-@erase "$(INTDIR)\screenshot.obj"
	-@erase "$(INTDIR)\scroptions.obj"
	-@erase "$(INTDIR)\shell.obj"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\support.obj"
	-@erase "$(INTDIR)\tilp.obj"
	-@erase "$(INTDIR)\tilp.res"
	-@erase "$(INTDIR)\tilp_calcs.obj"
	-@erase "$(INTDIR)\tilp_error.obj"
	-@erase "$(INTDIR)\tilp_files.obj"
	-@erase "$(INTDIR)\tilp_indep.obj"
	-@erase "$(INTDIR)\tilp_main.obj"
	-@erase "$(INTDIR)\tilp_misc.obj"
	-@erase "$(INTDIR)\tilp_paths.obj"
	-@erase "$(INTDIR)\tilp_plugin.obj"
	-@erase "$(INTDIR)\tilp_prompt.obj"
	-@erase "$(INTDIR)\tilp_rcfile.obj"
	-@erase "$(INTDIR)\tilp_refresh.obj"
	-@erase "$(INTDIR)\tilp_screen.obj"
	-@erase "$(INTDIR)\tilp_slct.obj"
	-@erase "$(INTDIR)\tilp_vars.obj"
	-@erase "$(INTDIR)\toolbar.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wizard.obj"
	-@erase "$(OUTDIR)\tilp.exe"
	-@erase "$(OUTDIR)\tilp.ilk"
	-@erase "$(OUTDIR)\tilp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /w /W0 /Gm /GX /ZI /Od /I "../../../libs/cables/src" /I "../../../libs/files/src" /I "../../../libs/calcs/src" /D "_DEBUG" /D "GTK" /D "_CONSOLE" /D "__WIN32__" /D "_MBCS" /D "WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\tilp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tilp_gtk_console.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib glib-2.0.lib gobject-2.0.lib gdk-win32-2.0.lib gmodule-2.0.lib gdk_pixbuf-2.0.lib atk-1.0.lib gtk-win32-2.0.lib glade-2.0.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\tilp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\tilp.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\action.obj" \
	"$(INTDIR)\clist.obj" \
	"$(INTDIR)\clock.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\ctree.obj" \
	"$(INTDIR)\dboxes.obj" \
	"$(INTDIR)\extprgms.obj" \
	"$(INTDIR)\filesel.obj" \
	"$(INTDIR)\general.obj" \
	"$(INTDIR)\gtk_refresh.obj" \
	"$(INTDIR)\labels.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\manpage.obj" \
	"$(INTDIR)\pbars.obj" \
	"$(INTDIR)\pbars_db.obj" \
	"$(INTDIR)\popup.obj" \
	"$(INTDIR)\release.obj" \
	"$(INTDIR)\screenshot.obj" \
	"$(INTDIR)\scroptions.obj" \
	"$(INTDIR)\shell.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\support.obj" \
	"$(INTDIR)\tilp.obj" \
	"$(INTDIR)\toolbar.obj" \
	"$(INTDIR)\wizard.obj" \
	"$(INTDIR)\tilp_calcs.obj" \
	"$(INTDIR)\tilp_error.obj" \
	"$(INTDIR)\tilp_files.obj" \
	"$(INTDIR)\tilp_indep.obj" \
	"$(INTDIR)\tilp_main.obj" \
	"$(INTDIR)\tilp_misc.obj" \
	"$(INTDIR)\tilp_paths.obj" \
	"$(INTDIR)\tilp_plugin.obj" \
	"$(INTDIR)\tilp_prompt.obj" \
	"$(INTDIR)\tilp_rcfile.obj" \
	"$(INTDIR)\tilp_refresh.obj" \
	"$(INTDIR)\tilp_screen.obj" \
	"$(INTDIR)\tilp_slct.obj" \
	"$(INTDIR)\tilp_vars.obj" \
	"$(INTDIR)\tilp.res" \
	"$(OUTDIR)\ticables.lib" \
	"$(OUTDIR)\ticalcs.lib" \
	"$(OUTDIR)\tifiles.lib"

"$(OUTDIR)\tilp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("tilp_gtk_console.dep")
!INCLUDE "tilp_gtk_console.dep"
!ELSE 
!MESSAGE Warning: cannot find "tilp_gtk_console.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tilp_gtk_console - Win32 Release" || "$(CFG)" == "tilp_gtk_console - Win32 Debug"
SOURCE=..\..\src\about.c

"$(INTDIR)\about.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\action.c

"$(INTDIR)\action.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\clist.c

"$(INTDIR)\clist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\clock.c

"$(INTDIR)\clock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\comm.c

"$(INTDIR)\comm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\ctree.c

"$(INTDIR)\ctree.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\dboxes.c

"$(INTDIR)\dboxes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\extprgms.c

"$(INTDIR)\extprgms.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\filesel.c

"$(INTDIR)\filesel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\general.c

"$(INTDIR)\general.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\gtk_refresh.c

"$(INTDIR)\gtk_refresh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\labels.c

"$(INTDIR)\labels.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\main.c

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\manpage.c

"$(INTDIR)\manpage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pbars.c

"$(INTDIR)\pbars.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pbars_db.c

"$(INTDIR)\pbars_db.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\popup.c

"$(INTDIR)\popup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\release.c

"$(INTDIR)\release.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\screenshot.c

"$(INTDIR)\screenshot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\scroptions.c

"$(INTDIR)\scroptions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\shell.c

"$(INTDIR)\shell.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\splash.c

"$(INTDIR)\splash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\support.c

"$(INTDIR)\support.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp.c

"$(INTDIR)\tilp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\toolbar.c

"$(INTDIR)\toolbar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\wizard.c

"$(INTDIR)\wizard.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\tilp.rc

"$(INTDIR)\tilp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_calcs.c

"$(INTDIR)\tilp_calcs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_error.c

"$(INTDIR)\tilp_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_files.c

"$(INTDIR)\tilp_files.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_indep.c

"$(INTDIR)\tilp_indep.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_main.c

"$(INTDIR)\tilp_main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_misc.c

"$(INTDIR)\tilp_misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_paths.c

"$(INTDIR)\tilp_paths.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_plugin.c

"$(INTDIR)\tilp_plugin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_prompt.c

"$(INTDIR)\tilp_prompt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_rcfile.c

"$(INTDIR)\tilp_rcfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_refresh.c

"$(INTDIR)\tilp_refresh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_screen.c

"$(INTDIR)\tilp_screen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_slct.c

"$(INTDIR)\tilp_slct.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\tilp_vars.c

"$(INTDIR)\tilp_vars.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "tilp_gtk_console - Win32 Release"

"ticables - Win32 Release" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticables - Win32 ReleaseCLEAN" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ELSEIF  "$(CFG)" == "tilp_gtk_console - Win32 Debug"

"ticables - Win32 Debug" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticables - Win32 DebugCLEAN" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ENDIF 

!IF  "$(CFG)" == "tilp_gtk_console - Win32 Release"

"ticalcs - Win32 Release" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticalcs - Win32 ReleaseCLEAN" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ELSEIF  "$(CFG)" == "tilp_gtk_console - Win32 Debug"

"ticalcs - Win32 Debug" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticalcs - Win32 DebugCLEAN" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ENDIF 

!IF  "$(CFG)" == "tilp_gtk_console - Win32 Release"

"tifiles - Win32 Release" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" 
   cd "..\..\..\..\tilp\win32\msvc"

"tifiles - Win32 ReleaseCLEAN" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ELSEIF  "$(CFG)" == "tilp_gtk_console - Win32 Debug"

"tifiles - Win32 Debug" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" 
   cd "..\..\..\..\tilp\win32\msvc"

"tifiles - Win32 DebugCLEAN" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ENDIF 


!ENDIF 

