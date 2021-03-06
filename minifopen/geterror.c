#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>

#define UNICODE
#define _UNICODE

int CDECL MessageBoxPrintf(TCHAR *szCaption, TCHAR * szFormat, ...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;
	
	va_start(pArgList, szFormat);
	
	_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArgList);
	
	va_end(pArgList);
	
	return MessageBox(NULL, szBuffer, szCaption, MB_ICONERROR);
}

/* Display error message text, given an error code.
 * Typically, the parameter passed to this function is retrieved
 * from GetLastError().
 */
void PrintCSBackupAPIErrorMessage(DWORD dwErr)
{

    WCHAR   wszMsgBuff[512];  // Buffer for text.

    DWORD   dwChars;  // Number of chars returned.

    // Try to get the message from the system errors.
    dwChars = FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM |
                             FORMAT_MESSAGE_IGNORE_INSERTS,
                             NULL,
                             dwErr,
                             0,
                             wszMsgBuff,
                             512,
                             NULL );

    if (0 == dwChars)
    {
        // The error code did not exist in the system errors.
        // Try Ntdsbmsg.dll for the error code.

        HINSTANCE hInst;

        // Load the library.
        hInst = LoadLibrary(L"Ntdsbmsg.dll");
        if ( NULL == hInst )
        {
            MessageBoxPrintf(TEXT("Error"), TEXT("cannot load Ntdsbmsg.dll\n"));
            exit(1);  // Could 'return' instead of 'exit'.
        }

        // Try getting message text from ntdsbmsg.
        dwChars = FormatMessage( FORMAT_MESSAGE_FROM_HMODULE |
                                 FORMAT_MESSAGE_IGNORE_INSERTS,
                                 hInst,
                                 dwErr,
                                 0,
                                 wszMsgBuff,
                                 512,
                                 NULL );

        // Free the library.
        FreeLibrary( hInst );

    }

    // Display the error message, or generic text if not found.
    MessageBoxPrintf(TEXT("Error"), TEXT("Error value: %d Message: %s\n"),
            dwErr,
            dwChars ? wszMsgBuff : L"Error message not found." );

}
