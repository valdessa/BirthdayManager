@echo off
cls
echo ----------------------------------------
echo  Searching for Developer Command Prompt...
echo ----------------------------------------

REM Try to locate Visual Studio with C++ tools
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set VS_PATH=%%i

if defined VS_PATH (
    color 0A
    echo Developer Command Prompt found:
    echo    %VS_PATH%
    echo.
    echo Setting up environment...
    
    REM Call Developer Command Prompt
    call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x86

    cls
    echo ---------------------------------------------------
    echo  Compilation process started
    echo ---------------------------------------------------

    if not exist ..\bin\debug mkdir ..\bin\debug

    cl /nologo /Zi /EHs /MDd /c ../src/ADT/adt_memory_node.c -I ../include -I ../include/ADT -I ../deps/edk_memory_manager/include
    cl /nologo /Zi /EHs /MDd /c ../src/ADT/adt_vector.c -I ../include -I ../include/ADT -I ../deps/edk_memory_manager/include
    cl /nologo /Zi /EHs /MDd /W4 /D_CRT_SECURE_NO_WARNINGS -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui -I ..\deps\imgui\backends /c ..\deps\imgui\backends\imgui_impl_sdl.cpp
    cl /nologo /Zi /EHs /MDd /W4 /D_CRT_SECURE_NO_WARNINGS -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui -I ..\deps\imgui\backends /c ..\deps\imgui\backends\imgui_impl_sdlrenderer.cpp
    cl /nologo /Zi /EHs /MDd /W4 /D_CRT_SECURE_NO_WARNINGS -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui -I ..\deps\imgui\backends /c ..\deps\imgui\imgui*.cpp
    cl /nologo /Zi /EHs /MDd /W4 /D_CRT_SECURE_NO_WARNINGS -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui -I ..\deps\imgui\backends -I ..\deps\edk_memory_manager\include /c ..\src\*.cc
    cl /nologo /Zi /EHs /MDd /W4 /Fe:..\bin\debug\main.exe ..\tools\*.obj /link /SUBSYSTEM:CONSOLE ..\deps\sdl2\lib\x86\SDL2.lib ..\deps\edk_memory_manager\lib\EDK_MemoryManager\x32\EDK_MemoryManager_Windows_d.lib ..\deps\sdl2\lib\x86\SDL2main.lib ..\deps\sdl2\lib\x86\sqlite3.lib ..\deps\sdl2\lib\x86\SDL2_image.lib ..\deps\sdl2\lib\x86\SDL2_ttf.lib ..\deps\sdl2\lib\x86\SDL2_mixer.lib opengl32.lib shell32.lib user32.lib gdi32.lib

    echo ---------------------------------------------------
    echo  COPYING DLLs
    echo ---------------------------------------------------

    xcopy /D /Y /Q "..\deps\dlls\*" "..\bin\debug\"

    del *.obj *.pdb *.ilk *.exe 
    echo ---------------------------------------------------
    echo  PROGRAM COMPILED IN DEBUG
    echo ---------------------------------------------------
) else (
    color 0C
    echo Developer Command Prompt not found.
    echo Make sure you have Visual Studio with C++ tools installed.
)

echo.
pause
color 07
