#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <optional>

namespace Fst
{
	struct RELATION //ребро:символ -> вершина графа переход КА
	{
		char symbol; //символ перехода
		short nnode; //номер смежной вершины
		RELATION(char c = 0x00, short ns = NULL); // символ перехода, новое состояние
	};

	struct NODE // вершина графа переходов
	{
		short n_relation; // кол-во индицентных ребер
		RELATION* relations; //индецентные ребра
		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST // недетерминированный конечный автомат
	{
		char* string; //цепочка
		short position; //позиция
		short nstates; //кол-во состояний
		NODE* nodes; // граф переходов
		short* rstates; //возможные состояния на данной позиции
		FST(char* s, short ns, NODE n, ...);
		FST(short ns, NODE n, ...);
		FST() = default;
	};

	struct avail_symbols 
	{
		bool low_eng : 1;
		bool upp_eng : 1;
		bool low_rus : 1;
		bool upp_rus : 1;
		bool numbers : 1;
		bool str_lit : 1;
		bool ubt_lit : 1;
	};

	int execute(FST& fst);
	Fst::NODE CreateNode(avail_symbols as);
}