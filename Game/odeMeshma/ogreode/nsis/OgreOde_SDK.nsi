;--------------------------------

!define BASE_NAME "OgreOde"
!define PKG_NAME "SDK"
!define VERSION "v1_3_0"
!define PKG_EXE "Install_${BASE_NAME}_${PKG_NAME}_${VERSION}_setup.exe"
!define PKG_SUBMENU "Ogre SDK\${BASE_NAME}\${PKG_NAME}"
!define PKG_FOLDER "${BASE_NAME}\${PKG_NAME}"

;--------------------------------
SetCompress off
SetCompressor /SOLID lzma
CRCCheck on

XPStyle on
SetDateSave on
SilentInstall normal

;--------------------------------
Var OGRE_HOME
Var PKG_BINDIR

;-------------------------------
;Include Modern UI
!include "MUI.nsh"


;--------------------------------
Name "${BASE_NAME} {PKG_NAME}"
OutFile "${PKG_EXE}"
InstallDirRegKey HKLM "Software\Ogre\${BASE_NAME}\${PKG_NAME}" "Install_Dir"



;----------------
;Modern UI Configuration

  ;;!define MUI_FINISHPAGE_RUN "$INSTDIR\${GAME_NAME}.bat"
  !define MUI_FINISHPAGE_NOREBOOTSUPPORT 1

  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU"
  !define MUI_LANGDLL_REGISTRY_KEY "Software\Ogre\${BASE_NAME}\${PKG_NAME}"
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP ".\${BASE_NAME}_header.png"

  !define MUI_WELCOMEFINISHPAGE_BITMAP ".\${BASE_NAME}_left.png"

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "Ogre\${BASE_NAME}\${PKG_NAME}"
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ogre\${BASE_NAME}\${PKG_NAME}"
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  !define MUI_STARTMENUPAGE_VARIABLE "$R9"

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  ;!insertmacro MUI_PAGE_STARTMENU
  !insertmacro MUI_PAGE_LICENSE "license.txt"
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_DIRECTORY
  !insertmacro MUI_UNPAGE_COMPONENTS
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "French"
 	;!insertmacro MUI_LANGUAGE "German"
 	;!insertmacro MUI_LANGUAGE "Spanish"
	;!insertmacro MUI_LANGUAGE "SimpChinese"
	;!insertmacro MUI_LANGUAGE "TradChinese"
  ;!insertmacro MUI_LANGUAGE "Japanese"
  ;!insertmacro MUI_LANGUAGE "Korean"
  ;!insertmacro MUI_LANGUAGE "Italian"
  ;!insertmacro MUI_LANGUAGE "Dutch"
  ;!insertmacro MUI_LANGUAGE "Danish"
	;!insertmacro MUI_LANGUAGE "Swedish"
	;!insertmacro MUI_LANGUAGE "Greek"
	;!insertmacro MUI_LANGUAGE "Russian"
	;!insertmacro MUI_LANGUAGE "Portuguese"
	;!insertmacro MUI_LANGUAGE "PortugueseBR"
	;!insertmacro MUI_LANGUAGE "Polish"
	;!insertmacro MUI_LANGUAGE "Ukrainian"
	;!insertmacro MUI_LANGUAGE "Czech"
	;!insertmacro MUI_LANGUAGE "Slovak"
	;!insertmacro MUI_LANGUAGE "Croatian"
	;!insertmacro MUI_LANGUAGE "Bulgarian"
	;!insertmacro MUI_LANGUAGE "Hungarian"
	;!insertmacro MUI_LANGUAGE "Thai"
  ;!insertmacro MUI_LANGUAGE "Romanian"
  ;!insertmacro MUI_LANGUAGE "Macedonian"
	;!insertmacro MUI_LANGUAGE "Estonian"
	;!insertmacro MUI_LANGUAGE "Turkish"
	;!insertmacro MUI_LANGUAGE "Lithuanian"
	;!insertmacro MUI_LANGUAGE "Catalan"
	;!insertmacro MUI_LANGUAGE "Serbian"

