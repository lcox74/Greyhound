#ifndef GREYHOUND_ASSERTS_H_
#define GREYHOUND_ASSERTS_H_

#include <iostream>
#include <windows.h>

#ifdef linux
	#define RESET 	"\033[0m"
	#define BLACK 	"\033[30m"
	#define RED 	"\033[31m"
	#define GREEN 	"\033[32m"
	#define YELLOW 	"\033[33m"
	#define BLUE 	"\033[34m"
	#define MAGENTA "\033[35m"
	#define CYAN 	"\033[36m"
	#define WHITE 	"\033[37m"
#elif _WIN32
	#define BLACK 	 0x0000
	#define BLUE 	 0x0001
	#define GREEN 	 0x0002
	#define CYAN 	 0x0003
	#define RED 	 0x0004
	#define MAGENTA  0x0005
	#define YELLOW 	 0x0006
	#define WHITE 	 0x0007
#endif

#ifndef FATAL_ASSERT
static void _fAssert(bool logic, const char* file, int line, const char* func, const char* errorMess)
{
	if (!logic)
	{
#ifdef _WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		std::cout << "FATAL:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << "\n\tMESS : " << errorMess << std::endl;
#else
		std::cout << RED << "FATAL:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << "\n\tMESS : " << errorMess << RESET << std::endl;
#endif

		std::cout << "Press 'Enter' to continue..." << std::endl;
		std::cin.get();
		exit(0);
	}
}
#endif

#ifndef WARN_ASSERT
static void _wAssert(bool logic, const char* file, int line, const char* func, const char* errorMess)
{
	if (!logic)
	{
#ifdef _WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		std::cout << "WARN:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << "\n\tMESS : " << errorMess << std::endl;
#else
		std::cout << YELLOW << "WARN:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << "\n\tMESS : " << errorMess << RESET << std::endl;
#endif
	}
}
#endif

#ifndef LOG_ASSERT
static void _lAssert(bool logic, const char* file, int line, const char* func, const char* errorMess)
{
	if (!logic)
	{
#ifdef _WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
		std::cout << "LOG:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << "\n\tMESS : " << errorMess << std::endl;
#else
		std::cout << CYAN << "LOG:\n\tFILE : " << file << " \n\tLINE : " << line << " \n\tFUNC : " << func << "\n\tMESS : " << errorMess << RESET << std::endl;
#endif
	}
}
#endif

#define FATAL_ASSERT(logic) _fAssert(logic, __FILE__, __LINE__, __FUNCTION__, "Regular Fatal error Assert")
#define WARN_ASSERT(logic) _wAssert(logic, __FILE__, __LINE__, __FUNCTION__, "Regular Warning Assert")
#define LOG_ASSERT(logic) _lAssert(logic, __FILE__, __LINE__, __FUNCTION__, "Regular Log Assert")

#define FATAL_ASSERT_MESS(logic, mess) _fAssert(logic, __FILE__, __LINE__, __FUNCTION__, mess)
#define WARN_ASSERT_MESS(logic, mess) _wAssert(logic, __FILE__, __LINE__, __FUNCTION__, mess)
#define LOG_ASSERT_MESS(logic, mess) _lAssert(logic, __FILE__, __LINE__, __FUNCTION__, mess)

#endif //GREYHOUND_ASSERTS_H_