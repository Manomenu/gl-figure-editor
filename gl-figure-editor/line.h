#pragma once
#include "config.h"

struct Line
{
public:
	Line(GLFWwindow* window, const point<int>& start, const point<int>& end);
	~Line();
	void draw() const;
	void update_end(const point<int>& mouse_pos);

private:
	void bresenham_line_alg();

	point<int> start, end;
	points_t<float> line_points;
	uint lineVAO, lineVBO;
	GLFWwindow* window;
};

