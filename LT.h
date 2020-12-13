#pragma once
#include "FST.h"
#include "IT.h"
#include "In.h"
#include "Error.h"
#include <queue>
#include <stack>
#include <sstream>
#include <map>
#define LEXEMA_FIXSIZE	1
#define LT_MAXSIZE		4096
#define LT_TI_NULLIDX	0xfffffff
#define LEX_DATA		't'
#define LEX_NUMBER		't'
#define LEX_STRING		't'
#define LEX_UBYTE		't'
#define LEX_BOOL		't'
#define LEX_MAIN		'm'
#define LEX_ID			'i'
#define LEX_LITERAL		'l'
#define LEX_DIG_LITERAL	'l'
#define LEX_UBT_LITERAL	'l'
#define LEX_TRUE        'l'
#define LEX_FALSE       'l'
#define LEX_FUNCTION	'f'
#define LEX_DEF			'd'
#define LEX_RETURN		'r'
#define LEX_PRINT		'p'
#define LEX_GET			'g'
#define LEX_IF		    '?'
#define LEX_ELIF	    'o'
#define LEX_ELSE	    'e'
#define LEX_ASSIGN		'='
#define LEX_SEMICOLON	';'
#define LEX_COMMA		','
#define LEX_LEFTBRACE	'{'
#define LEX_BRACELET	'}'
#define LEX_TO			'>'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_PLUS		'v'
#define LEX_MINUS		'v'
#define LEX_STAR		'v'
#define LEX_ARIFMETIC	'v'
#define LEX_DIRSLASH	'v'
#define LEX_CONDITION	'c'
#define LEX_LESS		'c'
#define LEX_MORE		'c'
#define LEX_LESSEQUAL	'c'
#define LEX_MOREEQUAL	'c'
#define LEX_EQUAL		'c'
#define LEX_NOTEQUAL	'c'
#define LEX_AND			'b'
#define LEX_OR			'b'
#define LEX_UNARY		'u'
#define LEX_INV			'u'
#define LEX_INC			'u'
#define LEX_DEC			'u'
#define LEX_BYTEOP		'b'
#define LEX_COMPOP		'z'
#define LEX_COMP_AND	'z'
#define LEX_COMP_OR		'z'
#define LEX_FOR			'&'
#define LEX_IN			'j'
#define LEX_STEP		's'
#define LEX_DOTES		'.'
#define LEX_QUOTE       '\"'
#define LEX_LEFTBRACKET '['
#define LEX_RIGHTBRACKET ']'
#define LEX_PAD			'_'
#define LEX_FUNC_CALL	'@'
#define LEX_COUNT		50
#define LEX_GLOBAL		"global_"
#define LEX_MAIN_SPACE	"main"



namespace LT // таблица лексем
{
	struct Entry  // строка таблицы лексем
	{
		char lexema;
		int sn;			// номер строки
		union {
			int idxTI;		// индекс в таблице индетификаторов 
			int idxLex;		// индекс лексемы
		};
	};

	class LexTable
	{
	public:
		LexTable() : maxsize(LT_MAXSIZE), size(0) {}
		LexTable(int size);
		void Add(Entry entry);
		Entry& GetEntry(int n) const;
		void LexAnalysis(unsigned char* text, IT::IdTable& ID);																					// обработка входного файлаа и создание таблицы лексем и идентификаторов
		std::vector<std::string> SeparateLexems(std::string& line);																				// разделение элементов языка
		int AddId(IT::IdTable& ID, std::string& input, IT::IDDATATYPE& iddatatype, IT::IDTYPE& idtype, int idx, std::string& space_name);		// добавление элемента в таблицу идентификаторрв
		int AddLit(IT::IdTable& ID, int& lit_count, int idx, int value, std::string& space_name, IT::IDDATATYPE iddatatype, std::string data);
		int LexDefinition(const std::string& input);																							// анализ входной цепочки, возвращает номер элемента, иначе -1
		void PolishNotation(IT::IdTable& ID, int lt_pos, int& func_call_count);																	// построение польской записи для выражения
		void BuildPolish(IT::IdTable& ID, const std::vector<int>& expr_pos);
		int Size() const;
		static bool IsExprEnd(char symb);
		std::vector<int> GetFuncCallPos() const;
		void operator=(const LexTable& rhs);
		~LexTable();

	private:
		int maxsize;
		int size;
		Entry* table = nullptr; // массив строка таблицы лексем

		std::vector<int> func_call_pos;
		std::vector<int> assign_pos;
	
