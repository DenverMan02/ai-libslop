@echo off
setlocal
cd /d "%~dp0"

echo === Chairlib: Release ARM64 (CLEAN REBUILD) ===
where msbuild >nul 2>nul
if errorlevel 1 (
  echo ERROR: msbuild was not found in PATH.
  echo Open a Visual Studio 2022 Developer Command Prompt and run this again.
  exit /b 1
)

msbuild PvZ2.vcxproj /t:Rebuild /p:Configuration=Release /p:Platform=ARM64 /m
if errorlevel 1 (
  echo.
  echo BUILD FAILED.
  exit /b 1
)

echo.
echo BUILD SUCCEEDED.
echo Look for libChair.so in the project's ARM64 Release output.
exit /b 0
