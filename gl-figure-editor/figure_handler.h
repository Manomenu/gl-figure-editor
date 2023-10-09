#pragma once
#include "config.h"
#include "figure.h"

class FigureHandler
{
public:
	FigureHandler(GLFWwindow* window);
	void draw_figures();
	void add_figure(const points_t<int>& points = {});
	void enable_figure_creation();
	void disable_figure_creation();
	void update_figures();

private:
	static enum FigureUpdateMode
	{
		None,
		ControlLastPoint,
		AddNewPoint
	} figure_update_mode;
	GLFWwindow* window;
	static std::vector<std::unique_ptr<Figure>> figures;
	static int figure_to_update;
	static point<int> mouse_pos;

	static void control_latest_figure_point_callback(GLFWwindow* window, double xpos, double ypos);
	static void new_point_on_click_callback(GLFWwindow* window, int button, int action, int mods);

	
};

