#include <stdio.h>
#include <cstring>
#include <WTypes.h>
#include <shlobj.h>
#include <windows.h>
#pragma comment (lib, "urlmon.lib")
#include <iostream>

using namespace std;

string ExePath();       //get current working directory

int main()
{
    char * dwnld_URL = "https://source.unsplash.com/random/1920x1080";
    typedef int * (*URLDownloadToFileA)(void*, char*, char*, DWORD, void*);
    HINSTANCE LibHnd = LoadLibrary("Urlmon.dll");
    URLDownloadToFileA URLDownloadToFile =  (URLDownloadToFileA) GetProcAddress(LibHnd, "URLDownloadToFileA");

    string path = ExePath() + "\\temp.jpg";
    try
    {
        URLDownloadToFile(0, dwnld_URL, "temp.jpg", 0, 0);
        cout << "File Downloaded" << endl;
        cout << path << endl;
        SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)path.c_str() , 3);
        cout << "Wallpaper set" << endl;
    }
    catch(...)
    {
        printf("Error occurred\n");
    }
    char test;
    cout << "Wallpaper is saved as temp.jpg. Do you want to save the wallpaper?(y/n) ";
    cin >> test;
    if(test == 'y' || test == 'Y')
        cout << "Done!" << endl;
    else
    {
        if( remove("temp.jpg") != 0 )
            perror("Error deleting file");
        else
            puts("Temporary file successfully deleted");
    }
    return 0;
}

//current path
string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

// set background
// SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)s.c_str(), SPIF_SENDCHANGE);

//https://www.experts-exchange.com/questions/21690101/What-to-include-for-URLDownloadToFile-New-C-programmer.html
//https://stackoverflow.com/questions/875249/how-to-get-current-directory
