#include "Log.h"
#include <cstring>
#pragma warning(disable: 4996)
using namespace std;

#define output(message)  if(debug_mode) { std::cout << message; if(stream != nullptr) *stream << message;} \
						 else *stream << message

extern bool DEBUG_MODE;

namespace Log
{
	LOG::LOG() : logfile(L""), stream(nullptr) {}

	LOG::LOG(Parm::PARM& parm)
	{
		stream = new ofstream(parm.log);
		debug_mode = DEBUG_MODE;
		if (!stream->is_open()) throw ERROR_THROW(112);
		wcscpy_s(this->logfile, parm.log);
	}

	void LOG::WriteLine(const char* c, ...)
	{
		int i = 0;
		const char** str = &c;
		while (str[i] != "")
			* stream << str[i++];
		*stream << IN_CODE_ENDL;
	}

	void LOG::WriteLine(const wchar_t* c, ...)
	{
		int i = 0;
		const wchar_t** str = &c;
		while (str[i] != L"")
			* stream << str[i++];
		*stream << IN_CODE_ENDL;
	}

	LOG& LOG::operator=(Log::LOG&& rhs) noexcept
	{
		wcscpy_s(logfile, rhs.logfile);
		debug_mode = rhs.debug_mode;
		stream = rhs.stream;
		rhs.stream = nullptr;
		return *this;
	}

	LOG::~LOG()
	{
		if (stream != nullptr) {
			stream->close();
			delete stream;
		}
	}

	void LOG::WriteLog()  // ������� � �������� ���������
	{
		tm* timeinfo;
		time_t ttime;
		time(&ttime);
		timeinfo = localtime(&ttime);
		char info[TIME_LOG_SIZE];
		strftime(info, TIME_LOG_SIZE, "\n ------ �������� ------\n ����: %d.%m.%y %T \n", timeinfo);
		output(info);
	}

	void LOG::WriteParm(const Parm::PARM& parm) // ������� ���������� � ������� ����������
	{
		char i[PARM_MAX_SIZE], o[PARM_MAX_SIZE], l[PARM_MAX_SIZE];
		wcstombs(i, parm.in, PARM_MAX_SIZE);
		wcstombs(o, parm.out, PARM_MAX_SIZE);
		wcstombs(l, parm.log, PARM_MAX_SIZE);
		output("\n ------ ��������� ------ "
			<< "\n-log: " << l
			<< "\n-out: " << o
			<< "\n-in:  " << i
			<< "\n-debug: " << DEBUG_MODE << IN_CODE_ENDL);
	}

	void LOG::WriteIn(const In::IN& in) // ������� ���������� � ������� ������
	{
		output("n ------ �������� ������ ------ " <<
			"\n����� ��������: " << in.size <<
			"\n����� �����: " << in.lines <<
			"\n���������: " << in.ignor << "\n");
	}

	void LOG::WriteError(const Error::ERROR& error) // ������� ���������� �� ������
	{
		bool tmp = move(debug_mode);
		debug_mode = true;

		output(IN_CODE_ENDL);
		if (100 <= error.id && error.id <= 109) output("PARM.");
		else if (110 <= error.id && error.id <= 119) output("IN.");
		else if (120 <= error.id && error.id <= 139) output("LEX.");
		else if (200 <= error.id && error.id <= 299) output("SEM.");
		else if (600 <= error.id && error.id <= 699) output("SYN.");
		else output("SYST.");
		output(error.id << ": " << error.message);
		if (error.inext.line != -1) output(", ������ " << error.inext.line);
		if (error.inext.col != -1) output(", ������� " << error.inext.col);

		debug_mode = move(tmp);
	}

	void LOG::WriteLexTable(LT::LexTable& lextable)
	{
		output("\n ------ ������� ������ ------ \n");
		int LTsize = lextable.Size(), pr = 0;
		for (int i = 0; i < LTsize; i++)
		{
			LT::Entry ent = lextable.GetEntry(i);
			if (pr != ent.sn)
			{
				output(endl << right << setw(3) << setfill('0') << ent.sn << " ");
				pr = ent.sn;
			}
			output(ent.lexema);
		}
	}

	void LOG::WriteIdTable(IT::IdTable& idtable)
	{
		output("\n\n \t\t------ ������� ��������������� ------ \n");
		int IDsize = idtable.Size();
		output(IN_CODE_ENDL << setw(ID_MAXSIZE) << setfill(' ') << left << "���" << setw(ID_MAXSIZE) << "������� ���������" << left << "\t������\t���\t\t��� ������\t��������\n");
		for (int i = 0; i < IDsize;i++)
		{
			IT::Entry ent = idtable.GetEntry(i);

			output(setw(ID_MAXSIZE) << setfill(' ') << left << ent.id);
			output(setw(ID_MAXSIZE) << setfill(' ') << left << ent.spacename << '\t');

			output(setw(4) << setfill('0') << right << ent.idxfirstLE << '\t');

			switch (ent.idtype)
			{
			case IT::IDTYPE::V:
				output("variable"); break;
			case IT::IDTYPE::F:
				output("function"); break;
			case IT::IDTYPE::P:
				output("parameter"); break;
			case IT::IDTYPE::L:
				output("literal\t"); break;
			}
			output('\t');

			switch (ent.iddatatype)
			{
			case IT::IDDATATYPE::NUMB:
				output("number\t\t" << ent.value.vint);
				break;
			case IT::IDDATATYPE::STR:
			{
				output("string\t\t");
				output('[' << (int)ent.value.vstr.len << ']');
				for (int i = 0; i < ent.value.vstr.len;i++) {
					output(ent.value.vstr.str[i]);
				}
				break;
			}
			case IT::IDDATATYPE::UBYTE:
			{
				output("ubyte\t\t" << (int)ent.value.vubyte);
				break;
			}
			case IT::IDDATATYPE::BOOL:
			{
				output("bool\t\t");
				if (ent.value.vbool)  output("true");
				else output("false");
				break;
			}
			}
			output(IN_CODE_ENDL);
		}
	}

	void LOG::WriteResultTime(size_t lex_time, size_t synt_time, size_t sem_time, size_t gen_time, size_t overall)
	{
		debug_mode = true;
		output("\n����� ����������:\n"
			<< "����������� ������: " << lex_time << "��\n"
			<< "�������������� ������: " << synt_time << "��\n"
			<< "������������� ������: " << sem_time << "��\n"
			<< "��������� ����: " << gen_time << "��\n"
			<< "�����: " << overall << "��\n");
	}

	void LOG::WriteErrors(std::queue<Error::ERROR>& errors)
	{
		output("\n\t\t----- ������ ������ -----\n");
		while (!errors.empty())
		{
			WriteError(errors.front());
			errors.pop();
		}
	}
}
