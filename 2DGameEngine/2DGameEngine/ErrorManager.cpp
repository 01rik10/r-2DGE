#include "ErrorManager.h"

void ErrorManager::error(const std::string& error)
{
	std::cout << error << std::endl;
	std::cout << "Exiting window" << std::endl;
}
