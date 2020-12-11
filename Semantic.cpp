#include "Semantic.h"

namespace SEM
{
	Semantic::Semantic(LT::LexTable& lexTable, IT::IdTable& idTable) : LexTable(lexTable), IdTable(idTable) {}

	void Semantic::Analysis()
	{
		CheckParameters();
		CheckExprTypes();
		if (!errors.empty()) throw errors;
	}

	void Semantic::CheckParameters()
	{
		for (int pos : LexTable.GetFuncCallPos())
		{
			LT::Entry lt_entry = LexTable.GetEntry(pos);
			IT::Entry it_entry = IdTable.GetEntry(lt_entry.idxTI);
			std::vector<IT::IDDATATYPE> expected_params = GetExpectedParams(lt_entry, it_entry);
			int count_param = 0;
			for (int i = pos + 1; LexTable.GetEntry(i).lexema != LEX_RIGHTHESIS; i++)
			{
				LT::Entry entry = LexTable.GetEntry(i);
				if (entry.lexema == LEX_ID || entry.lexema == LEX_LITERAL)	// åñëè ïàðàìåòð ôóíêöèè
				{
					if (count_param < expected_params.size())
					{
						if (!(IdTable.GetEntry(entry.idxTI).iddatatype == expected_params[count_param++])) errors.push(ERROR_THROW_L(208, lt_entry.sn));
					}
					else  errors.push(ERROR_THROW_L(207, lt_entry.sn));
				}
			}
			if (count_param != expected_params.size())  errors.push(ERROR_THROW_L(207, lt_entry.sn));
		}
	}

	void Semantic::CheckExprTypes()
	{
		int left_begin, pos;
		LT::Entry entry;
		IT::IDDATATYPE expected_type = IT::IDDATATYPE::NONE, res = IT::IDDATATYPE::NONE;
		for (int i = 0; i < LexTable.Size();i++)
		{
			entry = LexTable.GetEntry(i);
			switch (entry.lexema)
			{
			case LEX_ASSIGN:		// проверка оператора присваивания
				if (LexTable.GetEntry(i - 1).lexema == LEX_ID)	expected_type = IdTable.GetEntry(LexTable.GetEntry(i - 1).idxTI).iddatatype;
				else expected_type = IT::UBYTE;
				if (expected_type == IT::IDDATATYPE::UBYTE) expected_type = IT::IDDATATYPE::NUMB;
				res = GetExprType(i + 1);
				if (res == IT::IDDATATYPE::UBYTE) res = IT::IDDATATYPE::NUMB;
				if (expected_type != res) errors.push(ERROR_THROW_L(210, entry.sn));
				break;
			case LEX_CONDITION:		// проверка условия (левого и правого операнда)

				left_begin = i;
				for (;(LexTable.GetEntry(left_begin).lexema != LEX_IF) && (LexTable.GetEntry(left_begin).lexema != LEX_ELIF) && (LexTable.GetEntry(left_begin).lexema != LEX_COMPOP);left_begin--) {} // находим крайнее левое положение
				if (LexTable.GetEntry(left_begin).lexema == LEX_COMPOP) left_begin--;
				if (GetExprType(left_begin + 2) != GetExprType(i + 1)) errors.push(ERROR_THROW_L(211, entry.sn));
				break;
			case LEX_RETURN:		// соответсвие возвращаемого значения
				pos = i;
				for (;(LexTable.GetEntry(pos).lexema != LEX_ID) && (LexTable.GetEntry(pos).lexema != LEX_LITERAL); pos++) {}

				for (int k = 0; k < IdTable.Size(); k++)
					if (std::strcmp(IdTable.GetEntry(k).id, IdTable.GetEntry(LexTable.GetEntry(pos).idxTI).spacename) == 0)		// ищем в таблице функцию из которой выходим
						if (GetExprType(i + 1) != IdTable.GetEntry(k).iddatatype)
						{
							errors.push(ERROR_THROW_L(203, entry.sn));
							break;
						}
				break;
			case LEX_PRINT:
				GetExprType(i + 1);
				break;
			case LEX_UNARY:
				if (entry.idxLex == LT::lex_inc || entry.idxLex == LT::lex_dec)
				{
					res = GetExprType(i);
					if (res != IT::NUMB && res != IT::UBYTE) errors.push(ERROR_THROW_L(215, entry.sn));
				}
				break;
			case LEX_FOR:
				entry = LexTable.GetEntry(i+1);
				// for i in 0..1 step i++ 
				//     ^
				if(IdTable.GetEntry(entry.idxTI).iddatatype != IT::NUMB && IdTable.GetEntry(entry.idxTI).iddatatype != IT::UBYTE)
					errors.push(ERROR_THROW_L(215, entry.sn));

				// for i in 0..9 step i++ 
				//          ^  ^
				if ((IdTable.GetEntry(LexTable.GetEntry(i + 3).idxTI).iddatatype != IT::NUMB && IdTable.GetEntry(LexTable.GetEntry(i + 3).idxTI).iddatatype != IT::UBYTE) ||
					(IdTable.GetEntry(LexTable.GetEntry(i + 5).idxTI).iddatatype != IT::NUMB && IdTable.GetEntry(LexTable.GetEntry(i + 5).idxTI).iddatatype != IT::UBYTE))
					errors.push(ERROR_THROW_L(216, entry.sn));
				break;
			default:
				break;
			}
		}
	}

