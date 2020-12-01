#pragma once
#define IN_MAX_LEN_TEXT 1024*1024 // ������������ ������ ��������� ���� (1��)
#define IN_CODE_ENDL '\n' 
#define IN_CODE_NULL '\0' 
#define IN_CODE_SEPARATOR '/'
#define IN_CODE_INSTR_SEPARATOR ';'
#define IN_CODE_SPACE ' '
#define IN_CODE_QUOTE '\"'
#define EXPR_COUNT 19
// ������� �������� ������� ����������, ������ = ��� (Windows-1251) �������
// �������� IN::F - ����������� ������, IN::T - ����������� ������, IN::I - ������������ (�� �������),
// ���� 0<= �������� < 256 - �� �������� ������ ��������

#define IN_CODE_TABLE {																							\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::I, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, \
IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, \
                                                                                                                \
IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
                      }

namespace In
{
	struct IN // �������� ������
	{
		enum { T = 1024, F = 2048, I = 4096 };  // T - ��������� ������, F - ������������, I - ������������, ����� ��������
		int size; // ������ ��������� ����
		int lexems;
		int lines; // ���������� �����
		int ignor; // ���������� ����������������� ��������
		unsigned char* text; // �������� ��� (Windows - 1251)
		int code[256] = IN_CODE_TABLE; // ������� ��������: T, F, I ����� ��������
	};
	const char expr[EXPR_COUNT] = { ';', '(', ')', ',' , '=', '{', '}', '+','-','*','/', '<', '>', '!', '&', '|', '~', '[', ']' };

	IN getin(wchar_t* infile); // ���� � �������� �������� ������
	bool is_expr(char symbol);
};