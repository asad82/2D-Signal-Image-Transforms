// MyTrace.h

#ifndef __MYTRACE_H__
#define __MYTRACE_H__

void MyTrace(int nLevel, LPCTSTR pFmt, ...);
void MyTraceSEH(PEXCEPTION_RECORD per);

#define MYGETBOOLSTR(b) (b ? _T("TRUE") : _T("FALSE"))

#ifdef _DEBUG

#define MYTRACE MyTrace
#define MYTRACESEH MyTraceSEH

#else

#define MYTRACE		1 ? ((void)0) : MyTrace
#define MYTRACESEH	1 ? ((void)0) : MyTraceSEH

#endif

#endif // __MYTRACE_H__
