#include "GRB.h"

#define GRB_ERRORS_SERIES 600

#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)

namespace GRB
{

	Greibach greibach(
		NS('S'), TS('$'),
		17,
		Rule(NS('S'), GRB_ERRORS_SERIES + 0,	// стартовый символ
			3,
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), NS('P'), TS('>'), TS('r'), NS('E'), TS(';'), NS('S')),
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'))
		),
		Rule(NS('N'), GRB_ERRORS_SERIES + 1,	// последовательность операторов программы
			20,
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('i'), NS('D'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), NS('D'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), NS('K'), TS(';'), NS('N')),
			Rule::Chain(3, TS('i'), NS('K'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('g'), TS('i'), TS(';')),
			Rule::Chain(4, TS('g'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(3, TS('?'), NS('C'), NS('O')),
			Rule::Chain(9, TS('&'), TS('i'), TS('j'), NS('R'), TS('.'), NS('R'), TS('s'), NS('Q'), NS('B')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('u'), TS('i'), TS(';')),
			Rule::Chain(4, TS('u'), TS('i'), TS(';'), NS('N'))
		),
		Rule(NS('E'), GRB_ERRORS_SERIES + 2,	// выражение
			14,
			Rule::Chain(1, TS('i')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(2, TS('i'), NS('D')),
			Rule::Chain(3, TS('i'), NS('D'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(2, TS('i'), NS('K')),
			Rule::Chain(3, TS('i'), NS('K'), NS('M')),
			Rule::Chain(2, TS('u'), TS('i')),
			Rule::Chain(3, TS('u'), TS('i'), NS('M')),	
			Rule::Chain(2, TS('u'), TS('l')),
			Rule::Chain(3, TS('u'), TS('l'), NS('M'))
		),
		Rule(NS('P'), GRB_ERRORS_SERIES + 3,	// блок параметра функций
			2,
			Rule::Chain(3, TS('('), NS('F'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(NS('K'), GRB_ERRORS_SERIES + 4,	// параметры вызываемой функции
			2,
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(NS('F'), GRB_ERRORS_SERIES + 3,	// параметры функции
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERRORS_SERIES + 4,	// подвыражение
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('M'), GRB_ERRORS_SERIES + 5,	// операции языка
			4,
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M')),
			Rule::Chain(2, TS('b'), NS('E')),
			Rule::Chain(2, TS('b'), NS('E'), NS('M'))
		),
		Rule(NS('C'), GRB_ERRORS_SERIES + 6,	// условие
			4,
			Rule::Chain(6, TS('('), NS('E'), TS('c'), NS('E'), NS('C'), TS(')')),
			Rule::Chain(5, TS('('), NS('E'), TS('c'), NS('E'), TS(')')),
			Rule::Chain(4, TS('z'), NS('E'), TS('c'), NS('E')),
			Rule::Chain(5, TS('z'), NS('E'), TS('c'), NS('E'), NS('C'))

		),
		Rule(NS('I'), GRB_ERRORS_SERIES + 7,	// условная конструкция
			2,
			Rule::Chain(3, TS('o'), NS('C'), NS('O')),
			Rule::Chain(2, TS('e'), NS('O'))
		),
		Rule(NS('O'), GRB_ERRORS_SERIES + 7,	// блок операторов условия
			5,
			Rule::Chain(4, TS('{'), NS('N'), TS('}'), NS('I')),
			Rule::Chain(3, TS('{'), NS('N'), NS('G')),
			Rule::Chain(3, TS('>'), NS('Y'), NS('I')),
			Rule::Chain(2, TS('>'), NS('Y')),
			Rule::Chain(3, TS('>'), NS('Y'), NS('N'))
		),
		Rule(NS('Y'), GRB_ERRORS_SERIES + 8,	// последовательность операторов одиночного блока условия
			5,
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('g'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(3, TS('i'), NS('K'), TS(';'))
		),
		Rule(NS('D'), GRB_ERRORS_SERIES + 9,	// индекс
			2,
			Rule::Chain(3, TS('['), TS('i'), TS(']')),
			Rule::Chain(3, TS('['), TS('l'), TS(']'))
		),
		Rule(NS('R'), GRB_ERRORS_SERIES + 10,	// аргументы диапазона цикла
			2,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),
		Rule(NS('Q'), GRB_ERRORS_SERIES + 11,	// шаг цикла
			2,
			Rule::Chain(3, TS('i'), TS('='), NS('E')),
			Rule::Chain(2, TS('u'), TS('i'))
		),
		Rule(NS('B'), GRB_ERRORS_SERIES + 12,	// тело цикла
			3,
			Rule::Chain(3, TS('{'), NS('N'), NS('G')),
			Rule::Chain(2, TS('>'), NS('Y')),
			Rule::Chain(3, TS('>'), NS('Y'), NS('N'))
		),
		Rule(NS('G'), GRB_ERRORS_SERIES + 13,	// конец блока цикла или условия
			2,
			Rule::Chain(2, TS('}'), NS('N')),
			Rule::Chain(1, TS('}'))
		)
		);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...) : size(psize), nt(new GRBALPHABET[psize])
	{
		int* p = (int*)& s;
		for (int i = 0; i < psize; i++)
			nt[i] = (GRBALPHABET)p[i];
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size;i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) : nn(pnn), iderror(piderror), size(psize), chains(new Chain[psize])
	{
		Chain* p = &c;
		for (int i = 0; i < psize; i++)
			chains[i] = p[i];
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...) : startN(pstartN), stbottomT(pstbottomT), size(psize), rules(new Rule[psize])
	{
		Rule* p = &r;
		for (int i = 0; i < size; i++)
			rules[i] = p[i];
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	};

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn) k++;
		if (k < size) prule = rules[rc = k];
		return rc;
	};

	Greibach getGreibach()
	{
		return greibach;
	}
}