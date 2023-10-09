#include "config.h"
#include "App.h"

int main()
{
    std::unique_ptr<App> app = std::make_unique<App>(SCR_WIDTH, SCR_HEIGHT);
    
    const std::shared_ptr<FigureHandler> figure_handler = app->get_figure_handler();
    figure_handler->add_figure({ { 250, 250 }, { 750, 500 },{ 150, 700 }, { 500, 750 }, { 33, 445 } });
    figure_handler->add_figure({ { 150, 150 }, { 250, 300 },{ 450, 100 }, { 500, 550 } });

    app->run();

    return EXIT_SUCCESS;
}