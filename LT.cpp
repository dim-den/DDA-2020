#include "LT.h"

using namespace std;
namespace LT
{
	LexTable::LexTable(int size) : maxsize(size) {
		if (size > LT_MAXSIZE) throw ERROR_THROW(121);
		this->size = 0;
		table = new Entry[size];
	}

	void LexTable::Add(Entry entry) 
	{
		if (size >= maxsize) throw ERROR_THROW(122);
		table[size++] = entry;
	}

	Entry& LexTable::GetEntry(int n) const
	{
		if (n > size) throw ERROR_THROW(123);
		return table[n];
	}

	LexTable::~LexTable() 
	{
		if (table != nullptr) {
			delete[] table;
		}
	}

	void LexTable::LexAnalysis(wchar_t* out_file, IT::IdTable& ID) {
		int row = 1, col = 1;
		queue <Error::ERROR> errors;
		IT::IDDATATYPE nxt_id_datatype = IT::IDDATATYPE::NONE;
		IT::IDTYPE nxt_id_type = IT::IDTYPE::N;
		ifstream File(out_file);
		string line, space_name;
		int add_id_res = 0, lit_count = 0, func_call_count = 0, opened_leftbrace = 0;		
		bool main_included = false;
		queue<int> lt_pos;
		while (getline(File, line))
		{
			vector<string> lexems = SeparateLexems(line);
			col = 1;
			for (string& lexem : lexems)
			{
				if (lexem == "\n") continue;
				int symbol_code = LexDefinition(lexem);
				if (symbol_code < 0) errors.push(ERROR_THROW_IN(120, row, col)); 
				else 
				{
					LT::Entry entry;
					//entry.idxTI = LT_TI_NULLIDX;
					switch (symbol_code)
					{
					case lex_assign:
						lt_pos.push(size + 1);
						break;
					case lex_number:
						nxt_id_datatype = IT::IDDATATYPE::NUMB;
						break;
					case lex_string:
						nxt_id_datatype = IT::IDDATATYPE::STR;
						break;
					case lex_ubyte:
						nxt_id_datatype = IT::IDDATATYPE::UBYTE;
						break;
					case lex_bool:
						nxt_id_datatype = IT::IDDATATYPE::BOOL;
						break;
					case lex_def:
						nxt_id_type = IT::IDTYPE::V;
						break;
					case lex_main:
						space_name = LEX_MAIN_SPACE;
						if (!main_included) main_included = true;
						else errors.push(ERROR_THROW_IN(200, row, col));
						break;
					case lex_function:
						nxt_id_type = IT::IDTYPE::F;
						break;
					case lex_leftbrace:
						opened_leftbrace++;
						break;
					case lex_bracelet:
						opened_leftbrace--;
						if(!opened_leftbrace) space_name = "";
						break;
					case lex_righthesis:
						nxt_id_type = IT::IDTYPE::N;
						break;
					case lex_true_lit:
						add_id_res = AddLit(ID, lit_count, size, 1, space_name, IT::IDDATATYPE::BOOL, "");
						break;
					case lex_false_lit:
						add_id_res = AddLit(ID, lit_count, size, 0, space_name, IT::IDDATATYPE::BOOL , "");
						break;
					case lex_str_lit:
						add_id_res = AddLit(ID, lit_count, size, lexem.length(), space_name, IT::IDDATATYPE::STR, lexem);
						if (add_id_res == -1) errors.push(ERROR_THROW_IN(127, row, col));
						entry.idxTI = add_id_res;
						break;
					case lex_dig_lit:
						add_id_res = AddLit(ID, lit_count, size, atoi(lexem.c_str()), space_name, IT::IDDATATYPE::NUMB , "");
						entry.idxTI = add_id_res;						
						break;
					case lex_id:
						add_id_res = AddId(ID, lexem, nxt_id_datatype, nxt_id_type, size, space_name);
						if (add_id_res == -1) errors.push(ERROR_THROW_IN(202, row, col));
						else if (add_id_res == -2) errors.push(ERROR_THROW_IN(204, row, col));
						else if (add_id_res == -3) errors.push(ERROR_THROW_IN(205, row, col));
						else if (add_id_res == -4) errors.push(ERROR_THROW_IN(206, row, col));
						entry.idxTI = add_id_res;
						break;
					default: break;
					}
					
					entry.lexema = avail_lexems[symbol_code];
					entry.sn = row;
					if (symbol_code != lex_id && symbol_code != lex_str_lit && symbol_code != lex_dig_lit && symbol_code != lex_true_lit && symbol_code!= lex_false_lit) entry.idxLex = symbol_code;
					Add(entry);
	
				}
				col++;
			}
			row++;
		}
		if (!main_included) errors.push(ERROR_THROW(201));
		//while(!lt_pos.empty()) {
		// if (!PolishNotation(ID, lt_pos.front(), func_call_count)) errors.push(ERROR_THROW_IN(128, table[pos].sn, 3));
		// lt_pos.pop();
		// }				
		if (!errors.empty()) throw errors;
	}

