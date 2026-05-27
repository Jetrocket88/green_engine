@echo off

if "%1"=="--reconfig" (
    echo "Cleaning..."
    rmdir /s /q build 
)

if not exist build (
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build -G "MinGW Makefiles"
    cp build/compile_commands.json compile_commands.json
)

cmake --build build --parallel 4

if %errorlevel% neq 0 (
    echo Build Failed. :(
    exit /b 1
)

.\bin\green_eng.exe
