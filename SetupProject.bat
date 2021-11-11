@echo off

:: Set default post setup behaviour
set POST_SETUP_COMMAND=exit /b 0

if "%SETUP_SILENTLY%"=="" (
    :: Kill background processes
    taskkill /IM "MSBuild.exe" /F 2>nul
    taskkill /IM "ServiceHub.Roslyn.CodeAnalysisService32.exe" /F 2>nul
    taskkill /IM "devenv.exe" /F 2>nul
    taskkill /IM "PerfWatson2.exe" /F 2>nul

    :: Clean up conan locks
    conan remove --locks 1>nul

    :: Open project solution
    set POST_SETUP_COMMAND=cmake --open .
)

:: Set build path
set ROOT_PATH="%~dp0"
set BUILD_PATH="%ROOT_PATH%\build\"

:: Remove previous cmake build
if exist %BUILD_PATH% rmdir %BUILD_PATH% /s /q

:: Create the new one and run the solution
mkdir %BUILD_PATH% && cd %BUILD_PATH% && cmake .. -G "Visual Studio 16 2019" -A x64 -T v141 -DCMAKE_CONFIGURATION_TYPES:STRING=Debug;Release && %POST_SETUP_COMMAND% && exit /b 0

:: Wait user input if something is broken
pause
exit /b 1