	std::vector<std::string> LexTable::SeparateLexems(std::string& line) {
		vector<string> res;
		string lexem;
		bool str_lit = false;
		int pos_str_lit = 0;
		if (line[0] != IN_CODE_SEPARATOR) {
			for (int i = 0; i < line.size() - 1; i++) {
				if (line[i] == IN_CODE_SPACE && !str_lit) {
					res.push_back(lexem);
					lexem = "";
				}
				else if (line[i] == LEX_QUOTE) {
					if (str_lit) {
						lexem += LEX_QUOTE;
						res.push_back(lexem);
						lexem = "";
						str_lit = false;
					}
					else {
						lexem += LEX_QUOTE;
						pos_str_lit = res.size();
						str_lit = true;
					}
				}
				else if (In::is_expr(line[i]))
				{
					if (!lexem.empty()) res.push_back(lexem);
					string s; s = line[i];
					if (line[i + 1] == LEX_ASSIGN) {
						s += '=';
						res.push_back(s);
						i++;
					}
					else res.push_back(s);
					lexem = "";
				}
				else {
					lexem += line[i];
				}
			}
			if (!lexem.empty()) res.push_back(lexem);
		}
		else res.push_back("\n");
		if (str_lit) res[pos_str_lit] = "_";
		return res;
	}

	int LexTable::AddId(IT::IdTable& ID, std::string& input, IT::IDDATATYPE& iddatatype, IT::IDTYPE& idtype, int idx, string& space_name) // добавление элемента в таблицу идентификаторрв
	{
		char id[ID_MAXSIZE];
		char spacename[ID_MAXSIZE];
		if (space_name == "") space_name = LEX_GLOBAL;
		strncpy_s(spacename, space_name.c_str(), ID_MAXSIZE - 1);
		strncpy_s(id, input.c_str(), ID_MAXSIZE - 1);
		int IsId = ID.IsId(id, spacename);
		if (IsId == TI_NULLIDX) // если id не существует
		{ 
			if (idtype == IT::IDTYPE::N || iddatatype == IT::IDDATATYPE::NONE) // если не хватает данных
			{
				IsId = ID.IsId(id, (char*)LEX_GLOBAL); // проверка на наличие в глобальной области (если это вызов функции)
				if (IsId == TI_NULLIDX)	return -1;
				func_call_pos.push_back(idx);
				return IsId;
			}
			if (idtype == IT::IDTYPE::V && std::strcmp(spacename, LEX_GLOBAL) == 0) return -3;
			IT::Entry ent;
			strncpy_s(ent.id, id, ID_MAXSIZE);
			strncpy_s(ent.spacename, spacename, ID_MAXSIZE);
			ent.idxfirstLE = idx;
			ent.iddatatype = iddatatype;
			ent.idtype = idtype;
			if (iddatatype == IT::IDDATATYPE::NUMB) ent.value.vint = TI_INT_DEFAULT;
			else if (iddatatype == IT::IDDATATYPE::STR) ent.value.vstr.len = TI_STR_DEFAULT;
			else if (iddatatype == IT::IDDATATYPE::UBYTE) ent.value.vubyte = TI_UBYTE_DEFAULT;
			else if (iddatatype == IT::IDDATATYPE::BOOL) ent.value.vbool = TI_BOOL_DEFAULT;
			if (idtype == IT::IDTYPE::F) {
				idtype = IT::IDTYPE::P;
				if (space_name == LEX_GLOBAL) space_name = input;
			}
			else if (idtype != IT::IDTYPE::P) idtype = IT::IDTYPE::N;
			iddatatype = IT::IDDATATYPE::NONE;
			return ID.Add(ent);
		}
		if (idtype != IT::IDTYPE::N || iddatatype != IT::IDDATATYPE::NONE) { // идентификатор должен быть уникальным
			if (idtype == IT::IDTYPE::F) {
				idtype = IT::IDTYPE::P;
				if (space_name == LEX_GLOBAL) space_name = input;
			}
			else idtype = IT::IDTYPE::N;
			iddatatype = IT::IDDATATYPE::NONE;
			if (IsId < TI_LIBRARYSIZE) return -4;
			return -2;
		}
		return IsId;
	}

