#include "Generation.h"
#include <string>
namespace Gen
{
#define IT_ENTRY(i) idTable.GetEntry(i)
#define LT_ENTRY(i) lexTable.GetEntry(i)

	Generator::Generator(const LT::LexTable& lexTable, const IT::IdTable& idTable, wchar_t* out) : idTable(idTable), lexTable(lexTable), out(new std::ofstream(out)) {}

	Generator::~Generator()
	{
		if (out != nullptr) {
			out->close();
			delete out;
		}
	}

	std::string Generator::GetType(IT::IDDATATYPE datatype)
	{
		switch (datatype)
		{
		case IT::IDDATATYPE::STR: return "SBYTE";
		case IT::IDDATATYPE::NUMB: return "SDWORD";
		case IT::IDDATATYPE::UBYTE: return "BYTE";
		case IT::IDDATATYPE::BOOL: return "BYTE";
		}
	}

	std::string Generator::GetOppositeCompareType(int lex)
	{
		switch (lex)
		{
		case LT::lex_equal: return "jne";
		case LT::lex_notequal: return "je";
		case LT::lex_more: return "jle";
		case LT::lex_moreequal: return "jl";
		case LT::lex_less: return "jge";
		case LT::lex_lessequal: return "jg";
		}
	}

	void Generator::Generate()
	{
		Head();
		Constants();
		Data();
		Code();
	}

	void Generator::Head()
	{
		*out << ".586P\n";
		*out << ".model flat, stdcall\n";
		*out << "includelib libucrt.lib\n";
		*out << "includelib user32.lib\n";
		*out << "includelib kernel32.lib\n\n";
		*out << "ExitProcess PROTO : DWORD\n\n";
		*out << "extrn print_number : proc\n";
		*out << "extrn print_string : proc\n";
		*out << "extrn print_bool : proc\n";
		*out << "extrn print_ubyte : proc\n";
		*out << "extrn get_string : proc\n";
		*out << "extrn get_bool : proc\n";
		*out << "extrn get_number : proc\n";
		*out << "extrn strcopy : proc\n";
		*out << "extrn strconcat : proc\n\n";
		*out << ".stack 4096\n\n";
	}

	bool Generator::Constants()
	{
		*out << ".const\n";
		IT::Entry entry;
		for (int i = 0; i < idTable.Size(); i++)
		{
			entry = idTable.GetEntry(i);
			if (entry.idtype == IT::IDTYPE::L) // заносим литералы в сегмент констант
			{
				*out << entry.id << ' ' << GetType(entry.iddatatype) << ' ';
				switch (entry.iddatatype)
				{
				case IT::IDDATATYPE::STR:
					*out << "\"" << entry.value.vstr.str << "\", 0\n";
					break;
				case IT::IDDATATYPE::NUMB:
					*out << entry.value.vint << '\n';
					break;
				case IT::IDDATATYPE::BOOL:
					*out << entry.value.vbool << '\n';
					break;
				default:
					return false;
				}
			}
		}
		*out << '\n';
		return true;
	}

	bool Generator::Data()
	{
		*out << ".data\n";
		IT::Entry entry;
		for (int i = 0; i < idTable.Size(); i++)
		{
			entry = idTable.GetEntry(i);
			if (entry.idtype == IT::IDTYPE::V)
			{
				*out << entry.spacename << '_' << entry.id << ' ' << GetType(entry.iddatatype);
				if (entry.iddatatype == IT::STR)* out << " 255 dup (?)\n";
				else *out << " ?\n";
			}
		}
		*out << '\n';
		return true;
	}