		const char avail_lexems[LEX_COUNT] = 
		{
			LEX_NUMBER, LEX_STRING, LEX_UBYTE, LEX_BOOL, LEX_DEF, LEX_MAIN, LEX_FUNCTION, LEX_RETURN, LEX_PRINT, LEX_GET, LEX_IF, LEX_ELIF, LEX_ELSE,
			LEX_FOR, LEX_IN, LEX_STEP, LEX_LEFTBRACE, LEX_BRACELET, LEX_LEFTHESIS, LEX_RIGHTHESIS, LEX_ASSIGN, LEX_COMMA, LEX_SEMICOLON, LEX_TO, LEX_INC, LEX_DEC, 
			LEX_PLUS, LEX_MINUS, LEX_STAR, LEX_DIRSLASH, LEX_LESS, LEX_MORE, LEX_LESSEQUAL, LEX_MOREEQUAL, LEX_EQUAL, LEX_NOTEQUAL, LEX_AND, LEX_OR, 
			LEX_INV,LEX_LEFTBRACKET,LEX_RIGHTBRACKET, LEX_TRUE, LEX_FALSE, LEX_COMP_AND, LEX_COMP_OR, LEX_DOTES, LEX_UBT_LITERAL, LEX_LITERAL, LEX_DIG_LITERAL, LEX_ID
		};

