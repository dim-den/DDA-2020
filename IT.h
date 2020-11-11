#pragma once
#include <cstring>
#include "Error.h"

#define ID_MAXSIZE			16
#define TI_MAXSIZE			4096
#define TI_INT_DEFAULT		0x00000000
#define TI_STR_DEFAULT		0x00
#define TI_UBYTE_DEFAULT	0x00
#define TI_BOOL_DEFAULT		0x00
#define TI_NULLIDX			0xfffffff
#define TI_STR_MAXSIZE		255
#define TI_LIBRARYSIZE		2

namespace IT // ������� ���������������
{
	enum IDDATATYPE // ���� ������ ���������������
	{
		NONE = 0,		
		NUMB = 1,
		STR = 2,
		UBYTE = 3,
		BOOL = 4
	};

	enum IDTYPE // ��� ��������������
	{
		N = 0,
		V = 1,	// ����������
		F = 2,	// �������
		P = 3,	// ��������
		L = 4	// �������
	};

	struct Entry // ������ ������� ��������������
	{
		int			idxfirstLE;		// ������ ������ ������ � ������� ������
		char		id[ID_MAXSIZE]; // �������������
		char		spacename[ID_MAXSIZE]; 
		IDDATATYPE	iddatatype;
		IDTYPE		idtype;
		union
		{
			int vint;	// number
			struct		// string
			{
				unsigned char len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
			unsigned char vubyte;
			bool vbool;
		} value;					// �������� ��������������
	};



	class IdTable
	{
	public:
		IdTable() : maxsize(TI_MAXSIZE), size(0) {}
		IdTable(int size);
		int Add(Entry entry);
		Entry& GetEntry(int n);
		int IsId(char id[ID_MAXSIZE], char spacename[ID_MAXSIZE]);
		int Size() const;
		~IdTable();

	private:
		const int maxsize;
		int size;
		Entry* table = nullptr; // ������ ����� ������� ���������������
	};

}