#include <windows.h> 
#pragma comment(lib, "advapi32.lib") 
  
BOOL ShutdownSystem(LPTSTR lpMsg, bool flag){ 
   HANDLE hToken;              // handle to process token  
   TOKEN_PRIVILEGES tkp;       // pointer to token structure  
  
   BOOL fResult;               // system shutdown flag  
  
   // Get the current process token handle so we can get shutdown  
   // privilege.  
  
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))  
          return FALSE;  
  
   // Get the LUID for shutdown privilege.  
  
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,  
        &tkp.Privileges[0].Luid);  
  
   tkp.PrivilegeCount = 1;  // one privilege to set     
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
  
   // Get shutdown privilege for this process.  
  
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);  
  
   // Cannot test the return value of AdjustTokenPrivileges.  
  
   if (GetLastError() != ERROR_SUCCESS)  
      return FALSE;  
  
   // Display the shutdown dialog box and start the countdown.  
  
   fResult = InitiateSystemShutdown(  
      NULL,    // shut down local computer  
      lpMsg,   // message for user 
      60,      // time-out period, in seconds  
      FALSE,   // ask user to close apps  
      flag);   // reboot after shutdown  
  
   if (!fResult)  
      return FALSE;  
  
   // Disable shutdown privilege.  
  
   tkp.Privileges[0].Attributes = 0;  
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,  
    (PTOKEN_PRIVILEGES) NULL, 0);  
  
   return TRUE;  
} 
