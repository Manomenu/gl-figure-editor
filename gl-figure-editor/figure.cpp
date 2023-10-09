#include "figure.h"

Figure::Figure(GLFWwindow* window)
{
	this->window = window;

	point<double> mouse_pos;
	glfwGetCursorPos(window, &mouse_pos.x, &mouse_pos.y);
	
	is_finished = false;
	lines = std::vector<std::unique_ptr<Line>>();
	points = points_t<int>{ { int(mouse_pos.x), int(mouse_pos.y) } };
	start_point = std::make_unique<DistinguishedPoint>(window, points.front());
	end_point = std::make_unique<DistinguishedPoint>(window, points.front());
}

Figure::Figure(GLFWwindow* window, const points_t<int>& points)
{
	if (points.size() < 3)
		throw std::invalid_argument("Invalid amout of points.\n");

	is_finished = true;
	this->points = points;

	lines = std::vector<std::unique_ptr<Line>>();
	for (uint i = 1; i < points.size(); ++i)
		lines.push_back(std::make_unique<Line>(window, points.at(i - 1), points.at(i)));
	lines.push_back(std::make_unique<Line>(window, points.back(), points.front()));
}

void Figure::draw() const
{
	if (!is_finished && !points.empty())
	{
		start_point->draw();
		end_point->draw();
	}
	for (auto const& line : lines)
		line->draw();
}

void Figure::update_last_point(const point<int>& mouse_pos)
{
	points.back() = mouse_pos;
	end_point->update(mouse_pos);
	if (!lines.empty())
		lines.back()->update_end(mouse_pos);
}

void Figure::add_new_point(const point<int>& mouse_pos)
{
	lines.push_back(std::make_unique<Line>(window, points.back(), mouse_pos)); // can crash because initially i will have two points that are equal!, fix it if crashes
	
	// has to be improved, detect that last point is near first one and close the figure!
	points.push_back(mouse_pos); 
	end_point->update(mouse_pos);
}




