#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "Parm.h"
#include <fstream>
#include <iomanip>
#include <queue>
#include <iostream>
#include <ctime>

#define TIME_LOG_SIZE 100

namespace Log
{
	class LOG {
	public:
		LOG(); 
		LOG(Parm::PARM& parm);
		void WriteLine(const char* c, ...);
		void WriteLine(const wchar_t* c, ...);
		void WriteLog(); // вывести в протокол заголовок
		void WriteParm(const Parm::PARM& parm); // вывести информацию о входных параметрах
		void WriteIn(const In::IN& in); // вывести информацию о входном потоке
		void WriteError(const Error::ERROR& error); // вывести информацию об ошибке
		void WriteLexTable(LT::LexTable& lextable);
		void WriteIdTable(IT::IdTable& idtable);
		void WriteErrors(std::queue<Error::ERROR>& errors);
		LOG& operator=(Log::LOG&& rhs) noexcept;
		~LOG();
	private:
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
		bool debug_mode = false;
	};
}
