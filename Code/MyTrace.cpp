// MyTrace.cpp

#include "stdafx.h"

#include "MyTrace.h"

#ifdef _DEBUG

static LPCTSTR MyLevel[10] =
{
	_T("|"),
	_T("| |"),
	_T("| | |"),
	_T("| | |"),
	_T("| | | |"),
	_T("| | | | |"),
	_T("| | | | | |"),
	_T("| | | | | | |"),
	_T("| | | | | | | |"),
	_T("| | | | | | | |"),
};
static TCHAR MyTraceBuffer[512];
static int MyTraceLevel;
void MyTrace(int nLevel, LPCTSTR pFmt, ...)
{
	va_list ap;
	va_start( ap,pFmt );
	_vsntprintf(MyTraceBuffer,512,pFmt,ap);
	va_end(ap);

	if( nLevel > 0 )
		TRACE(_T("%s-> %s"),MyLevel[MyTraceLevel],MyTraceBuffer);
	else if( nLevel < 0 && MyTraceLevel > 0 )
		TRACE(_T("%s<- %s"),MyLevel[MyTraceLevel-1],MyTraceBuffer);
	else
		TRACE(_T("%s   %s"),MyLevel[MyTraceLevel],MyTraceBuffer);

	MyTraceLevel += nLevel;
	if( MyTraceLevel < 0 )
		MyTraceLevel = 0;
	else if( MyTraceLevel >= 10 )
		MyTraceLevel = 9;
}

MEMORY_BASIC_INFORMATION _mbi_;
void MyTraceSEH(PEXCEPTION_RECORD per)
{
	MYTRACE(0,_T("ExceptionCode            = 0x%p\n"),per->ExceptionCode);
	MYTRACE(0,_T("ExceptionFlags           = 0x%p\n"),per->ExceptionFlags);
	MYTRACE(0,_T("ExceptionAddress         = 0x%p\n"),per->ExceptionAddress);
	MYTRACE(0,_T("NumberParameters         = 0x%p\n"),per->NumberParameters);
	for( DWORD i = 0; i < per->NumberParameters; ++i )
	{
		MYTRACE(0,_T("ExceptionInformation[%d]  = 0x%p\n"),i,per->ExceptionInformation[i]);
	}
	if( per->NumberParameters > 1 )
	{
		MYTRACE(0,_T("Attempt to %s data at address %p\n"),
			per->ExceptionInformation[0] ? _T("WRITE") : _T("READ"),
			per->ExceptionInformation[1]);
		DWORD dwRet = VirtualQuery(
			(LPCVOID)(per->ExceptionInformation[1]),
			&_mbi_, sizeof(_mbi_));
		if( dwRet == sizeof(_mbi_) )
		{
			MYTRACE(0,_T("BaseAddress       = %p\n"),_mbi_.BaseAddress);
			MYTRACE(0,_T("AllocationBase    = %p\n"),_mbi_.AllocationBase);
			switch( _mbi_.AllocationProtect )
			{
			case PAGE_READONLY:
				MYTRACE(0,_T("AllocationProtect = PAGE_READONLY\n"));
				MYTRACE(0,_T("\"Attempts to write to or execut code in this page\n"));
				MYTRACE(0,_T("raize an acess violation.\"\n"));
				break;
			case PAGE_READWRITE:
				MYTRACE(0,_T("AllocationProtect = PAGE_READWRITE\n"));
				MYTRACE(0,_T("\"Attemps to execute code in this page raise an acess\n"));
				MYTRACE(0,_T("violation.\"\n"));
				break;
			case PAGE_WRITECOPY:
				MYTRACE(0,_T("AllocationProtect = PAGE_WRITECOPY\n"));
				MYTRACE(0,_T("Attemps to execute code in this page raise an access\n"));
				MYTRACE(0,_T("violation. Attempts to write to memory in this page\n"));
				MYTRACE(0,_T("cause the system to give the process its own private\n"));
				MYTRACE(0,_T("copy of the page (backed byt the paging file).\"\n"));
				break;
			case PAGE_EXECUTE:
				MYTRACE(0,_T("AllocationProtect = PAGE_EXECUTE\n"));
				MYTRACE(0,_T("\"Attempts to read or write memory in this page raise\n"));
				MYTRACE(0,_T("an access violation.\"\n"));
				break;
			case PAGE_EXECUTE_READ:
				MYTRACE(0,_T("AllocationProtect = PAGE_EXECUTE_READ\n"));
				MYTRACE(0,_T("\"Attemps to write to memory in this page raise an\n"));
				MYTRACE(0,_T("access violation.\"\n"));
				break;
			case PAGE_EXECUTE_READWRITE:
				MYTRACE(0,_T("AllocationProtect = PAGE_EXECUTE_READWRITE\n"));
				MYTRACE(0,_T("\"There is nothin you can do to this page to raise an\n"));
				MYTRACE(0,_T("access violation.\"\n"));
				break;
			case PAGE_EXECUTE_WRITECOPY:
				MYTRACE(0,_T("AllocationProtect = PAGE_EXECUTE_WRITECOPY\n"));
				MYTRACE(0,_T("\"There is nothing you can do to this region to raise an\n"));
				MYTRACE(0,_T("access violation. Attempt to write to memory in this\n"));
				MYTRACE(0,_T("page cause the system to give the process its own\n"));
				MYTRACE(0,_T("private copy of the page (backed by the paging file).\"\n"));
				break;
			case PAGE_GUARD:
				MYTRACE(0,_T("AllocationProtect = PAGE_GUARD\n"));
				break;
			case PAGE_NOACCESS:
				MYTRACE(0,_T("AllocationProtect = PAGE_NOACCESS\n"));
				MYTRACE(0,_T("\"Attempts to read from, writ to, or excute code in\n"));
				MYTRACE(0,_T("this page raise an access violation.\"\n"));
				break;
			case PAGE_NOCACHE:
				MYTRACE(0,_T("AllocationProtect = PAGE_NOCACHE\n"));
				break;
			}
			MYTRACE(0,_T("RegionSize        = %d\n"),_mbi_.RegionSize);
			switch( _mbi_.State )
			{
			case MEM_COMMIT:
					MYTRACE(0,_T("State             = MEM_COMMIT\n"));
					break;
			case MEM_FREE:
					MYTRACE(0,_T("State             = MEM_FREE\n"));
					break;
			case MEM_RESERVE:
					MYTRACE(0,_T("State             = MEM_RESERVE\n"));
					break;
			}
			MYTRACE(0,_T("Protect           = %d\n"),_mbi_.Protect);
			switch( _mbi_.Type )
			{
			case MEM_IMAGE:
				MYTRACE(0,_T("Type              = MEM_IMAGE\n"),_mbi_.Type);
				break;
			case MEM_MAPPED:
				MYTRACE(0,_T("Type              = MEM_MAPPED\n"),_mbi_.Type);
				break;
			case MEM_PRIVATE:
				MYTRACE(0,_T("Type              = MEM_PRIVATE\n"),_mbi_.Type);
				break;
			}
		}
	}
}

#else

void MyTrace(int /*nLevel*/, LPCTSTR /*pFmt*/, ...) {}
void MyTraceSEH(PEXCEPTION_RECORD /*per*/) {}

#endif