	int LexTable::AddLit(IT::IdTable& ID, int& lit_count, int idx, int value, string& space_name, IT::IDDATATYPE iddatatype, string data) 
	{
		IT::Entry ent;
		string lit_id = "lit_" + to_string(lit_count);
		strncpy_s(ent.id, lit_id.c_str(), ID_MAXSIZE - 1);
		strncpy_s(ent.spacename, space_name.c_str(), ID_MAXSIZE - 1);
		ent.idxfirstLE = idx;
		ent.iddatatype = iddatatype;
		ent.idtype = IT::IDTYPE::L;
		if (iddatatype == IT::IDDATATYPE::NUMB) ent.value.vint = value;
		else if (iddatatype == IT::IDDATATYPE::BOOL) ent.value.vbool = value;
		else if (iddatatype == IT::IDDATATYPE::STR) {
			if (value - 2 > TI_STR_MAXSIZE) return -1;
			ent.value.vstr.len = value - 2;
			strncpy_s(ent.value.vstr.str, data.substr(1, value - 2).c_str(), value - 2);
		}
		lit_count++;
		return ID.Add(ent);
	}

	int LexTable::LexDefinition(std::string input) // производит анализ входной цепочки, возвращает номер элемента в таблице avail_lexems, если элемента нет возвращает -1
	{
		for (int i = 0; i < LEX_COUNT; i++) {
			Fst::FST fst = avail_lexems_FST[i];
			fst.string = (char*)input.c_str();
			if (!Fst::execute(fst)) return i;
		}
		return -1;
	}

	bool LexTable::PolishNotation(IT::IdTable& ID, int lt_pos, int& func_call_count)
	{
		std::map<int, int> oper_priority =
		{
			{lex_lefthesis,		0},
			{lex_righthesis,	0},
			{lex_comma,			1},
			{lex_minus,			2},
			{lex_plus,			2},
			{lex_star,			3},
			{lex_dirslash,		3},
			{lex_leftbracket,	4},
			{lex_rightbracket,	4},
		};

		std::stack<Entry> operators;			// стек операторов
		std::stack<IT::Entry> called_func;	// стек вызовов функций
		LT::Entry entry = table[lt_pos];
		int length = 0;
		while (table[lt_pos + length].lexema != LEX_SEMICOLON) length++;
		LT::LexTable expr(length);

		int sn = entry.sn;
		for (int i = lt_pos; entry.lexema != LEX_SEMICOLON; i++, entry = table[i])
		{
			switch (entry.lexema)
			{
			case LEX_ARIFMETIC: // + - * /
				while (!operators.empty() && operators.top().lexema != LEX_LEFTBRACKET && oper_priority[entry.idxLex] <= oper_priority[operators.top().idxLex]) {
					expr.Add(operators.top());
					operators.pop();
				}
				operators.push(entry);
				break;
			case LEX_LEFTHESIS: // (
				operators.push(entry);
				break;
			case LEX_RIGHTHESIS: // )
				while (true) {
					if (operators.top().lexema == LEX_LEFTHESIS) {
						operators.pop();
						break;
					}
					else if (operators.top().lexema == LEX_LEFTBRACKET) {
						operators.pop();
						called_func.top().iddatatype = IT::IDDATATYPE::NUMB;
						string name = called_func.top().id; name += '_' + to_string(func_call_count++);
						strncpy_s(called_func.top().id, name.c_str(), ID_MAXSIZE - 1);
						called_func.top().idxfirstLE = lt_pos + expr.size;
						expr.Add({ LEX_FUNC_CALL, entry.sn, ID.Add(called_func.top()) });
						called_func.pop();
						break;
					}
					else {
						expr.Add(operators.top());
						operators.pop();
					}
				}
				break;
			case LEX_ID:
				if (ID.GetEntry(entry.idxTI).idtype == IT::IDTYPE::F) {	// если функция => добавляем [
					i++;
					operators.push({ LEX_LEFTBRACKET, entry.sn, LT::lexem_number::lex_leftbracket });
					called_func.push(ID.GetEntry(entry.idxTI));
					called_func.top().value.vint = 0;
				}
				else expr.Add(entry);
				break;
			case LEX_LITERAL:
				expr.Add(entry);
				break;
			case LEX_COMMA:
				if (called_func.top().value.vint == 0) called_func.top().value.vint = 1;
				while (!operators.empty() && operators.top().lexema != LEX_LEFTBRACKET && operators.top().lexema != LEX_LEFTHESIS) {
					expr.Add(operators.top());
					operators.pop();
				}
				called_func.top().value.vint++;
				break;
			default:
				return false;
			}
		}

		while (!operators.empty()) {
			expr.Add(operators.top());
			operators.pop();
		}

		InsertTable(lt_pos, length, sn, expr);

		return true;
	}
	
	std::vector<int> LexTable::GetFuncCallPos() const 
	{
		return func_call_pos;
	}
	void LexTable::InsertTable(int pos, int length, int sn, LT::LexTable& LT)
	{
		for (int i = 0; i < length + 1; i++) {
			if (i == LT.Size()) table[pos + i] = { LEX_SEMICOLON , sn, LT::lexem_number::lex_semicolon };
			else if (i > LT.Size()) {
				table[pos + i] = { LEX_PAD , sn, LT::lexem_number::lex_pad };
			}
			else table[pos + i] = LT.GetEntry(i);
		}
	}

	int LexTable::Size() const {
		return size;
	}
}
