#pragma once
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include "Parm.h"

namespace SEM
{
	class Semantic
	{
	public:
		Semantic(LT::LexTable& LT, IT::IdTable& IT);
		void Analysis(Parm::PARM p);
		void CheckParameters();
		void CheckExprTypes();
	private:
		std::queue <Error::ERROR> errors;
		IT::IDDATATYPE GetExprType(int pos);
		std::vector<IT::IDDATATYPE> GetExpectedParams(const LT::Entry& entry, const IT::Entry& it_entry);
		 LT::LexTable& LexTable;
		 IT::IdTable& IdTable;		
	};
}