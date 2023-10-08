#pragma once
#include "config.h"
#include "interface_system.h"
#include "render_system.h"
#include "input_system.h"

class App
{
public:
	App(uint winX, uint winY);
	~App();
	void make_systems();
	void run();
	const std::shared_ptr<FigureHandler>& get_figure_handler() const { return figure_handler; }

private:
	GLFWwindow* window;
	std::unique_ptr<InputSystem> input_system;
	std::unique_ptr<RenderSystem> render_system;
	std::shared_ptr<InterfaceSystem> interface_system;
	std::shared_ptr<FigureHandler> figure_handler;

	void set_up_glfw(uint winX, uint winY);
	void set_up_imgui();
	void set_up_opengl();
	void make_handlers();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

