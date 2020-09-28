#include "IncludeOgl.h"
#include "includeExample.h"
#include "ProgramDirectory.h"

int main()
{
	auto modulepath = CProgramDirectory::GetModuleDirectory();
	SetCurrentDirectory(modulepath.c_str());

	GlfwShadow example;
	return example.main();
}