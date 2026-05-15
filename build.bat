@echo off

if "%1"=="--reconfig" (
    rmdir /s /q build 
)

if not exist build (
    cmake -B build -G "MinGW Makefiles"
)

cmake --build build --parallel 4

if %errorlevel% neq 0 (
    echo Build Failed. :(
    exit /b 1
)

.\bin\green_eng.exe
