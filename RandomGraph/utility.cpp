#include "utility.h"
#include "randomgraph.h"

#include <stdio.h>
#include <fcntl.h>

#include <iostream>
#include <fstream>
#include <stdarg.h>

// code for showing a console window on windows....
#ifdef _WIN32
using namespace std;

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

/*
 * function : showConsole
 *
 * abstract : This function forces a console window to be displayed in a Windows GUI application.  M$ doesn't
 *            think a console window is useful for debugging, but they are wrong...so we cry havok and let slip
 *            out dogs of war....
 *
 * input    : void
 *
 * output   : void
 *
 * written  : based off  "Adding Console I/O to a Win32 GUI App", Windows Developer Journal, December 1997
 */
void showConsole()
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;

    FILE *fp;

    if(AllocConsole())            // allocate a console for this app
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
        coninfo.dwSize.Y = MAX_CONSOLE_LINES;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

        // redirect unbuffered STDOUT to the console
        lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "w" );
        *stdout = *fp;
        setvbuf( stdout, NULL, _IONBF, 0 );

        // redirect unbuffered STDIN to the console 
        lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "r" );
        *stdin = *fp;
        setvbuf( stdin, NULL, _IONBF, 0 );

        // redirect unbuffered STDERR to the console
        lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "w" );
        *stderr = *fp;
        setvbuf( stderr, NULL, _IONBF, 0 );

        // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
        ios::sync_with_stdio();
    }
}


void hideConsole()
{
    FreeConsole();
}
#else                    // code for running on Linux....

void showConsole() { }
void hideConsole() { }
#endif



/*
 * function :
 *
 * abstract : 
 *
 * input    : lpszFmt -- [in] format string to process the message.  same formatting as used by `printf'
 *            ...     -- [in] variable argument list that contains the values that will be substitued into the format string
 *
 * output   : int, number of character outputted
 *
 * written  : July 2016, G.K.Huber
 */
/*************************************************************************************************************
* Function:  displayMsg
*
* Abstract: This function displays a diagnostic message, in all cases we send it out via a qDebug, so it will
*           be picked up if a debugger is lurking about, and if the user has activated the debugging console, 
*           we also send it out that way.
*           Note, we call vsnprintf with a null destination and a zero for the maximum number of bytes to use
*           in the buffer, that way the return value from vsnprintf will be the required size of the buffer
*           (the return valueaccording to the man page is "The number of characters that would have been
*           written in n had been sufficently large, not counting the null character").
*
* Params  : lpszFmt -- [in] pointer to a null-terminated format string
*           ...     -- [in] variable arguement list
*
* Returns : The number of characters written.
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int displayMsg(const char* lpszFmt, ...)
{
    int   nRet = 0;
    int   cbBytes;
    char*  buf;

    va_list    args;
    va_start(args, lpszFmt);


	// we need some platform specific code here, due to how Linux and Windows differ in handling
	// varargs.  Briefly, on Linux after using `args' once, it may not be in the same state as it
	// was initially.
#ifndef __WIN32
	va_list   args2;
	va_copy(args2, args);
#endif

    // calling vsnprintf with a NULL destination (and 0 max bytes) will cause vsnprintf to
	// return the needed buffer size.  On Linux we most likely mess up the vardic array
    cbBytes = vsnprintf(NULL, 0, lpszFmt, args);
    if(cbBytes > 0)
    {
	  buf = new char[cbBytes + 1];
#ifdef __WIN32
	  nRet = vsprintf(buf, lpszFmt, args);
#else
	  nRet = vsprintf(buf, lpszFmt, args2);
#endif

	  qDebug("%s", buf);

	  if(RandomGraph::getConsoleState())
		printf("%s", buf);

	  delete [] (buf);
    }

    va_end(args);

    return nRet;
}




 

 
