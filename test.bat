@echo off
@chcp 1251

cd "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build"
call vcvarsall x86

cd "C:\Users\dimde\OneDrive\������� ����\��\��������\DDA-2020\DDA-2020"
ml /c a.asm
pause
link /OPT:NOREF a.obj /DYNAMICBASE "C:\Users\dimde\OneDrive\������� ����\��\��������\DDA-2020\Debug\StandartLibrary.lib" /SUBSYSTEM:console /out:"C:\Users\dimde\OneDrive\������� ����\��\��������\DDA-2020\Debug\a.exe"
pause
cls
"C:\Users\dimde\OneDrive\������� ����\��\��������\DDA-2020\Debug\a.exe"

pause
