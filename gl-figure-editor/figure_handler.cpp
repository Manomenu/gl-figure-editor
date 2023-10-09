#include "figure_handler.h"

int FigureHandler::figure_to_update = -1;
std::vector<std::unique_ptr<Figure>> FigureHandler::figures = std::vector<std::unique_ptr<Figure>>();
point<int> FigureHandler::mouse_pos = {};
FigureHandler::FigureUpdateMode FigureHandler::figure_update_mode = None;

void default_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddMousePosEvent(float(xpos), float(ypos));
}

void default_mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddMouseButtonEvent(button, action == GLFW_PRESS);
}

FigureHandler::FigureHandler(GLFWwindow* window)
{
	this->window = window;
}

void FigureHandler::draw_figures()
{
	for (auto const& fig : figures)
		fig->draw();
}

void FigureHandler::add_figure(const points_t<int>& points)
{
	if (points.empty())
		figures.push_back(std::make_unique<Figure>(window));
	else
		figures.push_back(std::make_unique<Figure>(window, points));
}

void FigureHandler::enable_figure_creation()
{
	add_figure();
	glfwSetCursorPosCallback(window, control_latest_figure_point_callback);
	glfwSetMouseButtonCallback(window, new_point_on_click_callback);
}

void FigureHandler::disable_figure_creation()
{
	glfwSetCursorPosCallback(window, default_mouse_callback);
	glfwSetMouseButtonCallback(window, default_mouse_click_callback);
	figures.pop_back();
}

void FigureHandler::update_figures()
{
	// late add update_mode, now I just have moving the last point around
	if (figure_to_update != -1)
	{
		switch (figure_update_mode)
		{
		case ControlLastPoint:
			figures[figure_to_update]->update_last_point(mouse_pos);
			break;
		case AddNewPoint:
			figures[figure_to_update]->add_new_point(mouse_pos);
			if (figures[figure_to_update]->finished()) // deeper, because it should also start creating another point if edited figure has been closed
				figures.push_back(std::make_unique<Figure>(window));
			break;
		}
		
		figure_to_update = -1;
	}
}

void FigureHandler::control_latest_figure_point_callback(GLFWwindow* window, double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddMousePosEvent(float(xpos), float(ypos));

	if (!io.WantCaptureMouse)
	{
		figure_update_mode = ControlLastPoint;
		figure_to_update = figures.size() - 1;
		mouse_pos = { int(xpos), int(ypos) };
	}
}

void FigureHandler::new_point_on_click_callback(GLFWwindow* window, int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddMouseButtonEvent(button, action == GLFW_PRESS);

	if (!io.WantCaptureMouse)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			figure_update_mode = AddNewPoint;
			figure_to_update = figures.size() - 1;
		}
	}
}
