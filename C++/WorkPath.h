#include <iostream>
#ifdef _WIN32
#include <direct.h>
#elif __APPLE__ || __linux__
#include<unistd.h>
#endif
using namespace std;
string getWorkPath()
{
	  char runPath[1024] = {0};
    getcwd(runPath, sizeof(runPath));
    return runPath;
}