;--------------------------------
;Reserve Files

  ;Things that need to be extracted on first (keep these lines before any File command!)
  ;Only for BZIP2 compression
  !insertmacro MUI_RESERVEFILE_LANGDLL
;--------------------------------
;Language Strings

  ;Description

  ;Header
  LangString TEXT_IO_SUBTITLE ${LANG_ENGLISH} "Please review the license terms before installing ${MUI_PRODUCT}"
  LangString TEXT_IO_SUBTITLE ${LANG_FRENCH} "Pri�re de lire la license avant l'installation ${MUI_PRODUCT}"

;--------------------------------
;Data


  LicenseData "license.txt"

;--------------------------------
Function .onInit
    ReadEnvStr $OGRE_HOME OGRE_HOME

    StrCpy $INSTDIR "$OGRE_HOME\..\${PKG_FOLDER}"
    StrCpy $PKG_BINDIR "$OGRE_HOME\bin\Release"

    # the plugins dir is automatically deleted when the installer exits
    InitPluginsDir
    #optional
    #File /oname=$PLUGINSDIR\splash.wav "C:\myprog\sound.wav"
    File /oname=$PLUGINSDIR\splash.png "${BASE_NAME}_splash.png"
    advsplash::show 1000 600 400 0x00005B $PLUGINSDIR\splash
    Pop $0

    Delete $PLUGINSDIR\splash.png
    !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd


Section "${BASE_NAME} ${PKG_NAME} (required)"

  SectionIn RO

   SetOutPath $INSTDIR

  File /r /x *.sbr /x *.bsc /x *.pch /x *.exp /x *.lib /x BuildLog.htm /x nsis /x *.exe /x *.svn /x CVS /x *.res /x *.user /x *.obj /x *.ncb  /x *.bat /x *.idb /x *.pdb /x *.ilk /x *.dep /x *.dll /x *.manifest "..\*.*"

  WriteRegStr HKLM "SOFTWARE\${PKG_SUBMENU}" "Install_Dir" "$INSTDIR"

  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${BASE_NAME}\${PKG_NAME}" "DisplayName" "${BASE_NAME} ${PKG_NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${BASE_NAME}\${PKG_NAME}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${BASE_NAME}\${PKG_NAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${BASE_NAME}\${PKG_NAME}" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

SectionEnd

Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\${PKG_SUBMENU}"

  SetOutPath $PKG_BINDIR

  CreateShortCut  "$SMPROGRAMS\${PKG_SUBMENU}\${BASE_NAME} Simple Scenes.lnk" "$PKG_BINDIR\Demo_SimpleScenes.exe" "" "$PKG_BINDIR\Demo_SimpleScenes.exe" 0
  CreateShortCut  "$SMPROGRAMS\${PKG_SUBMENU}\${BASE_NAME} Gran Turism Ogre.lnk" "$PKG_BINDIR\Demo_GranTurismOgre.exe" "" "$PKG_BINDIR\Demo_GranTurismOgre.exe" 0
  CreateShortCut  "$SMPROGRAMS\${PKG_SUBMENU}\${BASE_NAME} Landscape.lnk" "$PKG_BINDIR\Demo_Landscape.exe" "" "$PKG_BINDIR\Demo_Landscape.exe" 0

  SetOutPath $OUTDIR

  CreateShortCut  "$SMPROGRAMS\${PKG_SUBMENU}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0

SectionEnd

Section "Uninstall"

  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${BASE_NAME}\${PKG_NAME}"
  DeleteRegKey HKLM SOFTWARE\Ogre\${BASE_NAME}

  RMDir /r "$SMPROGRAMS\${PKG_SUBMENU}\"

  Delete "$PKG_BINDIR\${BASE_NAME}*.*"

  RMDir /r "$INSTDIR"

SectionEnd