@echo off
rem adjust path to engine
Set "AckPath=d:\acknex8" 

Set "path=%path%;%AckPath%" 

echo Create Resources and Executable...

rem options.scr does not allow to ignore certain folders so provoke 
rem file not found for everything in "media" with folder renaming

ren media media_renamed_by_buildscript
timeout /t 1 /nobreak > NUL
wed -r galep.c
rem wed -p galep.c
ren media_renamed_by_buildscript media

echo.
echo Copy unresourced files...
xcopy /y media\*.* galep.cd\media\
xcopy /y publish\*.* galep.cd\
copy level.dat galep.cd
del galep.exe

echo.
echo Finished.
echo.

pause