#pragma once
#include "IT.h"
#include "LT.h"

namespace Gen
{
#define GEN_PLUS *out << "pop ebx\n";		\
				 *out << "pop eax\n";		\
				 *out << "add eax, ebx\n";	\
				 *out << "push eax\n";		

#define GEN_MINUS *out << "pop ebx\n";		\
				  *out << "pop eax\n";		\
				  *out << "sub eax, ebx\n";	\
				  *out << "push eax\n";		

#define GEN_MULT *out << "pop ebx\n";		\
				 *out << "pop eax\n";		\
				 *out << "imul eax, ebx\n";	\
				 *out << "push eax\n";		

#define GEN_DIV  *out << "pop ebx\n";		\
				 *out << "pop eax\n";		\
			     *out << "cdq\n";			\
				 *out << "idiv ebx\n";		\
				 *out << "push eax\n";		

#define GEN_INC *out << "pop eax\n";		\
				*out << "inc eax\n";		\
				*out << "push eax\n";		

#define GEN_DEC	*out << "pop eax\n";		\
				*out << "dec eax\n";		\
				*out << "push eax\n";		

#define GEN_AND *out << "pop ebx\n";		\
				*out << "pop eax\n";		\
				*out << "and eax, ebx\n";	\
				*out << "push eax\n";		 

#define GEN_OR *out << "pop ebx\n";			\
			   *out << "pop eax\n";			\
			   *out << "or eax, ebx\n";		\
		       *out << "push eax\n";		

#define GEN_INV *out << "pop eax\n";	    \
				*out << "not eax\n";		\
				*out << "push eax\n";


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
		void GenerateComparison(int& pos, std::stack<int>& condtion_count_pos, int& condition_count, int& condtion_end);
		bool IsManyConditions(int pos);
	};
}