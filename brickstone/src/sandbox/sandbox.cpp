#include <bspch.h>
#include "sandbox.h"

void onClick(void*);

void Sandbox::init() {


	this->w = new bs::Window(1920, 1080, "BrickStone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_FULLSCREEN);

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

	bs::pointLight light;
	light.m_Ambient = bs::vec3(1.0f, 1.0f, 1.0f);
	light.m_Diffuse = bs::vec3(1.0f, 1.0f, 1.0f);
	light.m_Specular = bs::vec3(1.0f, 1.0f, 1.0f);
	light.m_Position = bs::vec3(0.0f, 3.4f, -5.0f);
	light.m_Constant = 0.4f;
	light.m_Linear = 0.09f;
	light.m_Quadratic = 0.032f;

	bs::spotLight spotlight;
	spotlight.m_Ambient = bs::vec3(1.0f, 1.0f, 1.0f);
	spotlight.m_Diffuse = bs::vec3(1.0f, 1.0f, 1.0f);
	spotlight.m_Specular = bs::vec3(1.0f, 1.0f, 1.0f);
	spotlight.m_Position = bs::vec3(0.0f, 0.0f, 0.0f);
	spotlight.m_Direction = bs::vec3(0.0f, -0.2f, -1.0f).normalized();
	spotlight.cutOff = 0.2f;
	
	/* set shader */
	bs::Shader s;
	s.readSource("src/shader/basic.shader");
	s.create();
	s.bind();
	s.addSpotLight(spotlight);
	s.setUniform3f("u_ViewPosition", bs::vec3(.0f, .0f, .0f));
	s.setUniformMat4("u_Projection", proj);
	
	glEnable(GL_DEPTH_TEST);

	bs::camera cam;
	cam.x = 0.0f;
	cam.y = 0.0f;
	cam.z = 0.0f;

	float f = 0.0f;
	float angle = 0.0;
	float fov = 70.0;

	while (!this->w->shouldClose()) {
		
		/*IMGUI*/
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(this->w->getWindow());
		ImGui::NewFrame();

		{
			ImGui::Begin("Terrain");

			if (ImGui::SliderFloat("Width", &(terrain.m_Width), 1.0f, 15.0f, "%.1f"))
				terrain.load();

			if (ImGui::SliderFloat("Height", &(terrain.m_Height), 1.0f, 15.0f, "%.1f"))
				terrain.load();

			if (ImGui::SliderInt("Count Width", &(terrain.m_CountWidth), 4, 128, "%.1f"))
				terrain.load();

			if (ImGui::SliderInt("Count Height", &(terrain.m_CountHeight), 4, 128, "%.1f"))
				terrain.load();

			if (ImGui::SliderFloat("Noise Frequence", &(terrain.m_NoiseFrequency), 0.0, 0.5, "%.5f"))
				terrain.load();

			if (ImGui::SliderFloat("Hardness", &(terrain.m_Hardness), 0.0f, 100.0f, "%.1f"))
				terrain.load();

			if (ImGui::SliderFloat("TextureScale", &(terrain.m_TextureScale), 1.0f, 15.0f, "%.3f"))
				terrain.load();

			ImGui::End();
		}

		{
			ImGui::Begin("Light");

			if (ImGui::ColorPicker3("Ambient", &(light.m_Ambient.x)))
				s.addPointLight(light);

			if (ImGui::ColorPicker3("Diffuse", &(light.m_Diffuse.x)))
				s.addPointLight(light);

			if (ImGui::ColorPicker3("Specular", &(light.m_Specular.x)))
				s.addPointLight(light);

			if (ImGui::SliderFloat("Constant", &(light.m_Constant), 0.0f, 1.0f, "%.3f"))
				s.addPointLight(light);

			if (ImGui::SliderFloat("Linear", &(light.m_Linear), 0.0f, 0.5f, "%.3f"))
				s.addPointLight(light);

			if (ImGui::SliderFloat("Quadratic", &(light.m_Quadratic), 0.0f, 0.1f, "%.3f"))
				s.addPointLight(light);

			if (ImGui::SliderFloat("posX", &(light.m_Position.x), -5.0f, 5.0f, "%.3f"))
				s.addPointLight(light);

			if (ImGui::SliderFloat("posY", &(light.m_Position.y), -5.0f, 5.0f, "%.3f"))
				s.addPointLight(light);

			if (ImGui::SliderFloat("posZ", &(light.m_Position.z), -10.0f, 1.0f, "%.3f"))
				s.addPointLight(light);

			if (ImGui::SliderFloat("cutOff", &(spotlight.cutOff), 0.0, 1.0f, "%.3f"))
				s.addSpotLight(spotlight);

			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			ImGui::End();
		}

		{
			ImGui::Begin("Program");										            

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
