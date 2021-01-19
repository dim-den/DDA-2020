#include "In.h"
#include "Error.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

namespace In
{
	IN getin(wchar_t* infile)
	{
		ifstream File(infile);
		if (!File.is_open()) throw ERROR_THROW(110);
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT], ch;
		string str;
		IN in;
		in.size = 0; in.lexems = 0; in.lines = 0; in.ignor = 0; 
		bool str_lit = false;
		while (getline(File, str) && (in.size < IN_MAX_LEN_TEXT))
		{
			size_t str_size = str.size();
			for (size_t i = 0; i < str_size; i++)
			{
				ch = str[i];
				if (in.code[ch] == in.T) { // допустимый символ
					if (str[i] == IN_CODE_QUOTE) {
						if (!str_lit) str_lit = true;
						else str_lit = false;
						text[in.size++] = IN_CODE_QUOTE;
					}
					else if (str[i] != IN_CODE_SPACE) {
						if (is_expr(str[i])) in.lexems++;
						text[in.size++] = ch;
					}
					else if (str_lit || i < str_size - 1 && i > 0 && str[i + 1] != IN_CODE_SPACE && text[in.size - 1] != IN_CODE_ENDL && !is_expr(str[i + 1]) && !is_expr(str[i - 1])) {
						in.lexems++;
						text[in.size++] = IN_CODE_SPACE;
					}
					else in.lexems++;
				}
				else if (in.code[ch] == in.I) { // игнорируемый символ
					in.ignor++;
				}
				else if (in.code[ch] == in.F) { // недопустимый символ
					throw ERROR_THROW_IN(111, ++in.lines, ++i);
				}
				else text[in.size++] = in.code[ch]; // замена на значение в таблице
			}
			in.lexems++;
			text[in.size++] = IN_CODE_SEPARATOR;
			text[in.size++] = IN_CODE_ENDL;
			in.lines++;
		}
		text[in.size - 1] = IN_CODE_NULL;
		in.text = text;
		return in;
	}

	bool is_expr(char symbol) 
	{
		for (short i = 0; i < EXPR_COUNT;i++)
			if (expr[i] == symbol) return true;
		return false;
	}
}