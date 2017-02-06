if "%~1" == "" goto error

OgreMeshTool -v1 -V 1.8 "%~1"

goto end



:error
echo("usage: drag a source.mesh.xml file onto this batch file")
pause

:end