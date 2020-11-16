#pragma once
#define ERROR_THROW(id) Error::geterror(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l, c )
#define ERROR_THROW_L(id, l) Error::geterrorl(id, l)
#define ERROR_ENTRY(id, m) {id, m, {-1, -1}} 
#define ERROR_MAXSIZE_MESSAGE 200 
#define ERROR_ENTRY_NODEF(id) ERROR_ENTRY(-id, "�������������� ������") 
// ERROR_ENTRY_NODEF10(id) - 10 �������������� ��������� ������� ������
#define ERROR_ENTRY_NODEF10(id) ERROR_ENTRY_NODEF(id+0), ERROR_ENTRY_NODEF(id+1), ERROR_ENTRY_NODEF(id+2), ERROR_ENTRY_NODEF(id+3), \
                                ERROR_ENTRY_NODEF(id+4), ERROR_ENTRY_NODEF(id+5), ERROR_ENTRY_NODEF(id+6), ERROR_ENTRY_NODEF(id+7), \
                                ERROR_ENTRY_NODEF(id+8), ERROR_ENTRY_NODEF(id+9)
// ERROR_ENTRY_NODEF100(id) - 100
#define ERROR_ENTRY_NODEF100(id) ERROR_ENTRY_NODEF10(id+0),  ERROR_ENTRY_NODEF10(id+10), ERROR_ENTRY_NODEF10(id+20), ERROR_ENTRY_NODEF10(id+30), \
                                 ERROR_ENTRY_NODEF10(id+40), ERROR_ENTRY_NODEF10(id+50), ERROR_ENTRY_NODEF10(id+60), ERROR_ENTRY_NODEF10(id+70), \
                                 ERROR_ENTRY_NODEF10(id+80), ERROR_ENTRY_NODEF10(id+90)
#define ERROR_MAX_ENTRY 1000
namespace Error
{
	struct ERROR // ��� ���������� ��� throw ERROR_THROW 
	{
		int id; // ��� ������
		char message[ERROR_MAXSIZE_MESSAGE]; // ��������� �� ������
		struct IN // ���������� ��� ������, ��� ��������� ������
		{
			int line; // ����� ������
			int col; // ����� �������
		} inext;
	};

	ERROR geterror(int id); // ������������ ERROR ��� ERROR_THROW
	ERROR geterrorl(int id, int line); // ������������ ERROR ��� ERROR_THROW_L
	ERROR geterrorin(int id, int line, int col); // ������������ ERROR ��� ERROR_THROW_IN

};