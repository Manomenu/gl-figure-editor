#pragma once
#include "config.h"
#include "line.h"
#include "distinguished_point.h"

class Figure
{
public:
	Figure(GLFWwindow* window, const points_t<int>& points = {});
	void draw() const;
	void update_last_point(const point<int>& mouse_pos);
	void add_new_point(const point<int>& mouse_pos);
	bool finished() const { return is_finished; }

private:
	GLFWwindow* window;
	points_t<int> points;
	std::unique_ptr<DistinguishedPoint> start_point;
	std::unique_ptr<DistinguishedPoint> end_point;
	std::vector<std::unique_ptr<Line>> lines;
	bool is_finished;
};

