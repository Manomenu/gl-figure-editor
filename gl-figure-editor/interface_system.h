#pragma once
#include "config.h"

class InterfaceSystem
{
public:
	~InterfaceSystem();
	void draw_interface();
	void render();

private:
	bool show_window = true;
	float my_color[4];
};

