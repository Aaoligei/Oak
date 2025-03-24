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

#ifdef OAK_ENABLE_ASSERTS
#define OAK_ASSERT(x, ...) { if(!(x)) { OAK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define OAK_CORE_ASSERT(x, ...) { if(!(x)) { OAK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define OAK_ASSERT(x, ...)
#define OAK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define OAK_BIND_EVENT_FN(fn) std::bind(&fn,this, std::placeholders::_1)