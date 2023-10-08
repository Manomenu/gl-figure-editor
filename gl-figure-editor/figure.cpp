#include "figure.h"

Figure::Figure(GLFWwindow* window ,const points_t<int>& points)
{
	if (points.size() == 1 || points.size() == 2)
		throw std::invalid_argument("Invalid amout of arguments.");
	else if (points.size() == 0)
		is_finished = false;
	else
		is_finished = true;
	this->points = points;
	lines = std::vector<Line*>();
	for (uint i = 1; i < points.size(); ++i)
	{
		lines.push_back(new Line(window, points[i - 1], points[i]));

	}
	if (is_finished)
		lines.push_back(new Line(window, points[points.size() - 1], points[0]));
}

void Figure::draw() const
{
	if (!is_finished)
	{
		// draw a dot at the first point
	}
	for (uint i = 0; i < lines.size(); ++i)
		lines[i]->draw();
}




