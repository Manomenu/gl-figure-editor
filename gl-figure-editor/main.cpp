#include "config.h"
#include "App.h"

// settings
const uint SCR_WIDTH = 1200;
const uint SCR_HEIGHT = 800;

int main()
{
    std::unique_ptr<App> app = std::make_unique<App>(SCR_WIDTH, SCR_HEIGHT);
    
    const std::shared_ptr<FigureHandler> figure_handler = app->get_figure_handler();
    figure_handler->add_figure(
        { 
            { 250, 250 }, 
            { 750, 500 },
            { 500, 750 },
            {  33, 445 }
        }
    );

    app->make_systems();

    app->run();

    return EXIT_SUCCESS;
}