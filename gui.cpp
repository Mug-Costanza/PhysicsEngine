#include "gui.hpp"

extern Window window;

namespace GUI
{
	void Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO io = ImGui::GetIO(); (void)io;
		ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

	void Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}