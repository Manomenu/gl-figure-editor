#pragma once
#include "config.h"
#include "figure_handler.h"

class InterfaceSystem
{
public:
	InterfaceSystem(std::shared_ptr<FigureHandler> figure_handler);
	~InterfaceSystem();
	void draw_interface();
	void update_scene_mode();
	bool scene_mode_modified();
	const SceneMode& get_scene_mode() const { return (SceneMode)scene_mode; }
	const SceneMode& get_prev_scene_mode() const { return prev_scene_mode; }

private:
	bool show_window = true;
	int scene_mode = View;
	int _psm = View;
	SceneMode prev_scene_mode = View;
	std::shared_ptr<FigureHandler> figure_handler;
};