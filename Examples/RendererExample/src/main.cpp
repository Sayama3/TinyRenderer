//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/TinyRenderer.hpp"

#include <algorithm>
#include <random>
#include <glad/glad.h>

class MovementCallback : public tr::Callback
{
public:
	tr::Vec3 movement{0.0f};
	tr::Vec3 rotation{0.0f};
public:
	bool OnKeyPressed(tr::KeyPressedEvent& e) {
		if(e.GetRepeatCount() != 0) return false;

		switch (e.GetKeyCode())
		{
			case tr::Key::W: 		movement.z -= 1; break;
			case tr::Key::A: 		movement.x -= 1; break;
			case tr::Key::S: 		movement.z += 1; break;
			case tr::Key::D: 		movement.x += 1; break;
			case tr::Key::E: 		movement.y += 1; break;
			case tr::Key::Q: 		movement.y -= 1; break;

			case tr::Key::Left:		rotation.y += 1; break;
			case tr::Key::Right:	rotation.y -= 1; break;
			case tr::Key::Up:		rotation.x += 1; break;
			case tr::Key::Down:		rotation.x -= 1; break;
		}
		return false;
	}
	bool OnKeyRelease(tr::KeyReleasedEvent& e) {
		switch (e.GetKeyCode())
		{
			case tr::Key::W: movement.z += 1; break;
			case tr::Key::A: movement.x += 1; break;
			case tr::Key::S: movement.z -= 1; break;
			case tr::Key::D: movement.x -= 1; break;
			case tr::Key::E: movement.y -= 1; break;
			case tr::Key::Q: movement.y += 1; break;

			case tr::Key::Left:		rotation.y -= 1; break;
			case tr::Key::Right:	rotation.y += 1; break;
			case tr::Key::Up:		rotation.x -= 1; break;
			case tr::Key::Down:		rotation.x += 1; break;
		}
		return false;
	}

	virtual bool operator()(tr::Event& event)
	{
		tr::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<tr::KeyPressedEvent>(TR_BIND_MEMBER_FN(OnKeyPressed));
		dispatcher.Dispatch<tr::KeyReleasedEvent>(TR_BIND_MEMBER_FN(OnKeyRelease));
		return false;
	}
};

class ResizeCallback : public tr::Callback
{
public:
	std::shared_ptr<tr::Framebuffer> m_Framebuffer;
	bool OnResize(tr::WindowResizeEvent& e)
	{
		m_Framebuffer->Resize(e.GetWidth(), e.GetHeight());
		return false;
	}
public:
	virtual bool operator()(tr::Event& e)
	{
		tr::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<tr::WindowResizeEvent>(TR_BIND_MEMBER_FN(OnResize));
		return false;
	}
};

int main(int argc, const char* argv[]) {
	MovementCallback movement;
	ResizeCallback resize;
	std::vector<glm::mat4> m_CubeInstances{500};

	//std::for_each(std::execution::par_unseq, m_CubeInstances.begin(), m_CubeInstances.end(), [](glm::mat4& matrix)

	for(glm::mat4& matrix : m_CubeInstances)
	{
		tr::Random random(std::time(nullptr));

		matrix = glm::identity<glm::mat4>();
		glm::translate(matrix, {random.FValue(-10.f,10.f), random.FValue(-10.f,10.f), random.FValue(-10.f,10.f)});
		glm::rotate(matrix,random.FValue(-glm::pi<float>(),-glm::pi<float>()), glm::normalize(glm::vec3{random.FValue(-10.f,10.f), random.FValue(-10.f,10.f), random.FValue(-10.f,10.f)}));
		glm::scale(matrix, {random.FValue(0.5,2),random.FValue(0.5,2),random.FValue(0.5,2)});
	}
	//);

	auto *app = new tr::Application(tr::WindowProps{});
	app->AddCallback(&movement);

	auto cube = tr::Primitives::CreateCube();
	tr::StringShaderSource vertexShader = {tr::DefaultShaders::c_DefaultVert};
	tr::StringShaderSource fragmentShader = {tr::DefaultShaders::c_DefaultFrag};

	auto shader = tr::Shader::Create(&vertexShader, &fragmentShader);

	auto ssbo = tr::SSBO::Create(m_CubeInstances, tr::SSBOUsage::DynamicDraw);
	ssbo->Bind(1);

//	{
//		auto cubemap = tr::Cubemap::Load(R"(cube2.jpg)");
//		tr::Renderer::SetCubemap(cubemap);
//	}

//	{
//		resize.m_Framebuffer = tr::Framebuffer::Create({app->GetWindowWidth(), app->GetWindowHeight(), {
//				{tr::FramebufferTextureFormat::Color},
//				{tr::FramebufferTextureFormat::Depth},
//		}});
//		tr::Renderer::SetFramebuffer(resize.m_Framebuffer);
//		app->AddCallback(&resize);
//	}

	tr::Renderer::SetShader(shader);

	while (app->ShouldRun()) {
		app->BeginFrame();
		tr::Renderer::Clear();

		tr::Camera camera = tr::Renderer::GetCamera();

		if (movement.rotation.x != 0)
			camera.Rotation *= glm::angleAxis<float, glm::defaultp>(glm::radians(movement.rotation.x), {1.f, 0.f, 0.f});

		if (movement.rotation.y != 0)
			camera.Rotation = glm::angleAxis<float, glm::defaultp>(glm::radians(movement.rotation.y), {0.f, 1.f, 0.f}) *
							  camera.Rotation;

		camera.Rotation = glm::normalize(camera.Rotation);
		camera.Position += camera.Rotation * movement.movement;
		tr::Renderer::SetCamera(camera);
		tr::Renderer::DrawMesh(cube, m_CubeInstances.size());

		tr::Renderer::EndFrame();
		app->EndFrame();
	}
	ssbo.reset();

	app->RemoveCallback(&resize);
	resize.m_Framebuffer.reset();
	app->RemoveCallback(&movement);

	delete app;
	app = nullptr;

	return 0;
}