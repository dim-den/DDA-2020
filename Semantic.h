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
		bool Analysis();
		bool CheckParameters();
	private:
		std::vector<IT::IDDATATYPE> GetExpectedParams(const LT::Entry& entry, const IT::Entry& it_entry);
		const LT::LexTable& LexTable;
		const IT::IdTable& IdTable;		
	};
}