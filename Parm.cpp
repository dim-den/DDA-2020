#include "Parm.h"

extern bool DEBUG_MODE;

namespace Parm
{
	PARM GetParm::parm(int argc, wchar_t* argv[])
	{
		PARM parm;

		int posIN = 0, posOUT = 0, posLOG = 0;
		for (int i = 1; i < argc;i++) 
		{
			if (wcsstr(argv[i], PARM_IN) != NULL) posIN = i;
			else if (wcsstr(argv[i], PARM_OUT) != NULL) posOUT = i;
			else if (wcsstr(argv[i], PARM_LOG) != NULL) posLOG = i;
			else if (wcsstr(argv[i], PARM_DEBUG) != NULL) DEBUG_MODE = true;
		}

		if (!posIN) throw ERROR_THROW(100);
		
		wcscpy_s(parm.in, setparm(argv[posIN], wcslen(PARM_IN)));

		if (!posOUT) wcscpy_s(parm.out, setparm(parm.in, (wchar_t*)PARM_OUT_DEFAULT_EXT));
		else wcscpy_s(parm.out, setparm(argv[posOUT], wcslen(PARM_OUT)));

		if (!posLOG) wcscpy_s(parm.log, setparm(parm.in, (wchar_t*)PARM_LOG_DEFAULT_EXT));
		else wcscpy_s(parm.log, setparm(argv[posLOG], wcslen(PARM_LOG)));
				
		return parm;
	}

	wchar_t* GetParm::setparm(wchar_t parm_in[300], wchar_t* default_ext)  //если отстуствует ключ
	{
		wchar_t res[PARM_MAX_SIZE];
		wcscpy_s(res, parm_in);
		wcscat_s(res, default_ext);
		return res;
	}

	wchar_t* GetParm::setparm(wchar_t* argv, size_t skip) //если есть ключ
	{
		wchar_t res[PARM_MAX_SIZE];
		if (wcslen(argv) > PARM_MAX_SIZE) throw ERROR_THROW(104);
		wcscpy_s(res, argv + skip);
		return res;
	}

}