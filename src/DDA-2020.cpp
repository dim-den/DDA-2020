#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cwchar>
#include <locale>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <sstream>
#include "tchar.h"
using namespace std;
using namespace std::chrono;

bool DEBUG_MODE = false;

#include "Error.h"
#include "Parm.h"
#include "In.h"	
#include "Log.h"	
#include "FST.h"
#include "MFST.h"
#include "GRB.h"
#include "Semantic.h"
#include "Generation.h"
//#include "BAT.h"


int _tmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "Russian");
	auto program_start = chrono::steady_clock::now();
	std::ios::sync_with_stdio(false);
	using time = std::chrono::steady_clock;

	Log::LOG log;
	try
	{
		Parm::PARM parm = Parm::GetParm::parm(argc, argv);
		log = Log::LOG(parm);
		log.WriteLog();
		log.WriteParm(parm);
		In::IN in = In::getin(parm.in);

		IT::IdTable IT(in.lexems);
		LT::LexTable LT(in.lexems);

		auto start = time::now();
		LT.LexAnalysis(in.text, IT);
		auto lex_time = duration_cast<milliseconds>(time::now() - start).count();

		log.WriteLexTable(LT);
		log.WriteIdTable(IT);

		start = time::now();
		MFST::Mfst mfst(LT, GRB::getGreibach());
		mfst.start();

		mfst.savededucation();
		mfst.printrules();

		auto synt_time = duration_cast<milliseconds>(time::now() - start).count();

		start = time::now();
		SEM::Semantic semantic(LT, IT);
		semantic.Analysis();
		auto sem_time = duration_cast<milliseconds>(time::now() - start).count();

		LT.BuildPolish(IT, semantic.GetExprPos());

		start = time::now();
		Gen::Generator generator(LT, IT, parm.out);
		generator.Generate();
		auto gen_time = duration_cast<milliseconds>(time::now() - start).count();

		cout << "\n-------------------------------------------------------------------------------\n";
		cout << "Генерация завершена успешно!" << endl;
		log.WriteResultTime(lex_time, synt_time, sem_time, gen_time, duration_cast<milliseconds>(steady_clock::now() - program_start).count());

		//BAT::Generate(parm);
		//system("call \"C:\\Users\\dimde\\OneDrive\\Рабочий стол\\ЯП\\Курсовой\\DDA-2020\\DDA-2020\\compile.bat\"");
		return 1;
	}
	catch (Error::ERROR& error)
	{
		log.WriteError(error);
	}
	catch (queue<Error::ERROR>& errors)
	{
		log.WriteErrors(errors);
	}
	cout << "\n-------------------------------------------------------------------------------" << endl;
	cout << "Ошибка... Выход из программы" << endl;
	return 0;
}