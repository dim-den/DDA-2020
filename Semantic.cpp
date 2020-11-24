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
				if (entry.lexema == LEX_ID || entry.lexema == LEX_LITERAL)	// если параметр функции
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
		IT::IDDATATYPE expected_type = IT::IDDATATYPE::NONE, res;
		for (int i = 0; i < LexTable.Size();i++)
		{
			entry = LexTable.GetEntry(i);
			switch (entry.lexema)
			{
			case LEX_ASSIGN:		// проверка оператора присваивания
				expected_type = IdTable.GetEntry(LexTable.GetEntry(i - 1).idxTI).iddatatype;
				if (expected_type == IT::IDDATATYPE::UBYTE) expected_type = IT::IDDATATYPE::NUMB;
				res = GetExprType(i + 1);
				if (res == IT::IDDATATYPE::UBYTE) res = IT::IDDATATYPE::NUMB;
				if (expected_type != res) errors.push(ERROR_THROW_L(210, entry.sn));
				break;
			case LEX_CONDITION:		// проверка условия (левого и правого операнда)
				left_begin = i;
				for (;(LexTable.GetEntry(left_begin).lexema != LEX_IF) && (LexTable.GetEntry(left_begin).lexema != LEX_ELIF);left_begin--) {} // находим крайнее левое положение
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
		IT::IDDATATYPE datatype = IT::IDDATATYPE::NONE;
		for (; (lt_entry.lexema != LEX_SEMICOLON) && (lt_entry.lexema != LEX_CONDITION) && (lt_entry.lexema != LEX_LEFTBRACE); pos++, lt_entry = LexTable.GetEntry(pos))
		{
			if (lt_entry.lexema == LEX_ID || lt_entry.lexema == LEX_LITERAL)
			{
				it_entry = IdTable.GetEntry(lt_entry.idxTI);
				if (datatype == IT::IDDATATYPE::NONE) datatype = it_entry.iddatatype;
				else if (it_entry.iddatatype != datatype) errors.push(ERROR_THROW_L(209, lt_entry.sn));
				if (it_entry.idtype == IT::IDTYPE::F) for (;LexTable.GetEntry(pos).lexema != LEX_RIGHTHESIS;pos++) {} // игнорируем параметры вызова функции
			}
			else if (((lt_entry.lexema == LEX_ARIFMETIC) || (lt_entry.lexema == LEX_BYTEOP) || (lt_entry.lexema == LEX_INV)) && datatype == IT::STR) // недопустмы арифмитические операции над string
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

	std::vector<int> Semantic::GetExprPos() const
	{
		return expr_pos;
	}
}