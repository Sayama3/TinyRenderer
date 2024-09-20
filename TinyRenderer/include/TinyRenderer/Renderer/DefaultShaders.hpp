//
// Created by Sayama on 11/07/2024.
//

#pragma once

namespace tr::DefaultShaders
{
	static inline constexpr const char* const c_DefaultVert = R"(
#version 450 core

#define ALPHA_MODE_OPAQUE 0
#define ALPHA_MODE_MASK 1
#define ALPHA_MODE_BLEND 2

#define MAX_LIGHT_COUNT 20
#define EPSILON 0.1

//struct Light
//{
//    vec4 Color;
//    vec4 Position;
//    vec4 Direction;
//    float Range;
//    float Intensity;
//    int Type; //0 = Directional ; 2 = Spot ; 1 = Point
//};
//
//struct LightData
//{
//    Light lights[MAX_LIGHT_COUNT];
//    int lightCount;
//};

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjectionMatrix;
    vec4 u_CameraPosition;
    vec4 u_CameraDirection;
};

//layout(std140, binding = 1) uniform Model
//{
//    mat4 u_ModelMatrix;
//    mat4 u_NormalMatrix;
//    int u_EntityId;
//};

layout(std140, binding = 1) buffer Model
{
	mat4 u_ModelMatrices[];
};

//layout(std140, binding = 2) uniform Lights
//{
//    LightData lights;
//};

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;

layout (location = 0) out vec3 v_Position;
layout (location = 1) out vec3 v_Normal;
layout (location = 2) out vec2 v_TexCoord;
layout (location = 3) out vec4 v_Color;


void main() {
//    gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
    gl_Position = u_ViewProjectionMatrix * u_ModelMatrices[gl_InstanceID] * vec4(a_Position, 1.0);

    v_Position = (u_ModelMatrices[gl_InstanceID] * vec4(a_Position, 1.0)).xyz;
    v_Normal = normalize((transpose(inverse(u_ModelMatrices[gl_InstanceID])) * vec4(a_Normal, 0.0)).xyz);
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
}
)";

	static inline constexpr const char* const c_DefaultFrag = R"(
#version 450 core

#define ALPHA_MODE_OPAQUE 0
#define ALPHA_MODE_MASK 1
#define ALPHA_MODE_BLEND 2

#define MAX_LIGHT_COUNT 20
#define EPSILON 0.1

//struct Light
//{
//    vec4 Color;
//    vec4 Position;
//    vec4 Direction;
//    float Range;
//    float Intensity;
//    float Cutoff;
//    int Type; //0 = Directional ; 1 = Point ; 2 = Spot
//};
//
//struct LightData
//{
//    Light lights[MAX_LIGHT_COUNT];
//    int lightCount;
//};

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjectionMatrix;
    vec4 u_CameraPosition;
    vec4 u_CameraDirection;
};

//layout(std140, binding = 1) uniform Model
//{
//    mat4 u_ModelMatrix;
//    mat4 u_NormalMatrix;
//    int u_EntityId;
//};

layout(std140, binding = 1) buffer Model
{
	mat4 u_ModelMatrices[];
};

//layout(std140, binding = 2) uniform Lights
//{
//    LightData lights;
//};

layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Normal;
layout (location = 2) in vec2 v_TexCoord;
layout (location = 3) in vec4 v_Color;

layout (location = 0) out vec4 o_Color;

//layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
//	o_Color = vec4(0.8, 0.3, 0.2, 1);
	o_Color = v_Color;
}
)";

	static inline constexpr const char* const c_CubemapVert = R"(
#version 450 core

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjectionMatrix;
    vec4 u_CameraPosition;
    vec4 u_CameraDirection;
};

layout (location = 0) in vec3 v_Position;

layout(location = 0) out vec3 v_TexCoords;

void main()
{
    v_TexCoords = v_Position;
    vec4 tmpPosition = u_ViewProjectionMatrix * vec4(v_Position, 0.0);
    gl_Position = tmpPosition.xyww;
}
)";

	static inline constexpr const char* const c_CubemapFrag = R"(
#version 450 core

layout(binding = 0) uniform samplerCube u_Skybox;

layout(location = 0) in vec3 v_TexCoords;
layout(location = 0) out vec4 o_Color;

void main(void) {
	o_Color = texture(u_Skybox, v_TexCoords);
}

)";
}