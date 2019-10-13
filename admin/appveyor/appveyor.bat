set MSBUILD_LOGGER=/logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"
goto %TOOLSET%

:msbuild
cd build
msbuild /m:2 /v:n /p:Platform=%ARCH% /p:Configuration="%CONFIGURATION%" wxsqlite3_vc15.sln %MSBUILD_LOGGER%
goto :eof

:cmake
echo --- Tools versions:
cmake --version

if "%SHARED%"=="" set SHARED=ON
if "%CONFIGURATION%"=="" set CONFIGURATION=Release
echo.%GENERATOR% | findstr /C:"Visual Studio">nul && (
    set CMAKE_LOGGER=%MSBUILD_LOGGER%
)

echo.
echo --- Generating project files
echo.
mkdir build_cmake
pushd build_cmake
cmake -G "%GENERATOR%" -DwxBUILD_TESTS=%BUILD_TESTS% -DwxBUILD_SAMPLES=SOME -DCMAKE_INSTALL_PREFIX=%WX_INSTALL_PATH% -DwxBUILD_SHARED=%SHARED% %CMAKE_CONFIGURE_FLAGS% ..
if ERRORLEVEL 1 goto error
echo.
echo --- Starting the build
echo.
cmake --build . --config %CONFIGURATION% -- %CMAKE_NATIVE_FLAGS% %CMAKE_LOGGER%
if ERRORLEVEL 1 goto error

popd

goto :eof

:error
echo.
echo --- Build failed !
echo.
