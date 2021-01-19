#pragma once
#include <wchar.h>
#include <iostream>
#include "tchar.h"
#include "Error.h"

#define PARM_IN L"-in:"
#define PARM_OUT L"-out:"
#define PARM_LOG L"-log:"
#define PARM_DEBUG L"-debug"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT L".asm"
#define PARM_LOG_DEFAULT_EXT L".log"

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};

	static class GetParm
	{
	public:
		static PARM parm(int argc, wchar_t* argv[]);
	private:
		static wchar_t* setparm(wchar_t parm_in[300], wchar_t* default_ext);
		static wchar_t* setparm(wchar_t* argv, size_t skip);
	};

}