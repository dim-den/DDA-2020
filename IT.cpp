#include "IT.h"
#include "LT.h"

namespace IT
{

	Entry default_library[TI_LIBRARYSIZE] =
	{
		{ -1, "strconcat", LEX_GLOBAL, IT::IDDATATYPE::STR, IT::IDTYPE::F, TI_STR_DEFAULT },
		{ -2, "strcopy", LEX_GLOBAL, IT::IDDATATYPE::BOOL, IT::IDTYPE::F, TI_BOOL_DEFAULT }
	};

	IdTable::IdTable(int size) : maxsize(size) {
		if (size > TI_MAXSIZE) throw ERROR_THROW(124);
		this->size = 0;		
		table = new Entry[size];
		for (int i = 0; i < TI_LIBRARYSIZE; i++) Add(default_library[i]);
	}

	int IdTable::Add(Entry entry) {
		if (size >= maxsize) throw ERROR_THROW(125);
		table[size++] = entry;
		return size - 1;
	}

	Entry& IdTable::GetEntry(int n) {
		if (n > size) throw ERROR_THROW(126);
		return table[n];
	}

	int IdTable::IsId(char id[ID_MAXSIZE], char spacename[ID_MAXSIZE]) {
		for (int i = 0; i < size; i++) {
			if (std::strcmp(table[i].id, id) == 0 && std::strcmp(table[i].spacename, spacename) == 0) return i;
		}
		return TI_NULLIDX;
	}

	IdTable::~IdTable() {
		if (table != nullptr) {
			delete[] table;
		}
	}

	int IdTable::Size() const {
		return size;
	}
}