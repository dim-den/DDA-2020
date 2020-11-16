#include <iostream>
#include <cwchar>
#include <locale>
#include <fstream>
#include <iomanip>
#include <vector>
#include "tchar.h"
using namespace std;

#include "Error.h"
#include "Parm.h"
#include "In.h"	
#include "Log.h"	
#include "FST.h"
#include "MFST.h"
#include "GRB.h"
#include "Semantic.h"
#include "Tests.h"

#include <chrono>
int _tmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "Russian");
	auto start = chrono::steady_clock::now();
	//std::ios::sync_with_stdio(false);
	//Tests::TestProgramm();
	Log::LOG log;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::LOG(parm);
		log.WriteLine("Тест: ", "без ошибок", "");
		log.WriteLog();
		log.WriteParm(parm);

		In::IN in = In::getin(parm.in);

		ofstream out(parm.out);
		out << in.text;
		out.close();

		IT::IdTable IT(in.lexems);
		LT::LexTable LT(in.lexems);

		LT.LexAnalysis(parm.out, IT);

		log.WriteLexTable(LT);
		log.WriteIdTable(IT);

		MFST::Mfst mfst(LT, GRB::getGreibach(), parm.debug);

		mfst.start();
		mfst.savededucation();
		mfst.printrules();

		SEM::Semantic semantic(LT, IT);
		semantic.Analysis();

		cout << "-------------------------------------------------------------------------------\n";
		cout << "Программа завершена успешно!" << endl;
		cout << "Время выполнения: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() << "мс\n";
		return 1;
	}
	catch (Error::ERROR error)
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
	