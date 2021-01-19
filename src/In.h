#pragma once
#define IN_MAX_LEN_TEXT 1024*1024 // максмиальный размер исходного кода (1МБ)
#define IN_CODE_ENDL '\n' 
#define IN_CODE_NULL '\0' 
#define IN_CODE_SEPARATOR '/'
#define IN_CODE_INSTR_SEPARATOR ';'
#define IN_CODE_SPACE ' '
#define IN_CODE_QUOTE '\"'
#define EXPR_COUNT 20
// Таблица проверки входной информации, индекс = код (Windows-1251) символа
// значение IN::F - запрещенный символ, IN::T - разрешенный символ, IN::I - игнорировать (не вводить),
// если 0<= значение < 256 - то вводится данное значение

#define IN_CODE_TABLE {																							\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::I, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
                                                                                                                \
IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, \
IN::T, IN::T, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
                      }

namespace In
{
	struct IN // исходные данные
	{
		enum { T = 1024, F = 2048, I = 4096 };  // T - допустиый символ, F - недопустимый, I - игнорировать, иначе заменить
		int size; // размер исходного кода
		int lexems;
		int lines; // количество строк
		int ignor; // количество проигнорированных символов
		unsigned char* text; // исходный код (Windows - 1251)
		int code[256] = IN_CODE_TABLE; // таблица проверки: T, F, I новые значения
	};
	const char expr[EXPR_COUNT] = { ';', '(', ')', ',' , '=', '{', '}', '+','-','*','/', '<', '>', '!', '&', '|', '~', '[', ']' , '.' };

	IN getin(wchar_t* infile); // ввод и проверка входного потока
	bool is_expr(char symbol);
};