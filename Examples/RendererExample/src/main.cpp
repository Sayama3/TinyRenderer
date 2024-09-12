//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/TinyRenderer.hpp"

int main(int argc, const char* argv[])
{
	auto* app = new tr::Application(tr::WindowProps{});

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

		tr::Renderer::DrawMesh(cube, tr::Math::TRS({-2,-2,-10}, {}));

		app->EndFrame();
	}

	delete app;
	app = nullptr;

	return 0;
}