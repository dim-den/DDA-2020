#include "FST.h"
#include "In.h"
#include "Error.h"

using namespace std;
namespace Fst
{
	RELATION::RELATION(char c, short nn) 
	{
		symbol = c;
		nnode = nn;
	};

	NODE::NODE() 
	{
		n_relation = 0;
		RELATION* relations = nullptr;
	};

	NODE::NODE(short n, RELATION rel, ...) 
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (int i = 0; i < n; i++)
			relations[i] = p[i];
	};

	FST::FST(char* s, short ns, NODE n, ...) 
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int i = 0; i < ns; i++) nodes[i] = p[i];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;


	}

	FST::FST(short ns, NODE n, ...) 
	{
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int i = 0; i < ns; i++) nodes[i] = p[i];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	}

	bool step(FST& fst, short* rstates) 
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (int j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				};
		};
		return rc;
	};

	int execute(FST& fst) 
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		}
		if (fst.position < 1) fst.position = 1;

		return (rc ? fst.rstates[fst.nstates - 1] == lstring ? 0 : fst.position : fst.position);
	}

	NODE CreateNode(avail_symbols as) 
	{
		Fst::NODE p;
		short node1 = 1, node2 = 2;
		const int eng_size = 26, rus_size = 33, numb_size = 10;
		const int  punctuations_size = 10;
		const char punctuations[punctuations_size] = { ',', '!', '?', ':', '-', '.', '_', '\'', '/', ' ' };
		const int arifmetic_size = 2;
		const char arifmetic[arifmetic_size] = { '+', '-' };
		if (!as.str_lit && !as.ubt_lit) {
			node1 = 0; node2 = 1;
		}

		int relations = as.low_eng * eng_size + as.upp_eng * eng_size + as.low_rus * rus_size + as.upp_rus * rus_size + as.numbers * numb_size + as.str_lit * punctuations_size + +as.ubt_lit * punctuations_size;
		if (!as.str_lit && as.numbers) relations += arifmetic_size;
		if (!as.ubt_lit) relations *= 2;
		p.relations = new Fst::RELATION[relations];
		p.n_relation = relations;

		int size = 0;

		auto add_range = [&p, node1, node2, &size, &as](int first, int last = ' ') {
			for (int i = first; i <= last; i++) {
				p.relations[size++] = { (char)i, node2 };
				if(!as.ubt_lit) p.relations[size++] = { (char)i, node1 };
			};
		};

		if (as.low_eng) add_range('a', 'z');
		if (as.upp_eng) add_range('A', 'Z');
		if (as.low_rus) add_range('а', 'я');
		if (as.upp_rus) add_range('А', 'Я');
		if (as.numbers) add_range('0', '9');
		if (as.str_lit || as.ubt_lit) 
			for (int i = 0; i < punctuations_size;i++)
			{
				p.relations[size++] = { (char)punctuations[i], node2 };
				if (!as.ubt_lit) p.relations[size++] = { (char)punctuations[i], node1 };
			}
		if (!as.str_lit && as.numbers) 
			for (int i = 0; i < arifmetic_size;i++)
			{
				p.relations[size++] = { (char)arifmetic[i], node2 };
				if (!as.ubt_lit) p.relations[size++] = { (char)arifmetic[i], node1 };
			}
		return p;
	}
}