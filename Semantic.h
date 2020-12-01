#pragma once
#include "LT.h"
#include "IT.h"
#include "Error.h"

namespace SEM
{
	class Semantic
	{
	public:
		Semantic(LT::LexTable& LT, IT::IdTable& IT);
		void Analysis();
		void CheckParameters();
		void CheckExprTypes();
		std::vector<int> GetExprPos() const;
	private:
		std::queue <Error::ERROR> errors;
		std::vector <int> expr_pos;
		bool CheckIndex(IT::Entry& entry, int& pos);
		IT::IDDATATYPE GetExprType(int pos);
		std::vector<IT::IDDATATYPE> GetExpectedParams(const LT::Entry& entry, const IT::Entry& it_entry);
		const LT::LexTable& LexTable;
		const IT::IdTable& IdTable;		
	};
}