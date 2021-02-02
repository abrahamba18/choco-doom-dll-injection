#include "CommandWindow.h"

using namespace DLLInject;

int StartStatusWindow()
{
	StatusWindow^ sw = gcnew StatusWindow();
    Application::Run(sw); //Run our New user interface (linking to "User_Interface.h")
	
	return 0;
}