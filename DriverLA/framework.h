#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files

#include <vector>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <windows.h>

#ifdef DRIVERLA_EXPORTS
#define DRIVERLA_API __declspec(dllexport)
#define EXTSPEC_TEMPLATE
#else
#define DRIVERLA_API __declspec(dllimport)
#define EXTSPEC_TEMPLATE extern
#endif //DRIVERLA_EXPORTS

struct DRIVERLA_API std::_Container_base12;
EXTSPEC_TEMPLATE template struct DRIVERLA_API std::_Simple_types<std::int8_t>;
EXTSPEC_TEMPLATE template class DRIVERLA_API std::_Vector_val<std::_Simple_types<std::int8_t>>;
EXTSPEC_TEMPLATE template class DRIVERLA_API std::_Compressed_pair<std::allocator<std::int8_t>, std::_Vector_val<std::_Simple_types<std::int8_t>>, true>;
EXTSPEC_TEMPLATE template class DRIVERLA_API std::vector<std::int8_t>;
EXTSPEC_TEMPLATE template struct DRIVERLA_API std::pair<std::vector<std::int8_t>&&, std::vector<std::int8_t>&&>;