#include "DllLoader.h"
#include <iostream>
#include <windows.h>
using std::cout;

void DllLoader::dllLoader(std::string dllName) {
	testFunc importedFunctionPointer;
	std::string funcName = "TEST"; //default function expected in all dlls

	//loads dll
	HINSTANCE hinstLib = LoadLibraryA(dllName.c_str());

	if (hinstLib)
	{
		//assigning function pointer
		importedFunctionPointer = (testFunc)(GetProcAddress(hinstLib, funcName.c_str()));

		if (importedFunctionPointer)
		{
			cout << "Function Output -->" << importedFunctionPointer();
		}
		else
			cout << "Could Not Load function " << std::endl;
	}
	else
		cout << "Could Not Load DLL " << std::endl;
}