	void Generator::Code()
	{
		*out << ".code\n";
		bool first_par = true;
		char current_proc[ID_MAXSIZE];
		bool is_proc = false, is_main = false;
		bool is_if = false, last_if, single_if = false;
		int if_count = 0, condition_count = 0;

		int lt_pos = 0, leftbrace_opened = 0;
		IT::Entry it_entry;
		LT::Entry lt_entry;
		IT::IDDATATYPE expr_type;
		for (int i = 0; i < lexTable.Size(); i++)
		{
			lt_entry = LT_ENTRY(i);
			switch (lt_entry.lexema)
			{
			case LEX_FUNCTION:
				is_proc = true;
				lt_pos = LT_ENTRY(++i).idxTI;
				it_entry = IT_ENTRY(lt_pos);
				strncpy_s(current_proc, it_entry.id, ID_MAXSIZE - 1);
				*out << it_entry.id << " PROC ";
				while (IT_ENTRY(++lt_pos).idtype == IT::IDTYPE::P) {}
				while (true) // выводим параметры par : TYPE ,   в обратном порядке
				{
					it_entry = IT_ENTRY(--lt_pos);
					if (it_entry.idtype != IT::IDTYPE::P) break;
					if (!first_par)* out << ", ";
					*out << it_entry.spacename << '_' << it_entry.id << " : " << GetType(it_entry.iddatatype);
					first_par = false;
				}
				*out << '\n';
				first_par = true;
				break;
			case LEX_MAIN:
				*out << "main PROC\n";
				is_main = true;
				break;
			case LEX_IF:
				is_if = last_if = true;
				GenerateComparison(i, condition_count);
				break;
			case LEX_ELIF:
				last_if = single_if= false;
				*out << "condition_" << condition_count++ << ":\n";
				GenerateComparison(i, condition_count);
				break;
			case LEX_ELSE:
				last_if = single_if = false;
				*out << "condition_" << condition_count++ << ":\n";
				break;
			case LEX_TO:
				single_if = true;
				break;
			case LEX_LEFTBRACE:
				leftbrace_opened++;
				break;
			case LEX_BRACELET:
				leftbrace_opened--;
				if (!leftbrace_opened) // если конец функции
				{
					if (is_proc)
					{
						*out << current_proc << " endp\n\n";
						is_proc = false;
					}
					else if (is_main)
					{
						*out << "call ExitProcess\n";
						*out << "main ENDP\n\n";
						*out << "end main";
						is_main = false;
					}
				}
				else if (is_if)
				{
					*out << "jmp " << "if_end_" << if_count << '\n' << '\n';
					lt_entry = LT_ENTRY(i + 1);
					if (lt_entry.lexema != LEX_ELIF && lt_entry.lexema != LEX_ELSE)
					{
						is_if = false;
						if (last_if)* out << "condition_" << condition_count++ << ":\n";
						*out << "if_end_" << if_count++ << ":\n";

					}
				}
				break;
			case LEX_SEMICOLON:
				if (is_if && single_if)
				{
					*out << "jmp " << "if_end_" << if_count << '\n' << '\n';
					lt_entry = LT_ENTRY(i + 1);
					if (lt_entry.lexema != LEX_ELIF && lt_entry.lexema != LEX_ELSE)
					{
						is_if = single_if = false;
						if (last_if)* out << "condition_" << condition_count++ << ":\n";
						*out << "if_end_" << if_count++ << ":\n";

					}
				}
				break;
			case LEX_RETURN:
				GenerateExpression(++i);
				if (is_proc)* out << "pop eax\nret\n\n";
				break;
			case LEX_ASSIGN:
				it_entry = IT_ENTRY(LT_ENTRY(i - 1).idxTI);
				if (it_entry.iddatatype == IT::STR)* out << "push offset " << it_entry.spacename << '_' << it_entry.id << '\n';
				expr_type = GenerateExpression(++i);
				if (it_entry.iddatatype == IT::UBYTE || it_entry.iddatatype == IT::BOOL)
				{
					*out << "pop eax\n";
					*out << "mov " << it_entry.spacename << '_' << it_entry.id << ", al\n\n";
				}
				else if (expr_type == IT::STR)* out << "call strcopy\n";
				else *out << "pop " << it_entry.spacename << '_' << it_entry.id << '\n' << '\n';
				break;
			case LEX_PRINT:
				expr_type = GenerateExpression(++i);
				*out << "call ";
				if (expr_type == IT::STR)* out << "print_string\n";
				else if (expr_type == IT::BOOL)* out << "print_bool\n";
				else if (expr_type == IT::NUMB)* out << "print_number\n";
				else if (expr_type == IT::UBYTE)* out << "print_ubyte\n";
				break;
			case LEX_GET:
				it_entry = IT_ENTRY(LT_ENTRY(++i).idxTI);
				*out << "push offset " << it_entry.spacename << '_' << it_entry.id << '\n';
				*out << "call ";
				if (it_entry.iddatatype == IT::STR)* out << "get_string\n";
				else if (it_entry.iddatatype == IT::BOOL)* out << "get_bool\n";
				else *out << "get_number\n";
				break;
			default:
				break;
			}
		}
	}

