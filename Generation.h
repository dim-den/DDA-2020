#pragma once
#include "IT.h"
#include "LT.h"

namespace Gen
{
	class Generator
	{
	public:
		Generator(const LT::LexTable& lexTable, const IT::IdTable& idTable, wchar_t* out);
		~Generator();
		void Generate();
	private:
		const LT::LexTable& lexTable;
		const IT::IdTable& idTable;
		std::ofstream* out = nullptr;
		void Head();
		bool Constants();
		bool Data();
		void Code();
		std::string GetType(IT::IDDATATYPE);
		std::string GetOppositeCompareType(int);
		IT::IDDATATYPE GenerateExpression(int pos);
	};
}