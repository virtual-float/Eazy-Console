@echo off
setlocal EnableExtensions EnableDelayedExpansion
REM ---------------------------------------------------------
REM - an easy script to make g++ compiler at least bearable -
REM -               By naticzka                             - 
REM ---------------------------------------------------------


REM the version of C++
SET cver=23

REM add here g++ paremeters:
SET gpar=-Wall

REM your compiler
set compiler=g++


REM -------------
REM -    CODE   -
REM -------------

REM vars for better readability :3
SET fullcver=-std=c++%cver%

SET incBINDIR=%cd%\bin\inc
SET objBINDIR=%cd%\bin\obj
SET srcBINDIR=%cd%\bin\src

SET mainfile=%cd%\src\main.cpp
SET outputmainfile=%cd%\src\main.o
SET finalexe=%cd%\main.exe

SET alloutputfiles=%outputmainfile%

REM bin
for %%f in (%srcBINDIR%\*.cpp) do (
    SET "file=%%f"
    SET "outputfile=!file:.cpp=.o!"
    SET "outputfile=!outputfile:%srcBINDIR%=%objBINDIR%!"
    echo !outputfile!
    echo compiling !file! ...
    %compiler% -c !file! %gpar% %fullcver% -I%incBINDIR% -o !outputfile!
    if !errorlevel! neq 0 exit /b !errorlevel!
    SET alloutputfiles=%alloutputfiles% !outputfile!
    echo compiling !file! is done
)

REM compile main file
echo compiling the main file (%mainfile%)...
%compiler% -c %mainfile% %gpar% %fullcver% -I%incBINDIR% -o %outputmainfile%
if !errorlevel! neq 0 exit /b !errorlevel!
echo compiling the main file (%mainfile%) is done

REM link them
echo producing the .exe file (%finalexe%)...
%compiler% %alloutputfiles% %gpar% %fullcver% -o %finalexe%
echo the final .exe file (%finalexe%) has been produced

REM running
echo.
echo Do you want to run this exe?
SET /p choice=Y/N:
if %choice%==Y GOTO :run
if %choice%==y GOTO :run
if %choice%==yes GOTO :run
if %choice%==YES GOTO :run
if %choice%==T GOTO :run
if %choice%==t GOTO :run
GOTO :END

:run
echo starting...
echo.
echo.
echo ----------------------------
call %finalexe%


:END