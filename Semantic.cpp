#include "Semantic.h"


namespace SEM
{
	Semantic::Semantic(LT::LexTable& lexTable, IT::IdTable& idTable) : LexTable(lexTable), IdTable(idTable) {}

	bool Semantic::Analysis()
	{
		CheckParameters();

		return true;
	}

	bool Semantic::CheckParameters()
	{
		std::queue <Error::ERROR> errors;

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
		if (!errors.empty()) throw errors;
		return true;
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
}