/* ////////////////////////////////////////////////////////////

File Name: fslazywindow.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include <fssimplewindow.h>

#include "../fslazywindow.h"


static void IntervalCallBack(void *)
{
	auto appPtr=FsLazyWindowApplicationBase::GetApplication();
	if(nullptr!=appPtr)
	{
		appPtr->Interval();
	}
}

static void NeedRedrawCallBack(void *)
{
	auto appPtr=FsLazyWindowApplicationBase::GetApplication();
	if(nullptr!=appPtr)
	{
		appPtr->Draw();
	}
}

static bool UserWantToCloseProgram(void *)
{
	auto appPtr=FsLazyWindowApplicationBase::GetApplication();
	if(nullptr!=appPtr)
	{
		if(true==FsLazyWindowApplicationBase::GetApplication()->UserWantToCloseProgram())
		{
			FsLazyWindowApplicationBase::GetApplication()->BeforeTerminate();
			return true;
		}
		else
		{
			return false;
		}
	}
}

int main(int ac,char *av[])
{
	FsLazyWindowApplicationBase::GetApplication()->BeforeEverything(ac,av);

	FsOpenWindowOption owo;
	owo.useDoubleBuffer=true;
	FsLazyWindowApplicationBase::GetApplication()->GetOpenWindowOption(owo);

	FsOpenWindow(owo);
	FsLazyWindowApplicationBase::GetApplication()->Initialize(ac,av);


	// Memo: Don't register call backs before Initialize.
	//       Some of the call-back functions may be accidentally fired from inside FsOpenWindow.
	FsRegisterIntervalCallBack(IntervalCallBack,nullptr);
	FsRegisterOnPaintCallBack(NeedRedrawCallBack,nullptr);
	FsRegisterCloseWindowCallBack(UserWantToCloseProgram,nullptr);


	auto t0=FsSubSecondTimer();
	while(0!=FsCheckWindowOpen() &&
	      true!=FsLazyWindowApplicationBase::GetApplication()->MustTerminate())
	{
		auto t=FsSubSecondTimer();
		auto passed=t-t0;
		t0=t;

		FsPollDevice();
		FsLazyWindowApplicationBase::GetApplication()->Interval();

		if(0!=FsCheckWindowExposure() ||
		   true==FsLazyWindowApplicationBase::GetApplication()->NeedRedraw())
		{
			FsLazyWindowApplicationBase::GetApplication()->Draw();
		}

		auto sleepMS=FsLazyWindowApplicationBase::GetApplication()->GetMinimumSleepPerInterval();
		if(sleepMS>passed)
		{
			FsSleep(sleepMS-(int)passed);
		}
	}

	FsLazyWindowApplicationBase::GetApplication()->BeforeTerminate();

	FsCloseWindow();

	return 0;
}

#ifdef _WIN32
// Infamouse WinMain function.  This function will be used when SUBSYSTEM is set to WINDOWS.
#include <windows.h>
int PASCAL WinMain(HINSTANCE inst,HINSTANCE,LPSTR param,int)
{
	char *argv[]=
	{
		"something.exe",
		param
	};
	return main(2,argv);
}
#endif

