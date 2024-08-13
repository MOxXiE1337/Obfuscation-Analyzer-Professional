#pragma once

#ifndef FT2_BUILD_LIBRARY
#define FT2_BUILD_LIBRARY
#endif // !FT2_BUILD_LIBRARY


#include "freetype/ft2build.h"
//#include FT_FREETYPE_H 

#include "freetype/freetype.h"




#ifndef AUTO_LIB_ADDER_TYLPE
#	ifdef _WIN64
#		define AUTO_LIB_ADDER_TYLPE "_x64"
#	else
#		define AUTO_LIB_ADDER_TYLPE "_x86"
#	endif // _WIN64
#endif //AUTO_LIB_ADDER_TYLPE

#ifndef AUTO_LIB_RUNTIME_TYLPE
#	ifdef _DEBUG
#		define AUTO_LIB_RUNTIME_TYLPE "_Debug"
#	else
#		define AUTO_LIB_RUNTIME_TYLPE "_Release"
#	endif // _DEBUG
#endif //AUTO_LIB_RUNTIME_TYLPE

#ifndef AUTO_IMPORT_LIB_SUFFIX
#	define AUTO_IMPORT_LIB_SUFFIX(name) #name AUTO_LIB_ADDER_TYLPE AUTO_LIB_RUNTIME_TYLPE ".lib"
#endif

#pragma comment(lib,AUTO_IMPORT_LIB_SUFFIX(freetype))