		const Fst::FST avail_lexems_FST[LEX_COUNT] = // Таблица возможных переходов
		{
		{ // 0. number
			7,
			Fst::NODE(1, Fst::RELATION('n', 1)),
			Fst::NODE(1, Fst::RELATION('u', 2)),
			Fst::NODE(1, Fst::RELATION('m', 3)),
			Fst::NODE(1, Fst::RELATION('b', 4)),
			Fst::NODE(1, Fst::RELATION('e', 5)),
			Fst::NODE(1, Fst::RELATION('r', 6)),
			Fst::NODE()
		},
		{ // 1. string
			7,
			Fst::NODE(1, Fst::RELATION('s', 1)),
			Fst::NODE(1, Fst::RELATION('t', 2)),
			Fst::NODE(1, Fst::RELATION('r', 3)),
			Fst::NODE(1, Fst::RELATION('i', 4)),
			Fst::NODE(1, Fst::RELATION('n', 5)),
			Fst::NODE(1, Fst::RELATION('g', 6)),
			Fst::NODE()
		},
		{ // 2. ubyte
			6,
			Fst::NODE(1, Fst::RELATION('u', 1)),
			Fst::NODE(1, Fst::RELATION('b', 2)),
			Fst::NODE(1, Fst::RELATION('y', 3)),
			Fst::NODE(1, Fst::RELATION('t', 4)),
			Fst::NODE(1, Fst::RELATION('e', 5)),
			Fst::NODE()
		},
		{ // 3. bool
			5,
			Fst::NODE(1, Fst::RELATION('b', 1)),
			Fst::NODE(1, Fst::RELATION('o', 2)),
			Fst::NODE(1, Fst::RELATION('o', 3)),
			Fst::NODE(1, Fst::RELATION('l', 4)),
			Fst::NODE()
		},
		{ // 4. def
			4,
			Fst::NODE(1, Fst::RELATION('d', 1)),
			Fst::NODE(1, Fst::RELATION('e', 2)),
			Fst::NODE(1, Fst::RELATION('f', 3)),
			Fst::NODE()
		},
		{ // 5. main
			5,
			Fst::NODE(1, Fst::RELATION('m', 1)),
			Fst::NODE(1, Fst::RELATION('a', 2)),
			Fst::NODE(1, Fst::RELATION('i', 3)),
			Fst::NODE(1, Fst::RELATION('n', 4)),
			Fst::NODE()
		},
		{ // 6. function
			9,
			Fst::NODE(1, Fst::RELATION('f', 1)),
			Fst::NODE(1, Fst::RELATION('u', 2)),
			Fst::NODE(1, Fst::RELATION('n', 3)),
			Fst::NODE(1, Fst::RELATION('c', 4)),
			Fst::NODE(1, Fst::RELATION('t', 5)),
			Fst::NODE(1, Fst::RELATION('i', 6)),
			Fst::NODE(1, Fst::RELATION('o', 7)),
			Fst::NODE(1, Fst::RELATION('n', 8)),
			Fst::NODE()
		},
		{ // 7. return
			7,
			Fst::NODE(1, Fst::RELATION('r', 1)),
			Fst::NODE(1, Fst::RELATION('e', 2)),
			Fst::NODE(1, Fst::RELATION('t', 3)),
			Fst::NODE(1, Fst::RELATION('u', 4)),
			Fst::NODE(1, Fst::RELATION('r', 5)),
			Fst::NODE(1, Fst::RELATION('n', 6)),
			Fst::NODE()
		},
		{ // 8. print
			6,
			Fst::NODE(1, Fst::RELATION('p', 1)),
			Fst::NODE(1, Fst::RELATION('r', 2)),
			Fst::NODE(1, Fst::RELATION('i', 3)),
			Fst::NODE(1, Fst::RELATION('n', 4)),
			Fst::NODE(1, Fst::RELATION('t', 5)),
			Fst::NODE()
		},
		{ // 9. get
			4,
			Fst::NODE(1, Fst::RELATION('g', 1)),
			Fst::NODE(1, Fst::RELATION('e', 2)),
			Fst::NODE(1, Fst::RELATION('t', 3)),
			Fst::NODE()
		},
		{ // 10. if
			3,
			Fst::NODE(1, Fst::RELATION('i', 1)),
			Fst::NODE(1, Fst::RELATION('f', 2)),
			Fst::NODE()
		},
		{ // 11. elif
			5,
			Fst::NODE(1, Fst::RELATION('e', 1)),
			Fst::NODE(1, Fst::RELATION('l', 2)),
			Fst::NODE(1, Fst::RELATION('i', 3)),
			Fst::NODE(1, Fst::RELATION('f', 4)),
			Fst::NODE()
		},
		{ // 12. else
			5,
			Fst::NODE(1, Fst::RELATION('e', 1)),
			Fst::NODE(1, Fst::RELATION('l', 2)),
			Fst::NODE(1, Fst::RELATION('s', 3)),
			Fst::NODE(1, Fst::RELATION('e', 4)),
			Fst::NODE()
		},
		{ // 13. for
			4,
			Fst::NODE(1, Fst::RELATION('f', 1)),
			Fst::NODE(1, Fst::RELATION('o', 2)),
			Fst::NODE(1, Fst::RELATION('r', 3)),
			Fst::NODE()
		},
		{ // 14. in
			3,
			Fst::NODE(1, Fst::RELATION('i', 1)),
			Fst::NODE(1, Fst::RELATION('n', 2)),
			Fst::NODE()
		},
		{ // 15. step
			5,
			Fst::NODE(1, Fst::RELATION('s', 1)),
			Fst::NODE(1, Fst::RELATION('t', 2)),
			Fst::NODE(1, Fst::RELATION('e', 3)),
			Fst::NODE(1, Fst::RELATION('p', 4)),
			Fst::NODE()
		},
		{ // 16. {
			2,
			Fst::NODE(1,Fst::RELATION('{',1)),
			Fst::NODE()
		},
		{ // 17. }
			2,
			Fst::NODE(1,Fst::RELATION('}',1)),
			Fst::NODE()
		},
		{ // 18. (
			2,
			Fst::NODE(1,Fst::RELATION('(',1)),
			Fst::NODE()
		},
		{ // 19. )
			2,
			Fst::NODE(1,Fst::RELATION(')',1)),
			Fst::NODE()
		},
		{ // 20. =
			2,
			Fst::NODE(1,Fst::RELATION('=',1)),
			Fst::NODE()
		},
		{ // 21. ,
			2,
			Fst::NODE(1,Fst::RELATION(',',1)),
			Fst::NODE()
		},
		{ // 22. ;
			2,
			Fst::NODE(1,Fst::RELATION(';',1)),
			Fst::NODE()
		},
		{ // 23. =>
			3,
			Fst::NODE(1, Fst::RELATION('=', 1)),
			Fst::NODE(1, Fst::RELATION('>', 2)),
			Fst::NODE()
		},
		{ // 24. ++
			3,
			Fst::NODE(1, Fst::RELATION('+', 1)),
			Fst::NODE(1, Fst::RELATION('+', 2)),
			Fst::NODE()
		},
		{ // 25. --
			3,
			Fst::NODE(1, Fst::RELATION('-', 1)),
			Fst::NODE(1, Fst::RELATION('-', 2)),
			Fst::NODE()
		},
		{ // 26. +
			2,
			Fst::NODE(1,Fst::RELATION('+',1)),
			Fst::NODE()
		},
		{ // 27. -
			2,
			Fst::NODE(1,Fst::RELATION('-',1)),
			Fst::NODE()
		},
		{ // 28. *
			2,
			Fst::NODE(1,Fst::RELATION('*',1)),
			Fst::NODE()
		},
		{ // 29. /
			2,
			Fst::NODE(1,Fst::RELATION('/',1)),
			Fst::NODE()
		},
		{ // 30. <
			2,
			Fst::NODE(1, Fst::RELATION('<', 1)),
			Fst::NODE()
		},
		{ // 31. >
			2,
			Fst::NODE(1,Fst::RELATION('>',1)),
			Fst::NODE()
		},
		{ // 32. <=
			3,
			Fst::NODE(1, Fst::RELATION('<', 1)),
			Fst::NODE(1, Fst::RELATION('=', 2)),
			Fst::NODE()
		},
		{ // 33. >=
			3,
			Fst::NODE(1, Fst::RELATION('>',1)),
			Fst::NODE(1, Fst::RELATION('=', 2)),
			Fst::NODE()
		},
		{ // 34. ==
			3,
			Fst::NODE(1, Fst::RELATION('=', 1)),
			Fst::NODE(1, Fst::RELATION('=', 2)),
			Fst::NODE()
		},
		{ // 35. !=
			3,
			Fst::NODE(1,Fst::RELATION('!',1)),
			Fst::NODE(1,Fst::RELATION('=',2)),
			Fst::NODE()
		},
		{ // 36. &
			2,
			Fst::NODE(1, Fst::RELATION('&', 1)),
			Fst::NODE()
		},
		{ // 37. |
			2,
			Fst::NODE(1,Fst::RELATION('|',1)),
			Fst::NODE()
		},
		{ // 38. ~
			2,
			Fst::NODE(1,Fst::RELATION('~',1)),
			Fst::NODE()
		},
		{ // 39. [
			2,
			Fst::NODE(1,Fst::RELATION('[',1)),
			Fst::NODE()
		},
		{ // 40. ]
			2,
			Fst::NODE(1,Fst::RELATION(']',1)),
			Fst::NODE()
		},
		{ // 41. true (bool lit)
			5,
			Fst::NODE(1, Fst::RELATION('t', 1)),
			Fst::NODE(1, Fst::RELATION('r', 2)),
			Fst::NODE(1, Fst::RELATION('u', 3)),
			Fst::NODE(1, Fst::RELATION('e', 4)),
			Fst::NODE()
		},
		{ // 42. false (bool lit)
			6,
			Fst::NODE(1, Fst::RELATION('f', 1)),
			Fst::NODE(1, Fst::RELATION('a', 2)),
			Fst::NODE(1, Fst::RELATION('l', 3)),
			Fst::NODE(1, Fst::RELATION('s', 4)),
			Fst::NODE(1, Fst::RELATION('e', 5)),
			Fst::NODE()
		},
		{ // 43. and
			4,
			Fst::NODE(1, Fst::RELATION('a', 1)),
			Fst::NODE(1, Fst::RELATION('n', 2)),
			Fst::NODE(1, Fst::RELATION('d', 3)),
			Fst::NODE()
		},
		{ // 44. or
			3,
			Fst::NODE(1, Fst::RELATION('o', 1)),
			Fst::NODE(1, Fst::RELATION('r', 2)),
			Fst::NODE()
		},
		{ // 45. ..
			3,
			Fst::NODE(1, Fst::RELATION('.', 1)),
			Fst::NODE(1, Fst::RELATION('.', 2)),
			Fst::NODE()
		},
		{ // 46. ubyte lit
			4,
			Fst::NODE(1, Fst::RELATION('\'', 1)),
			Fst::CreateNode({1,1,1,1,1,0,1}),
			Fst::NODE(1, Fst::RELATION('\'', 3)),
			Fst::NODE()
		},
		{ // 47. string lit
			4,
			Fst::NODE(2, Fst::RELATION('\"', 1), Fst::RELATION('\"', 2)),
			Fst::CreateNode({1,1,1,1,1,1,0}),
			Fst::NODE(1, Fst::RELATION('\"', 3)),
			Fst::NODE()
		},
		{ // 48. digital lit
			2,
			Fst::CreateNode({0,0,0,0,1,0,0}),
			Fst::NODE()
		},
		{ // 49. id
			2,
			Fst::CreateNode({1,1,0,0,0,0,0}),
			Fst::NODE()
		}
		};
	};

	const enum lexem_number 
	{
		lex_number,
		lex_string,
		lex_ubyte,
		lex_bool,
		lex_def,
		lex_main,
		lex_function,
		lex_return,
		lex_print,
		lex_get,
		lex_if,
		lex_elif,
		lex_else,
		lex_for,
		lex_in,
		lex_step,
		lex_leftbrace,
		lex_bracelet,
		lex_lefthesis,
		lex_righthesis,
		lex_assign,
		lex_comma,
		lex_semicolon,
		lex_to,
		lex_inc,
		lex_dec,
		lex_plus,
		lex_minus,
		lex_star,
		lex_dirslash,
		lex_less,
		lex_more,
		lex_lessequal,
		lex_moreequal,
		lex_equal,
		lex_notequal,
		lex_and,
		lex_or,
		lex_inv,
		lex_leftbracket,
		lex_rightbracket,
		lex_true_lit,
		lex_false_lit,
		lex_comp_and,
		lex_comp_or,
		lex_dotes,
		lex_ubyte_lit,
		lex_str_lit,
		lex_dig_lit,
		lex_id,
		lex_func_call,
		lex_pad
	};
}