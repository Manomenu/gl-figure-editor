#include "figure_handler.h"

FigureHandler::FigureHandler(GLFWwindow* window)
{
	figures = std::vector<Figure*>();
	this->window = window;
}

FigureHandler::~FigureHandler()
{
	for (Figure* fig : figures)
		delete fig;
}

void FigureHandler::draw_figures()
{
	for (const Figure* fig : figures)
		fig->draw();
}

void FigureHandler::add_figure(const points_t<int>& points)
{
	figures.push_back(new Figure(window, points));
}
