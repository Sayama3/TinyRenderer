//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/TinyRenderer.hpp"
#include "TinyRenderer/Core/Math.hpp"

class MovementCallback : public tr::Callback
{
public:
	tr::Vec3 movement{0.0f};
	tr::Vec3 rotation{0.0f};
public:
	bool OnKeyPressed(tr::KeyPressedEvent& e) {
		switch (e.GetKeyCode())
		{
			case tr::Key::W: 		movement.z += 1; break;
			case tr::Key::A: 		movement.x -= 1; break;
			case tr::Key::S: 		movement.z -= 1; break;
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
			case tr::Key::W: movement.z -= 1; break;
			case tr::Key::A: movement.x += 1; break;
			case tr::Key::S: movement.z += 1; break;
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

int main(int argc, const char* argv[])
{
	MovementCallback movement;
	auto* app = new tr::Application(tr::WindowProps{});
	app->AddCallback(&movement);

	auto cube = tr::Primitives::CreateCube();
	tr::StringShaderSource vertexShader = {tr::DefaultShaders::c_DefaultVert};
	tr::StringShaderSource fragmentShader = {tr::DefaultShaders::c_DefaultFrag};

	auto shader = tr::Shader::Create(&vertexShader, &fragmentShader);
//	{
//		auto cubemap = tr::Cubemap::Load(R"(cube2.jpg)");
//		tr::Renderer::SetCubemap(cubemap);
//	}
	tr::Renderer::SetShader(shader);

	while(app->ShouldRun())
	{
		app->BeginFrame();

		tr::Camera camera = tr::Renderer::GetCamera();
		camera.Position += movement.movement;

		if(movement.rotation.x != 0)
			camera.Rotation *= glm::angleAxis<float, glm::defaultp>(glm::radians(movement.rotation.x), {1.f,0.f,0.f});

		if(movement.rotation.y != 0)
			camera.Rotation = glm::angleAxis<float, glm::defaultp>(glm::radians(movement.rotation.y), {0.f,1.f,0.f}) * camera.Rotation;

		camera.Rotation = glm::normalize(camera.Rotation);
		tr::Renderer::SetCamera(camera);
		tr::Renderer::DrawMesh(cube, tr::Math::TRS({-2,-2,-10}, {}));

		app->EndFrame();
	}

	app->RemoveCallback(&movement);

	delete app;
	app = nullptr;

	return 0;
}