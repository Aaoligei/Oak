#pragma once

#ifdef OAK_PLATFORM_WINDOWS

extern Oak::Application* Oak::CreateApplication();

int main(int argc,char** argv) {
	Oak::Log::Init();
	OAK_CORE_WRAN("Initialized Log!");
	OAK_INFO("Initialized Log!");

	auto app = Oak::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
