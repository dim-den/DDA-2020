//#pragma once
//#include "LT.h"
//#include "Error.h"
//#include "IT.h"
//#include "Log.h"
//#include "In.h"
//
//#define TEST_LEX_ANALYSIS
//
//#ifdef TEST_LEX_ANALYSIS
//#define TEST_ERROR_120_128
//#define TEST_ERROR_121
//#define TEST_ERROR_122
//#define TEST_ERROR_123
//#define TEST_ERROR_124
//#define TEST_ERROR_125
//#define TEST_ERROR_126
//#define TEST_ERROR_127_132
//#endif // TEST_LEX_ANALYYSIS
//
//#define TEST_PARMS
//
//#ifdef TEST_PARMS
//#define TEST_ERROR_100
//#define TEST_ERROR_104
//#define TEST_ERROR_110
//#define TEST_ERROR_111
//#endif // TEST_PARM
//
//
//namespace Tests
//{
//	void TestLexAnalysis(Log::LOG& testLog);
//	void TestParms(Log::LOG& testLog);
//
//	void TestProgramm()
//	{
//		Log::LOG testLog((wchar_t*)L"testLog.txt");
//		testLog.WriteLog();
//#ifdef TEST_LEX_ANALYSIS
//		TestLexAnalysis(testLog);
//#endif // TEST_LEX_ANALYSIS
//
//
//#ifdef TEST_PARMS
//		TestParms(testLog);
//#endif // TEST_PARMS
//	}
//
//
//	void TestParms(Log::LOG& testLog)
//	{
//
//#ifdef TEST_ERROR_100
//		{
//			int argc = 3;
//			wchar_t* argv[] = { (wchar_t*)L"" , (wchar_t*)L"-out:out.txt" , (wchar_t*)L"-log.log.txt" };
//			try {
//				Parm::getparm(argc, argv);
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_100
//
//#ifdef TEST_ERROR_104
//		{
//			wchar_t arg[PARM_MAX_SIZE + 1] = L"-in:in.txt";
//			for (int i = wcslen(arg); i < PARM_MAX_SIZE + 1; i++)
//				arg[i] = '-';
//			int argc = 2;
//			wchar_t* argv[] = { (wchar_t*)L"" , arg };
//			try {
//				Parm::getparm(argc, argv);
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_104
//
//#ifdef TEST_ERROR_110
//		{
//			try {
//				In::getin((wchar_t*)L"no_file.txt");
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_110
//
//#ifdef TEST_ERROR_111
//		try {
//			In::getin((wchar_t*)L"in.txt");
//		}
//		catch (Error::ERROR e) {
//			testLog.WriteError(e);
//		}
//#endif // TEST_ERROR_111
//
//	}
//
//
//
//	void TestLexAnalysis(Log::LOG& testLog)
//	{
//#ifdef TEST_ERROR_120_128
//		{
//			IT::IdTable ID(10);
//			LT::LexTable LT(10);
//
//			try {
//				LT.LexAnalysis((wchar_t*)L"testOut.txt", ID);
//			}
//			catch (queue<Error::ERROR>& errors) {
//				testLog.WriteErrors(errors);
//			}
//		}
//#endif // TEST_ERROR_120
//
//
//#ifdef TEST_ERROR_121
//		{
//			try {
//				IT::IdTable ID(1);
//				LT::LexTable LT(LT_MAXSIZE + 1);
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_121
//
//
//#ifdef TEST_ERROR_122
//		{
//			try {
//				IT::IdTable ID(1);
//				LT::LexTable LT(1);
//				LT.Add(LT::Entry());
//				LT.Add(LT::Entry());
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_122
//
//
//#ifdef TEST_ERROR_123
//		{
//			try {
//				IT::IdTable ID(1);
//				LT::LexTable LT(3);
//				LT.GetEntry(2);
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_123
//
//#ifdef TEST_ERROR_124
//		{
//			try {
//				IT::IdTable ID(TI_MAXSIZE + 1);
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_124
//
//
//#ifdef TEST_ERROR_125
//		{
//			try {
//				IT::IdTable ID(1);
//				ID.Add(IT::Entry());
//				ID.Add(IT::Entry());
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_125
//
//#ifdef TEST_ERROR_126
//		{
//			try {
//				IT::IdTable ID(3);
//				ID.GetEntry(2);
//			}
//			catch (Error::ERROR e) {
//				testLog.WriteError(e);
//			}
//		}
//#endif // TEST_ERROR_126
//
//#ifdef TEST_ERROR_127_132
//		{
//			IT::IdTable ID(10);
//			LT::LexTable LT(10);
//
//			try {
//				LT.LexAnalysis((wchar_t*)L"testOut2.txt", ID);
//			}
//			catch (queue<Error::ERROR>& errors) {
//				testLog.WriteErrors(errors);
//			}
//		}
//#endif // TEST_ERROR_127-132
//
//
//
//	}
//}