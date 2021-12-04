#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 100

void fsize(char *filename);

WIN32_FIND_DATAA fdata;

/* Print info about all subdirs of specified dir
 *      @path - full directory path
 */
static void dirwalk(char *path) {
        char *SubdirPath = malloc(strlen(path));
        sprintf(SubdirPath, "%s\\*", path);
        HANDLE hFind = FindFirstFileA(SubdirPath, &fdata);
        if (hFind == NULL)        
                return;        
        
        // skip .. file
        FindNextFileA(hFind, &fdata);
        
        while (FindNextFileA(hFind, &fdata))
                fsize(fdata.cFileName);
        
        FindClose(hFind);
}

int header_already_printed = 0;
static void printf_file_information(LPBY_HANDLE_FILE_INFORMATION finfo, HANDLE hFile)
{
        char szFilePath[MAX_NAME];
        if (!header_already_printed) {
                printf("Attr\t"
                        "Created\t\t\t"
                        "Size\t"
                        "ID\t\t\t"
                        "Name\n"
                        "----\t"
                        "---------------\t\t"
                        "------\t"
                        "-----------------\t"
                        "-----------------\n");
                header_already_printed = 1;
        }
        
        // print attribute fileld
        DWORD fattr = finfo->dwFileAttributes;
        if (fattr & FILE_ATTRIBUTE_DIRECTORY)
                printf("d");
        else printf("f");
        if (fattr & FILE_ATTRIBUTE_ENCRYPTED)
                printf("e");
        else printf("-");
        if (fattr & FILE_ATTRIBUTE_COMPRESSED)
                printf("a");
        else printf("-");
        if (fattr & FILE_ATTRIBUTE_SYSTEM)
                printf("s\t");
        else printf("-\t");
        
        // print creation time
        FILETIME time = finfo->ftCreationTime;
        SYSTEMTIME stime;
        FileTimeToSystemTime(&time, &stime);
        printf("%02d/%02d/%04d %02d:%02d\t", stime.wDay, stime.wMonth, stime.wYear,
        stime.wHour, stime.wMinute);
        
        // print file size
        uint64_t fsize = finfo->nFileSizeHigh;
        fsize = fsize << (sizeof(DWORD) * 8);
        fsize |= finfo->nFileSizeLow;
        if (fsize < 1<<10)
                printf("%llub\t", fsize);      
        else if (fsize < 1<<20)
                printf("%lluKB\t", fsize / (1<<10));      
        else if (fsize < 1<<30)
                printf("%lluMB\t", fsize / (1<<20));      
        else
                printf("%lluGB\t", fsize / (1<<30));      
        
        // print index
        uint64_t qindex = finfo->nFileIndexHigh;
        qindex = qindex << (sizeof(DWORD) * 8);
        qindex |= finfo->nFileIndexLow;
        printf("%llu\t\t", qindex);
        
        //print name
        GetFinalPathNameByHandleA(hFile, &szFilePath, MAX_NAME, FILE_NAME_NORMALIZED);
        int pos = strlen(szFilePath);        
        while (szFilePath[--pos] != '\\' && szFilePath[pos] != ':' && pos > 0);
        pos++;
        char *ptrName = szFilePath + pos;
        puts(ptrName);
}

void fsize(char *filename)
{       
        HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, 
         NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_BACKUP_SEMANTICS, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
                printf("Error opening file %s\n", filename);
                return 1;
        }
        
        BY_HANDLE_FILE_INFORMATION fileinfo;
        BOOL result =  GetFileInformationByHandle(hFile, &fileinfo);          
        if (result == FALSE) {
                printf("Unable to access file infotmation\n");
                return 1;
        }
        
        if (fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                dirwalk(filename);
        else
                printf_file_information(&fileinfo, hFile);
        
        CloseHandle(hFile);
}

int main(int argc, char *argv[])
{
        if (argc <= 1) {
                puts("Specify at least one parameter");
                return 1;
        }
        
        fsize(argv[1]);
}