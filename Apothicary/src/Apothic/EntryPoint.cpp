#pragma once
#include <iostream>
#include "Application.h"

#ifdef AP_PLATFORM_WINDOWS
extern apothic::Application* apothic::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "----- Apothicary -----" << std::endl;
	apothic::Application* app = apothic::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif