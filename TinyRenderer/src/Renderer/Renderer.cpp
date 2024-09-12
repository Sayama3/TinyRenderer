//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Renderer/Renderer.hpp"
#include "glad/glad.h"

namespace tr {

	RendererData::ModelData::ModelData(const glm::mat4& transformMatrix, const glm::mat4& normalMatrix, int entityId)
	: TransformMatrix(transformMatrix), NormalMatrix(normalMatrix), EntityId(entityId)
	{
	}

	RendererData::ModelData::ModelData(const glm::mat4& transformMatrix, int entityId)
	: TransformMatrix(transformMatrix), NormalMatrix(glm::transpose(glm::inverse(transformMatrix))), EntityId(entityId)
	{
	}

	void RendererData::ModelData::SetMatrix(const glm::mat4& transformMatrix, const glm::mat4& normalMatrix)
	{
		TransformMatrix = transformMatrix;
		NormalMatrix = normalMatrix;
	}

	void RendererData::ModelData::SetMatrix(const glm::mat4& transformMatrix)
	{
		TransformMatrix = transformMatrix;
		NormalMatrix = glm::transpose(glm::inverse(transformMatrix));
	}

	void Renderer::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		// glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		s_Camera = std::make_unique<Camera>();
		s_RenderData = std::make_unique<RendererData>();

		s_RenderData->CameraUniformBuffer = UniformBuffer::Create(sizeof(RendererData::CameraData), 0);
		s_RenderData->ModelUniformBuffer = UniformBuffer::Create(sizeof(RendererData::ModelData), 1);
//		s_RenderData->LightUniformBuffer = UniformBuffer::Create(sizeof(RendererData::LightData), 2);

		s_RenderData->CameraBuffer.CameraDirection = Vec4(s_Camera->GetForward(), 0);
		s_RenderData->CameraBuffer.CameraPosition = Vec4(s_Camera->Position, 1);
		s_RenderData->CameraBuffer.ViewProjectionMatrix = s_Camera->GetViewProjectionMatrix();
		s_RenderData->CameraUniformBuffer->SetData(s_RenderData->CameraBuffer);
	}

	void Renderer::Terminate()
	{
		s_RenderData.reset();
		s_Camera.reset();
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetShader(std::shared_ptr<Shader> shader) {
		if(!shader) return;
		s_Shader = std::move(shader);
		s_Shader->Bind();
	}

	void Renderer::DrawMesh(std::shared_ptr<Mesh> mesh, const Mat4& modelMatrix) {
		if(!mesh) return;
		auto vao = mesh->GetVertexArray();
		if(!vao) return;

		s_RenderData->ModelBuffer.SetMatrix(modelMatrix);
		s_RenderData->ModelUniformBuffer->SetData(s_RenderData->ModelBuffer);

		vao->Bind();
		glDrawElements(GL_TRIANGLES, vao->GetDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::SetCamera(const Camera &camera) {

		*s_Camera = camera;

		s_RenderData->CameraBuffer.CameraDirection = Vec4(s_Camera->GetForward(), 0);
		s_RenderData->CameraBuffer.CameraPosition = Vec4(s_Camera->Position, 1);
		s_RenderData->CameraBuffer.ViewProjectionMatrix = s_Camera->GetViewProjectionMatrix();

		s_RenderData->CameraUniformBuffer->SetData(s_RenderData->CameraBuffer);

	}
} // tr