#include "IT.h"
#include "LT.h"

namespace IT
{

	STDLib default_library[TI_LIBRARYSIZE] =
	{
		{{ LT_MAXSIZE + 0, "strconcat", LEX_GLOBAL, IT::IDDATATYPE::BOOL, IT::IDTYPE::F, TI_BOOL_DEFAULT } , {STR,STR}},
		{{ LT_MAXSIZE + 1, "strcopy", LEX_GLOBAL, IT::IDDATATYPE::BOOL, IT::IDTYPE::F, TI_BOOL_DEFAULT } , {STR,STR}},
		{{ LT_MAXSIZE + 2, "strlength", LEX_GLOBAL, IT::IDDATATYPE::NUMB, IT::IDTYPE::F, TI_UBYTE_DEFAULT } , {STR}},
		{{ LT_MAXSIZE + 3, "ToNumber", LEX_GLOBAL, IT::IDDATATYPE::NUMB, IT::IDTYPE::F, TI_INT_DEFAULT } , {STR}}
	};

	STDLib* GetSTDLib() {
		return default_library;
	}

	IdTable::IdTable(int size) : maxsize(size + TI_LIBRARYSIZE)
	{
		if (size > TI_MAXSIZE) throw ERROR_THROW(124);
		this->size = 0;		
		table = new Entry[size];
		for (int i = 0; i < TI_LIBRARYSIZE; i++) Add(default_library[i].entry);
	}

	int IdTable::Add(Entry entry) 
	{
		if (size >= maxsize) throw ERROR_THROW(125);
		table[size++] = entry;
		return size - 1;
	}

	Entry& IdTable::GetEntry(int n) const
	{
		if (n > size) throw ERROR_THROW(126);
		return table[n];
	}

	int IdTable::IsId(char id[ID_MAXSIZE], char spacename[ID_MAXSIZE]) const
	{
		for (int i = 0; i < size; i++) {
			if (std::strcmp(table[i].id, id) == 0 && std::strcmp(table[i].spacename, spacename) == 0) return i;
		}
		return TI_NULLIDX;
	}
	IdTable::~IdTable() 
	{
		if (table != nullptr) {
			delete[] table;
		}
	}

	int IdTable::Size() const 
	{
		return size;
	}
}