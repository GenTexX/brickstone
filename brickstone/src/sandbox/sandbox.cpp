#include <bspch.h>
#include "sandbox.h"

void onClick(void*);
void imguiLight(bs::pointLight& l, int index, bs::Shader s);

void Sandbox::init() {

<<<<<<< Updated upstream
	this->w = new bs::Window(1600, 800);
	this->w = new bs::Window(1920, 1080, "BrickStone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_FULLSCREEN);
=======

	this->w = new bs::Window(1600, 900, "BrickStone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_FOREIGN);
>>>>>>> Stashed changes

<<<<<<< HEAD
	this->w->setKeyDownCallback(onClick);
=======

	this->w->setMouseButtonDownCallback(onClick);
>>>>>>> parent of 97e6b8d... Revert "Revert "Revert "Merge branch 'lighting'"""

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
	bs::mat4 proj = bs::mat4::orthographic(-8, 8, -4.5, 4.5, 0, 1);
	bs::mat4 view = bs::mat4::rotation(20.0f, bs::vec3(0.0, 0.0, 0.0));
	bs::mat4 rot = bs::mat4::rotation(0.0f, bs::vec3(0.0, 0.0, 0.0));
	view *= bs::mat4::translation(bs::vec3(0.0f, -7.0f, -15.0f));

	bs::Material m(bs::vec3(0.4f, 0.4f, 0.4f), bs::vec3(0.5f, 0.5f, 0.5f), bs::vec3(0.1f, 0.1f, 0.1f), 2);

	bs::Model plane("src/res/plane.obj");
	bs::Terrain terrain = bs::Terrain(100.0f, 109.0f, 128, 128, 3.0f, 10.0f);

	bs::directionalLight dirlight;
	dirlight.m_Direction = bs::vec3(1.0f, -1.0f, 0.4f).normalized();
	dirlight.m_Ambient = bs::vec3(1.0f, 1.0f, 1.0f);
	dirlight.m_Diffuse = bs::vec3(0.2f, 0.2f, 0.2f);
	dirlight.m_Specular = bs::vec3(1.0f, 1.0f, 1.0f);

	bs::pointLight pointlight;
	pointlight.m_Ambient = bs::vec3(1.0f, 1.0f, 1.0f);
	pointlight.m_Diffuse = bs::vec3(1.0f, 1.0f, 1.0f);
	pointlight.m_Specular = bs::vec3(1.0f, 1.0f, 1.0f);
	pointlight.m_Position = bs::vec3(0.0f, 2.4f, -5.0f);
	pointlight.m_Constant = 0.4f;
	pointlight.m_Linear = 0.09f;
	pointlight.m_Quadratic = 0.032f;

	bs::pointLight pointlight2;
	pointlight2.m_Ambient = bs::vec3(1.0f, 1.0f, 1.0f);
	pointlight2.m_Diffuse = bs::vec3(0.2f, 0.1f, 0.2f);
	pointlight2.m_Specular = bs::vec3(1.0f, 1.0f, 1.0f);
	pointlight2.m_Position = bs::vec3(0.0f, 0.4f, -3.0f);
	pointlight2.m_Constant = 0.12f;
	pointlight2.m_Linear = 0.09f;
	pointlight2.m_Quadratic = 0.022f;

	bs::spotLight spotlight;
	spotlight.m_Ambient = bs::vec3(1.0f, 1.0f, 1.0f);
	spotlight.m_Diffuse = bs::vec3(1.0f, 1.0f, 1.0f);
	spotlight.m_Specular = bs::vec3(1.0f, 1.0f, 1.0f);
	spotlight.m_Position = bs::vec3(0.0f, 0.0f, 0.0f);
	spotlight.m_Direction = bs::vec3(0.0f, -0.2f, -1.0f).normalized();
	spotlight.innerCutOff = 0.2f;
	spotlight.outerCutOff = 0.23f;
	
	/* set shader */
	bs::Shader s;
	s.readSource("src/shader/basic.shader");
	s.create();
	s.bind();
	s.addDirectionalLight(dirlight);
	s.addPointLight(pointlight);
	s.addPointLight(pointlight2);
	s.addSpotLight(spotlight);
	s.addSpotLight(spotlight);
	s.addSpotLight(spotlight);
	s.addSpotLight(spotlight);
	s.setUniform3f("u_ViewPosition", bs::vec3(.0f, .0f, .0f));
	s.setUniformMat4("u_Projection", proj);
	
	glEnable(GL_DEPTH_TEST);

	bs::camera cam;
	cam.x = 0.0f;
	cam.y = 0.0f;
	cam.z = 0.0f;

	int selectedLight = 0;
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

		imguiLight(pointlight, 0, s);
		imguiLight(pointlight2, 1, s);
		

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

void imguiLight(bs::pointLight& l, int index, bs::Shader s) {
	ImGui::Begin(("Light" + std::to_string(index)).c_str());

	if (ImGui::ColorPicker3(("Ambient" + std::to_string(index)).c_str(), &(l.m_Ambient.x)))
		s.addPointLight(l, index);

	if (ImGui::ColorPicker3(("Diffuse" + std::to_string(index)).c_str(), &(l.m_Diffuse.x)))
		s.addPointLight(l, index);

	if (ImGui::ColorPicker3(("Specular" + std::to_string(index)).c_str(), &(l.m_Specular.x)))
		s.addPointLight(l, index);

	if (ImGui::SliderFloat(("Constant" + std::to_string(index)).c_str(), &(l.m_Constant), 0.0f, 1.0f, "%.3f"))
		s.addPointLight(l, index);

	if (ImGui::SliderFloat(("Linear" + std::to_string(index)).c_str(), &(l.m_Linear), 0.0f, 0.5f, "%.3f"))
		s.addPointLight(l, index);

	if (ImGui::SliderFloat(("Quadratic" + std::to_string(index)).c_str(), &(l.m_Quadratic), 0.0f, 0.1f, "%.3f"))
		s.addPointLight(l, index);

	if (ImGui::SliderFloat(("posX" + std::to_string(index)).c_str(), &(l.m_Position.x), -5.0f, 5.0f, "%.3f"))
		s.addPointLight(l, index);

	if (ImGui::SliderFloat(("posY" + std::to_string(index)).c_str(), &(l.m_Position.y), -5.0f, 5.0f, "%.3f"))
		s.addPointLight(l, index);

	if (ImGui::SliderFloat(("posZ" + std::to_string(index)).c_str(), &(l.m_Position.z), -10.0f, 1.0f, "%.3f"))
		s.addPointLight(l, index);

	ImGui::End();
}
