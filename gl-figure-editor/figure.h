#pragma once
#include "config.h"
#include "line.h"

class Figure
{
public:
	Figure(GLFWwindow* window, const points_t<int>& points = points_t<int>());
	void draw() const;

private:
	points_t<int> points;
	std::vector<Line*> lines;
	bool is_finished;
};

