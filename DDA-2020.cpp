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
#include "Tests.h"

#include <chrono>
int _tmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "Russian");
	auto now = chrono::steady_clock::now();
	//Tests::TestProgramm();
	Log::LOG log;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::LOG(parm.log);
		log.WriteLine("Тест: ", "без ошибок", "");
		log.WriteLog();
		log.WriteParm(parm);

		In::IN in = In::getin(parm.in);

		ofstream out(parm.out);
		out << in.text;
		out.close();

		IT::IdTable ID(in.lexems);
		LT::LexTable LT(in.lexems);

		LT.LexAnalysis(parm.out, ID);		

		log.WriteLexTable(LT);
		log.WriteIdTable(ID);

		MFST_TRACE_START
			MFST::Mfst mfst(LT, GRB::getGreibach());

		mfst.start();
		mfst.savededucation();
		mfst.printrules();
		
		
	}
	catch (Error::ERROR error)
	{
		log.WriteError(error);
	}
	catch (queue<Error::ERROR>& errors)
	{
		log.WriteErrors(errors);
	}
	cout << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - now).count();
}
	