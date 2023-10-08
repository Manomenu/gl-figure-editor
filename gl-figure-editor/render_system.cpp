#include "render_system.h"

RenderSystem::RenderSystem(std::shared_ptr<InterfaceSystem> interface_system, std::shared_ptr<FigureHandler> figure_handler)
{
	shader = std::make_unique<Shader>("./shaders/default.vs", "./shaders/default.fs");
	this->interface_system = interface_system;
	this->figure_handler = figure_handler;
}

void RenderSystem::update()
{
	glClearColor(0.2f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shader->use();

	figure_handler->draw_figures();
	interface_system->draw_interface(); // shall be last
}