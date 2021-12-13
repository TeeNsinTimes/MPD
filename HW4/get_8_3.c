
// The GetShortPathName() example

#include <stdlib.h> // for MAX_PATH

// windows.h contain other def also, such as stdlib, malloc and tchar...

//#include <windows.h>
#include <fileapi.h>

#include <tchar.h> // for TCHAR

#include <stdio.h>

#include <malloc.h> // malloc()

int main(void) {

    DWORD retval = 0;

// testing Windows XP SP2 path, change accordingly...

// the path and the file are valid...

    LPCWSTR szlongpath = L"E:\\testlong1.txt";

    LPWSTR szshortpath = (LPWSTR) malloc(sizeof(MAX_PATH));

    TCHAR* buffer = MAX_PATH;

    retval = GetShortPathNameW(szlongpath, szshortpath, buffer);
    
    if (retval == 0) {
        printf("GetshortPathName() failed! Error : %d\n", retval);
    }
    else {

// displaying short and long path
        printf("The long path name = %S\n", szlongpath);
    
        printf("The short path name = %S\n", szshortpath);
    
        printf("The buffer length in TCHARs = %d\n", buffer);
    }

    if(szshortpath = NULL) printf("memory freed!\n");
    else free(szshortpath);

    return 0;
}
