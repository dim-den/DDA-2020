#pragma once
#include <iostream>
#include <fstream>
#include "Parm.h"

static class BAT
{
public:
	static void Generate(const Parm::PARM& parm)
	{
		std::ofstream bat("..\\DDA-2020\\compile.bat");

		string out_name;
		for (int i = 0; i < PARM_MAX_SIZE;i++)
			if (parm.out[i] == '.' && parm.out[i + 1] == 'a' && parm.out[i + 2] == 's' && parm.out[i + 3] == 'm') break;
			else out_name += parm.out[i];

		bat << "@echo off\n";
		bat << "pause\n";
		bat << "@chcp 1251\n";
		bat << "cd \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\"" << endl;
		bat << "call vcvarsall x86" << endl;

		bat << "cd \"C:\\Users\\dimde\\OneDrive\\Рабочий стол\\ЯП\\Курсовой\\DDA-2020\\DDA-2020\"" << endl;
		bat << "ml /c " << out_name << ".asm" << endl;
		bat << "link /OPT:NOREF " << out_name << ".obj /DYNAMICBASE \"C:\\Users\\dimde\\OneDrive\\Рабочий стол\\ЯП\\Курсовой\\DDA-2020\\Release\\StandartLibrary.lib\" /SUBSYSTEM:console /out:\"C:\\Users\\dimde\\OneDrive\\Рабочий стол\\ЯП\\Курсовой\\DDA-2020\\Приложение\\" << out_name << ".exe\"" << endl;
		
		bat << "cls\n";
		bat << "\"C:\\Users\\dimde\\OneDrive\\Рабочий стол\\ЯП\\Курсовой\\DDA-2020\\Приложение\\" << out_name << ".exe\"" << endl;
		bat << "pause";

	}
};