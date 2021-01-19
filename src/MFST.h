#pragma once
#include "Error.h"
#include "GRB.h"
#include "LT.h"
#include "Parm.h"
#include <stack>
#include <iomanip>
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

typedef std::stack<short> MFSTSTSTACK;	// стек автомата

#define MFST_TRACE_START if(DEBUG_MODE) std::cout << std::setw(4) << std::setfill(' ') << std::left << "Шаг: " \
								   << std::setw(20) << std::left << " Правило" \
								   << std::setw(30) << std::left << " Входная лента" \
								   << std::setw(20) << std::left << " Стек" \
								   << std::endl;

#define MFST_TRACE1 if(DEBUG_MODE) std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain)  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE2 if(DEBUG_MODE) std::cout << std::setw(4) << std::left << FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE3 if(DEBUG_MODE) std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE4(c) if(DEBUG_MODE) std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " << std::setw(20) << std::left << c << std::endl;
#define MFST_TRACE5(c) if(DEBUG_MODE) std::cout << std::setw(4) << std::left <<   FST_TRACE_n << ": " << std::setw(20) << std::left << c << std::endl;

#define MFST_TRACE6(c,k) if(DEBUG_MODE) std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " << std::setw(20) << std::left << c << k << std::endl;

#define MFST_TRACE7 if(DEBUG_MODE) std::cout << std::setw(4) << std::left << state.lenta_position << ": " \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, state.nrulechain) \
	<< std::endl;

namespace MFST
{
	struct MfstState			// состояние автомата (для сохранения)
	{
		short lenta_position;	// позиция на ленте
		short nrule;			// номер текущего правила
		short nrulechain;		// номер текущей цепочки, текущего правила
		MFSTSTSTACK st;			// стек автомата
		MfstState();
		MfstState(
			short pposition,	// номер текущей позиции
			MFSTSTSTACK pst,	// стек автомата
			short pnrulechain	// номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition,	// номер текущей позиции
			MFSTSTSTACK pst,	// стек автомата
			short pnrule,		// номер текущего правила
			short pnrulechain	// номер текущей цепочки, текущего правила
		);
	};

	struct Mfst
	{
		enum RC_STEP			// код возврата функции step
		{
			NS_OK,				// найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,			// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,		// не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			// неизсвестный нетерминальный символ грамматики
			TS_OK,				// тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,				// тек. символ ленты != вершине стека, восстановление состаяния
			LENTA_END,			// текущая позиция ленты >= lenta_size
			SURPRISE			// неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis			// диагностика
		{
			short lenta_position;		// позиция на ленте
			RC_STEP rc_step;			// код возвращения шага
			short nrule;				// номер правила
			short nrule_chain;			// номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(				// диагностика
				short plenta_position,	// позиция на ленте
				RC_STEP prc_step,		// код возвращения шага
				short pnrule,			// номер правила
				short pnrule_chain		// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];	// последние самые глубокие сообщения

		GRBALPHABET* lenta;					// перекодированная (TS/NS) лента из lex
		short lenta_position;				// текущая позиция на ленте
		short nrule;						// номер текущего правила
		short nrulechain;					// номер текущей цепочки, текущего правила
		short lenta_size;					// размер ленты
		GRB::Greibach greibach;				// грамматика Грейбах
		LT::LexTable lex;					// результат лексического анализа
		MFSTSTSTACK st;						// стек автомата
		std::stack<MfstState> storestate;	// стек для сохранения состояний
		Mfst();
		Mfst(
			LT::LexTable& plex,				// результа лексического анализа
			GRB::Greibach pgreibach			// грамматика Грейбаха
		);
		char* getCSt(char* buf);			// получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);	// лента: n символов с pos
		char* getDiagnosis(short n, char* buf);	 // получить n-ую строку диагностики или 0x00
		bool savestate();					// сохранить состояние автомата
		bool reststate();					// восстановить состояние автомата
		bool push_chain(GRB::Rule::Chain chain); //	поместить цепочку правила в стек
		RC_STEP step();						// выполнить шаг автомата
		bool start();						// запустить автомат
		bool savediagnosis(RC_STEP prc_step);	// сохранить код завершения шага
		void printrules();					// вывысти последовательность правил

		struct Deducation					// вывод
		{
			short size;						// количество шагов в выводе
			short* nrules;					// номер правил грамматики
			short* nrulechains;				// номер цепочек правил грамматики (nrules)
			Deducation() : size(0), nrules(0), nrulechains(0) {}
		} deducation;
		bool savededucation();				// сохранить дерево вывода
	};
}