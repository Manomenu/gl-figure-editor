#pragma once
#include "config.h"
#include "figure.h"

class FigureHandler
{
public:
	FigureHandler(GLFWwindow* window);
	~FigureHandler();
	void draw_figures();
	void add_figure(const points_t<int>& points);

private:
	std::vector<Figure*> figures;
	GLFWwindow* window;
};

