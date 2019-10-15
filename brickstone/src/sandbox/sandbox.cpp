#include <bspch.h>
#include "sandbox.h"

void onClick(void*);

void Sandbox::init() {

	this->w = new bs::Window(1600, 800);

	this->w->setKeyDownCallback(onClick);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(this->w->getWindow(), this->w->getContext());
	ImGui_ImplOpenGL3_Init("#version 430");

	//FaceCulling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}

void Sandbox::run() {

	glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
	
	/* create matrices */
	bs::mat4 proj = bs::mat4::perspective(70.0f, 16.0f / 9.0f, 0.01f, 300.0f);
	bs::mat4 view = bs::mat4::rotation(20.0f, bs::vec3(0.0, 0.0, 0.0));
	bs::mat4 rot = bs::mat4::rotation(0.0f, bs::vec3(0.0, 0.0, 0.0));
	view *= bs::mat4::translation(bs::vec3(0.0f, -7.0f, -15.0f));

	bs::Material m(bs::vec3(0.4f, 0.4f, 0.4f), bs::vec3(0.5f, 0.5f, 0.5f), bs::vec3(0.1f, 0.1f, 0.1f), 2);

	bs::Model plane("src/res/plane.obj");
	bs::Terrain terrain = bs::Terrain(10.0f, 10.0f, 64, 64, 5.0f, 2.0f);

	/* set shader */
	bs::Shader s;
	s.readSource("src/shader/basic.shader");
	s.create();
	s.bind();
	s.setUniform3f("u_LightPosition", bs::vec3(2.0f, 5.0f, 0.0f));
	s.setUniform3f("u_LightColor", bs::vec3(1.0f, 1.0f, 1.0f));
	s.setUniform3f("u_ViewPosition", bs::vec3(.0f, .0f, .0f));
	s.setUniformMat4("u_Projection", proj);
	
	glEnable(GL_DEPTH_TEST);

	bs::Camera cam;
	cam.x = 0.0f;
	cam.y = 0.0f;
	cam.z = 0.0f;

	float f = 0.7f;
	float angle = 0.0;
	float fov = 70.0;

	while (!this->w->shouldClose()) {
		
		/*IMGUI*/
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(this->w->getWindow());
		ImGui::NewFrame();

		{
			ImGui::Begin("FOV");										            

			if (ImGui::SliderFloat("FieldOfView", &fov, 30.0f, 140.0f)) {           
				proj = bs::mat4::perspective(fov, 16.0f / 9.0f, 0.01f, 100.0f);
				s.setUniformMat4("u_Projection", proj);
			}

			ImGui::SliderFloat("Rotationspeed", &f, 0.0f, 15.0f, "%.1f");

			if (ImGui::SliderFloat("Width", &(terrain.m_Width), 1.0f, 15.0f, "%.1f"))
				terrain.load();

			if (ImGui::SliderFloat("Height", &(terrain.m_Height), 1.0f, 15.0f, "%.1f"))
				terrain.load();

			if (ImGui::SliderFloat("Hardness", &(terrain.m_Hardness), 1.0f, 100.0f, "%.1f"))
				terrain.load();

			if (ImGui::SliderFloat("TextureScale", &(terrain.m_TextureScale), 1.0f, 15.0f, "%.3f"))
				terrain.load();

			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			ImGui::End();
		}


		bs::Renderer::clear();
		
		view = cam.getViewMatrix();
		s.setUniformMat4("u_View", view);
	
		rot = bs::mat4::translation(bs::vec3(0.0f, -0.7f, -5.0f)) * bs::mat4::rotation(angle, bs::vec3(0.0, 1.0, 0.0));
		s.setUniformMat4("u_Model", rot);
		terrain.draw(s);

		angle += angle < 360 ? f : (f - 360);

		ImGui_ImplSDL2_ProcessEvent(&(bs::Window::event));
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		this->w->update();
	}

}

void onClick(void* window) {

	bs::Window* w = (bs::Window*) window;
	if (w->m_Keystate & (1ULL<<bs::KeyCode::BSK_W)) {



	}


}
