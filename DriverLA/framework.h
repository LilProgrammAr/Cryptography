#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>


#ifdef DRIVERLA_EXPORTS
#define DRIVERLA_API __declspec(dllexport)
#define EXTSPEC_TEMPLATE
#else
#define DRIVERLA_API __declspec(dllimport)
#define EXTSPEC_TEMPLATE extern
#endif //DRIVERLA_EXPORTS