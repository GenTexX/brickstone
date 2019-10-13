#include <bspch.h>
#include "sandbox.h"

void Sandbox::init() {

	this->w = new bs::Window(1600, 800);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(this->w->getWindow(), this->w->getContext());
	ImGui_ImplOpenGL3_Init("#version 430");

}

void Sandbox::run() {


	glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* create matrices */
	bs::mat4 proj = bs::mat4::perspective(70.0f, 16.0f / 9.0f, 0.01f, 300.0f);
	bs::mat4 view = bs::mat4::rotation(20.0f, bs::vec3(0.0, 0.0, 0.0));
	bs::mat4 rot = bs::mat4::rotation(0.0f, bs::vec3(0.0, 0.0, 0.0));
	view *= bs::mat4::translation(bs::vec3(0.0f, -7.0f, -15.0f));

	bs::Material m(bs::vec3(0.4f, 0.4f, 0.4f), bs::vec3(0.5f, 0.5f, 0.5f), bs::vec3(0.1f, 0.1f, 0.1f), 2);

	//m.loadDiffuseMap("src/res/bricks.png");
	//m.loadSpecularMap("src/res/bricks.png");

	bs::Model dino("src/res/elephant/elephant.obj");
	bs::Model lion("src/res/lion/lion.obj");

	/* set shader */
	bs::Shader s;
	s.readSource("src/shader/basic.shader");
	s.create();
	s.bind();
	s.setUniform3f("u_LightPosition", bs::vec3(1.0f, 0.5f, 0.0));
	s.setUniform3f("u_LightColor", bs::vec3(1.0f, 1.0f, 1.0f));
	s.setUniform3f("u_ViewPosition", bs::vec3(.0f, .0f, .0f));
	s.setUniformMat4("u_Projection", proj);
	s.setUniformMat4("u_View", view);
	
	glEnable(GL_DEPTH_TEST);


	bs::Camera cam;

	cam.x = 0.0f;
	cam.y = 0.0f;
	cam.z = 0.0f;

	float f = 0.7f;
	float angle = 0.0;
	float fov = 70.0;

	while (!this->w->shouldClose()) {
		
		//IMGUI
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

			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			ImGui::End();
		}


		bs::Renderer::clear();
		
		view = cam.getViewMatrix();
		s.setUniformMat4("u_View", view);
	
		rot = bs::mat4::translation(bs::vec3(-2.0f, -1.5f, -5.0f)) * bs::mat4::rotation(angle, bs::vec3(0.0, 1.0, 0.0));
		s.setUniformMat4("u_Model", rot);
		dino.draw(s);

		rot = bs::mat4::translation(bs::vec3(2.0f, -1.5f, -5.0f)) * bs::mat4::rotation(angle, bs::vec3(0.0, 1.0, 0.0));
		s.setUniformMat4("u_Model", rot);
		lion.draw(s);


		angle += angle < 360 ? f : (f - 360);
		bs::Log::trace("Angle {}", angle);
		//bs::Renderer::draw(s, cube.vao, );

		ImGui_ImplSDL2_ProcessEvent(&(bs::Window::event));
		
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		this->w->update();
	}

}
