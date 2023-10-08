#pragma once
#include "config.h"
#include <my/Shader.h>
#include "interface_system.h"
#include "figure_handler.h"

class RenderSystem
{
public:
	RenderSystem(
		std::shared_ptr<InterfaceSystem> interface_system, 
		std::shared_ptr<FigureHandler> figure_handler
	);
	void update();

private:
	std::unique_ptr<Shader> shader;
	std::shared_ptr<InterfaceSystem> interface_system;
	std::shared_ptr<FigureHandler> figure_handler;
};

