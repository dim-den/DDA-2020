#include "Log.h"
#include <cstring>
#pragma warning(disable: 4996)
using namespace std;

namespace Log
{
	LOG::LOG() : logfile(L""), stream(nullptr) {}

	LOG::LOG(wchar_t* logfile) {
		stream = new ofstream(logfile);
		if (!stream->is_open()) throw ERROR_THROW(112);
		wcscpy_s(this->logfile, logfile);
	}

	void LOG::WriteLine(const char* c, ...) {
		int i = 0;
		const char** str = &c;
		while (str[i] != "")
			* stream << str[i++];
		*stream << IN_CODE_ENDL;
	}

	void LOG::WriteLine(const wchar_t* c, ...) {
		int i = 0;
		const wchar_t** str = &c;
		while (str[i] != L"")
			* stream << str[i++];
		*stream << IN_CODE_ENDL;
	}

	LOG& LOG::operator=(Log::LOG&& rhs) noexcept {
		wcscpy_s(logfile, rhs.logfile);
		stream = rhs.stream;
		rhs.stream = nullptr;
		return *this;
	}

	LOG::~LOG() {
		if (stream != nullptr) {
			stream->close();
			delete stream;
		}
	}

	void LOG::WriteLog() { // вывести в протокол заголовок
		tm* timeinfo;
		time_t ttime;
		time(&ttime);
		timeinfo = localtime(&ttime);
		char info[TIME_LOG_SIZE];
		strftime(info, TIME_LOG_SIZE, "\n ------ ПРОТОКОЛ ------\n Дата: %d.%m.%y %T \n", timeinfo);
		*stream << info;
	}

	void LOG::WriteParm(const Parm::PARM& parm) {// вывести информацию о входных параметрах
		char i[PARM_MAX_SIZE], o[PARM_MAX_SIZE], l[PARM_MAX_SIZE];
		wcstombs(i, parm.in, PARM_MAX_SIZE);
		wcstombs(o, parm.out, PARM_MAX_SIZE);
		wcstombs(l, parm.log, PARM_MAX_SIZE);
		*stream << "\n ------ Параметры ------ "
			<< "\n-log: " << l
			<< "\n-out: " << o
			<< "\n-in:  " << i << "\n";
	}

	void LOG::WriteIn(const In::IN& in) { // вывести информацию о входном потоке
		*stream << "\n ------ Исходные данные ------ " <<
			"\nВсего символов: " << in.size <<
			"\nВсего строк: " << in.lines <<
			"\nПропущено: " << in.ignor << "\n";
	}

	void LOG::WriteError(const Error::ERROR& error) { // вывести информацию об ошибке
		if (stream != nullptr) {
			*stream << endl;
			if (100 <= error.id && error.id <= 109)* stream << "PARM.";
			else if(110 <= error.id && error.id <= 119)* stream << "IN.";
			else if(120 <= error.id && error.id <= 139)* stream << "LEX.";
			else if(200 <= error.id && error.id <= 299)* stream << "SEM.";
			else if(600 <= error.id && error.id <= 699)* stream << "SYN.";
			else *stream << "SYST.";
			*stream << error.id << ": " << error.message;
			if (error.inext.line != -1 && error.inext.col != -1)
				* stream << ", строка " << error.inext.line << ", позиция " << error.inext.col;
		}
	}

	void LOG::WriteLexTable(LT::LexTable& lextable) {
		*stream << "\n ------ Таблица лексем ------ \n";
		//cout << "\n ------ Таблица лексем ------ \n";
		int LTsize = lextable.Size(), pr = 0;
		for (int i = 0; i < LTsize; i++) {
			LT::Entry ent = lextable.GetEntry(i);
			if (pr != ent.sn) {
				//cout << endl << setw(3) << setfill('0') << ent.sn << " ";
				*stream << endl << setw(3) << setfill('0') << ent.sn << " ";
				pr = ent.sn;
			}
			//cout << ent.lexema;
			*stream << ent.lexema;
		}
	}

	void LOG::WriteIdTable(IT::IdTable& idtable) {
		*stream << "\n\n \t\t------ Таблица идентификаторов ------ \n";
			//cout << "\n\n ------ Таблица идентификаторов ------ \n";
		int IDsize = idtable.Size();
		*stream << "\nИмя\t  Область видимости\tИндекс\tТип\t\tТип данных\tЗначение\n";
		 //cout << "\nИмя\t\tИндекс\tТип\t\tТип данных\tзначение\n";
		for (int i = 0; i < IDsize;i++) {
			IT::Entry ent = idtable.GetEntry(i);

			*stream << setw(ID_MAXSIZE) << setfill(' ') << left << ent.id; 
			//cout << setw(ID_MAXSIZE) << setfill(' ') << left << ent.id; 

			*stream << setw(ID_MAXSIZE) << setfill(' ') << left << ent.spacename << '\t';
			//cout << setw(ID_MAXSIZE) << setfill(' ') << left << ent.spacename; 

			*stream << '\t' << setw(3) << setfill('0') <<  right << ent.idxfirstLE << '\t';
			//cout << '\t' << setw(3) << setfill('0') << right << ent.idxfirstLE << '\t';


			switch (ent.idtype) {
			case IT::IDTYPE::V:
				//cout << "variable";
				*stream << "variable"; break;
			case IT::IDTYPE::F:
				//cout << "function";
				*stream << "function"; break;
			case IT::IDTYPE::P:
				//cout << "parameter";
				*stream << "parameter"; break;
			case IT::IDTYPE::L:
				//cout << "literal\t";
				*stream << "literal\t"; break;
			default: break;
			}
			*stream << '\t';
			//cout << '\t';

			switch (ent.iddatatype)
			{
			case IT::IDDATATYPE::NUMB:
				*stream << "number\t\t" << ent.value.vint;
				//cout << "number\t\t" << ent.value.vint;
				break;
			case IT::IDDATATYPE::STR:
			{
				*stream << "string\t\t";
				//cout << "string\t\t";
				*stream << '[' << (int)ent.value.vstr.len << ']';
				//cout << '[' << (int)ent.value.vstr.len << ']';
				for (int i = 0; i < ent.value.vstr.len;i++) {
					//cout << ent.value.vstr.str[i];
					*stream << ent.value.vstr.str[i];
				}
				break;
			}
			case IT::IDDATATYPE::UBYTE:
			{
				*stream << "ubyte\t\t" << (int)ent.value.vubyte;
				break;
			}
			case IT::IDDATATYPE::BOOL:
			{
				*stream << "bool\t\t";
				if (ent.value.vbool)* stream << "true";
				else *stream << "false";
				break;
			}
			}
			*stream << '\n';
			//cout << '\n';
		}
	}

	void LOG::WriteErrors(std::queue<Error::ERROR>& errors) {
		*stream << "\n\t\t----- Список ошибок -----\n";
		while (!errors.empty()) {
			WriteError(errors.front());
			errors.pop();
		}
	}
}
