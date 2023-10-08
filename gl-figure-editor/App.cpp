#include "App.h"

App::App(uint winX, uint winY)
{
	set_up_glfw(winX, winY);
	set_up_imgui();
	set_up_opengl();
	make_handlers();
}

App::~App() 
{
	glfwTerminate();
}

void App::run()
{
    while (!glfwWindowShouldClose(window))
    {
		input_system->process_input();
		render_system->update();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::make_systems()
{
	interface_system = std::make_shared<InterfaceSystem>();
	render_system = std::make_unique<RenderSystem>(interface_system, figure_handler);
	input_system = std::make_unique<InputSystem>(window);
}

void App::set_up_opengl() 
{
	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
	//Set the rendering region to the actual screen size
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	//(left, top, width, height)
	glViewport(0, 0, w, h);
}

void App::make_handlers()
{
	figure_handler = std::make_shared<FigureHandler>(window);
}

void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void App::set_up_glfw(uint winX, uint winY) 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(winX, winY, "Figure Editor", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
	}
	glfwSwapInterval(0);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}
}

void App::set_up_imgui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init("#version 330");
}