#include "figure.h"

Figure::Figure(GLFWwindow* window, const points_t<int>& points)
{
	lines = std::vector<std::unique_ptr<Line>>();
	this->points = points;
	this->window = window;

	if (points.size() == 0)
	{
		is_finished = false;
		point<double> mouse_pos;
		glfwGetCursorPos(window, &mouse_pos.x, &mouse_pos.y);
		this->points.push_back({ int(mouse_pos.x), int(mouse_pos.y) });
		start_point = std::make_unique<DistinguishedPoint>(window, this->points.front());
		end_point = std::make_unique<DistinguishedPoint>(window, this->points.front());
	}
	else if (points.size() < 3)
		throw std::invalid_argument("Invalid amout of points.\n");
	else
	{
		is_finished = true;
		for (uint i = 1; i < points.size(); ++i)
			lines.push_back(std::make_unique<Line>(window, points.at(i - 1), points.at(i)));
		lines.push_back(std::make_unique<Line>(window, points.back(), points.front()));
	}
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
	if (points.size() == 1)
		start_point->update(mouse_pos);
	if (!lines.empty())
		lines.back()->update_end(mouse_pos);
}

void Figure::add_new_point(const point<int>& mouse_pos)
{
	if (points.size() > 3 && points.front().close_to(mouse_pos))
	{
		is_finished = true;
		points.back() = points.front();
		end_point->update(points.front());
		lines.back()->update_end(points.front());
	}
	else
	{
		lines.push_back(std::make_unique<Line>(window, points.back(), mouse_pos)); // can crash because initially i will have two points that are equal!, fix it if crashes
		points.push_back(mouse_pos);
		end_point->update(mouse_pos);
	}
}




