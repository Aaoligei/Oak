#pragma once

#ifdef  OAK_PLATFORM_WINDOWS
	#ifdef OAK_BUILD_DLL
		#define OAK_API __declspec(dllexport)
	#else
		#define OAK_API __declspec(dllimport)
	#endif // OAK_BUILD_DLL
#else
	#error Oak only supports Windows!
#endif //  OAK_PLATFORM_WINDOWS

#define BIT(x) (1 << x)