	IT::IDDATATYPE Generator::GenerateExpression(int pos)
	{
		IT::Entry it_entry;
		LT::Entry lt_entry;
		IT::IDDATATYPE expr_type = IT::IDDATATYPE::NONE;
		for (lt_entry = LT_ENTRY(pos);lt_entry.lexema != LEX_PAD && lt_entry.lexema != LEX_SEMICOLON && lt_entry.lexema != LEX_CONDITION && lt_entry.lexema != LEX_RIGHTHESIS; pos++, lt_entry = LT_ENTRY(pos))
		{
			if (lt_entry.lexema == LEX_ID || lt_entry.lexema == LEX_LITERAL)
			{
				it_entry = IT_ENTRY(lt_entry.idxTI);
				expr_type = it_entry.iddatatype;
				if (it_entry.iddatatype != IT::UBYTE && expr_type != IT::BOOL)
				{
					*out << "push ";
					if (it_entry.iddatatype == IT::IDDATATYPE::STR)* out << "offset ";
					if (it_entry.idtype != IT::IDTYPE::L)* out << it_entry.spacename << '_';
					*out << it_entry.id << '\n';
				}
				else
				{
					*out << "mov eax, 0\n";
					*out << "mov al, ";
					if (it_entry.idtype != IT::IDTYPE::L)* out << it_entry.spacename << '_';
					*out << it_entry.id << '\n';
					*out << "push eax\n";
				}
			}
			else if (lt_entry.lexema == '@')
			{
				it_entry = IT_ENTRY(lt_entry.idxTI);
				*out << "call ";
				for (int i = 0; it_entry.id[i] != '_'; i++)* out << it_entry.id[i];
				*out << "\npush eax\n";
			}
			else if (lt_entry.lexema == LEX_ARIFMETIC || lt_entry.lexema == LEX_BYTEOP || lt_entry.lexema == LEX_INV)
			{
				switch (lt_entry.idxLex)
				{
				case LT::lex_plus:
					*out << "pop ebx\n";
					*out << "pop eax\n";
					*out << "add eax, ebx\n";
					*out << "push eax\n";
					break;
				case LT::lex_minus:
					*out << "pop ebx\n";
					*out << "pop eax\n";
					*out << "sub eax, ebx\n";
					*out << "push eax\n";
					break;
				case LT::lex_star:
					*out << "pop ebx\n";
					*out << "pop eax\n";
					*out << "imul eax, ebx\n";
					*out << "push eax\n";
					break;
				case LT::lex_dirslash:
					*out << "pop ebx\n";
					*out << "pop eax\n";
					*out << "cdq\n";
					*out << "idiv ebx\n";
					*out << "push eax\n";
					break;
				case LT::lex_and:
					*out << "pop ebx\n";
					*out << "pop eax\n";
					*out << "and eax, ebx\n";
					*out << "push eax\n";
					break;
				case LT::lex_or:
					*out << "pop ebx\n";
					*out << "pop eax\n";
					*out << "or eax, ebx\n";
					*out << "push eax\n";
					break;
				case LT::lex_inv:
					*out << "pop eax\n";
					*out << "not eax\n";
					*out << "push eax\n";
					break;
				}
			}
		}
		return expr_type;
	}

	void Generator::GenerateComparison(int& pos, int condition_count)
	{
		LT::Entry lt_entry;
		GenerateExpression(pos + 2); // в стеке результат левого значения
		while (LT_ENTRY(pos).lexema != LEX_CONDITION) pos++;
		lt_entry = LT_ENTRY(pos);
		GenerateExpression(++pos);
		*out << "pop ebx\n";
		*out << "pop eax\n";
		*out << "cmp eax, ebx\n";
		*out << GetOppositeCompareType(lt_entry.idxLex) << " condition_" << condition_count << '\n';
	}
}