	IT::IDDATATYPE Semantic::GetExprType(int pos)
	{
		expr_pos.push_back(pos); // запоминаем позицию выражения ( для польской нотации)
		LT::Entry lt_entry = LexTable.GetEntry(pos);
		IT::Entry it_entry;
		IT::IDDATATYPE datatype = IT::IDDATATYPE::NONE, expected_type = IT::IDDATATYPE::NONE;
		for (; !LT::LexTable::IsExprEnd(lt_entry.lexema); pos++, lt_entry = LexTable.GetEntry(pos))
		{
			if (lt_entry.lexema == LEX_ID || lt_entry.lexema == LEX_LITERAL)
			{
				it_entry = IdTable.GetEntry(lt_entry.idxTI);
				expected_type = it_entry.iddatatype;
				if (CheckIndex(it_entry, pos)) expected_type = IT::UBYTE;
				if (datatype == IT::IDDATATYPE::NONE) datatype = expected_type;
				else if (expected_type != datatype)
				{
					if(!(expected_type == IT::NUMB && datatype == IT::UBYTE) && !(expected_type == IT::UBYTE && datatype == IT::NUMB)) errors.push(ERROR_THROW_L(209, lt_entry.sn));
				}

				if (it_entry.idtype == IT::IDTYPE::F) for (;LexTable.GetEntry(pos).lexema != LEX_RIGHTHESIS;pos++) {} // игнорируем параметры вызова функции
			}
			else if (((lt_entry.lexema == LEX_ARIFMETIC) || (lt_entry.lexema == LEX_BYTEOP) || (lt_entry.lexema == LEX_UNARY)) && datatype == IT::STR) // недопустмы арифмитические операции над string
				errors.push(ERROR_THROW_L(212, lt_entry.sn));
		}
		return datatype;
	}

	std::vector<IT::IDDATATYPE> Semantic::GetExpectedParams(const LT::Entry& lt_entry, const IT::Entry& it_entry)
	{
		std::vector<IT::IDDATATYPE> expected_params;
		if (it_entry.idxfirstLE < TI_MAXSIZE) // если обычная функция
		{
			for (int i = it_entry.idxfirstLE + 1; LexTable.GetEntry(i).lexema != LEX_RIGHTHESIS; i++)
			{
				auto entry = LexTable.GetEntry(i);
				if (entry.lexema == LEX_ID) expected_params.push_back(IdTable.GetEntry(entry.idxTI).iddatatype);
			}
		}
		else expected_params = IT::GetSTDLib()[it_entry.idxfirstLE - TI_MAXSIZE].params; // если фунция стандартной библиотек		
		return expected_params;
	}

	bool Semantic::CheckIndex(IT::Entry& entry, int& pos)
	{
		LT::Entry lt_entry = LexTable.GetEntry(pos + 1);
		IT::Entry it_entry;
		if (lt_entry.lexema == LEX_LEFTBRACKET)
		{
			pos += 2;
			if(entry.iddatatype != IT::STR) errors.push(ERROR_THROW_L(213, lt_entry.sn));
			it_entry = IdTable.GetEntry(LexTable.GetEntry(pos++).idxTI);
			if(it_entry.iddatatype != IT::NUMB && it_entry.iddatatype != IT::UBYTE) errors.push(ERROR_THROW_L(214, lt_entry.sn));
			return true;
		}
		return false;
	}

	std::vector<int> Semantic::GetExprPos() const
	{
		return expr_pos;
	}
}