@echo off
pause
@chcp 1251
cd "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build"
call vcvarsall x86
cd "C:\Users\dimde\OneDrive\Рабочий стол\ЯП\Курсовой\DDA-2020\DDA-2020"
ml /c out.asm
link /OPT:NOREF out.obj /DYNAMICBASE "C:\Users\dimde\OneDrive\Рабочий стол\ЯП\Курсовой\DDA-2020\Release\StandartLibrary.lib" /SUBSYSTEM:console /out:"C:\Users\dimde\OneDrive\Рабочий стол\ЯП\Курсовой\DDA-2020\Приложение\out.exe"
cls
"C:\Users\dimde\OneDrive\Рабочий стол\ЯП\Курсовой\DDA-2020\Приложение\out.exe"
pause