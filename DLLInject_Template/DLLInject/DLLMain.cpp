// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <string>
#include <iostream>
extern int StartStatusWindow();

DWORD WINAPI Main(LPVOID lpParam)
{
	StartStatusWindow();
	return S_OK;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  _reason,
                       LPVOID lpReserved
					  )
{
	if (_reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0x1000, &Main, 0, 0, NULL); 
	}
	return TRUE;
}