echo.
echo --- Running tests.
echo.

cd c:\projects\wxsqlite3

goto %TOOLSET%

:msbuild
PATH=%WXWIN%\lib\vc14x_x64_dll;%PATH%
".\build\bin\vc15\%ARCH%\%CONFIGURATION%\minimal.exe" -t -s .\samples
goto :eof

:error
echo.
echo !!! Test failed.
echo.
goto :eof
