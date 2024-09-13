cmake_minimum_required(VERSION 3.16)

set(LibraryName "TinyRenderer")
set(TR_SRC
		src/Core/Math.cpp
		include/TinyRenderer/Core/Math.hpp
		src/Core/Application.cpp
		include/TinyRenderer/Core/Application.hpp
		src/Core/Window.cpp
		include/TinyRenderer/Core/Window.hpp
		src/Core/Logger.cpp
		include/TinyRenderer/Core/Logger.hpp
		src/Renderer/Renderer.cpp
		include/TinyRenderer/Renderer/Renderer.hpp
		include/TinyRenderer/TinyRenderer.hpp
		src/Renderer/Texture.cpp
		include/TinyRenderer/Renderer/Texture.hpp
		src/Renderer/Shader.cpp
		include/TinyRenderer/Renderer/Shader.hpp
		src/Renderer/Mesh.cpp
		include/TinyRenderer/Renderer/Mesh.hpp
		src/Renderer/Buffer.cpp
		include/TinyRenderer/Renderer/Buffer.hpp
		src/Renderer/VertexArray.cpp
		include/TinyRenderer/Renderer/VertexArray.hpp
		include/TinyRenderer/Core/Buffer.hpp
		include/TinyRenderer/Renderer/DefaultShaders.hpp
		src/Core/Camera.cpp
		include/TinyRenderer/Core/Camera.hpp
		src/Renderer/UniformBuffer.cpp
		include/TinyRenderer/Renderer/UniformBuffer.hpp
		src/Renderer/Framebuffer.cpp
		include/TinyRenderer/Renderer/Framebuffer.hpp
		include/TinyRenderer/Renderer/Light.hpp
		src/Renderer/DefaultShaders.cpp
		src/Renderer/Cubemap.cpp
		include/TinyRenderer/Renderer/Cubemap.hpp
		include/TinyRenderer/Core/Image.hpp
		src/Core/Image.cpp
		include/TinyRenderer/Core/Image.hpp
		src/Core/Buffer.cpp
		vendors_src/implement.cpp
		include/TinyRenderer/Core/KeyCodes.hpp
		src/Core/Events.cpp
		include/TinyRenderer/Events/Event.hpp
		include/TinyRenderer/Core/MouseButtonCodes.hpp
		include/TinyRenderer/Core/Utility.hpp
		include/TinyRenderer/Events/Callback.hpp
)


file(GLOB_RECURSE TR_VENDORS_SRC CONFIGURE_DEPENDS vendors_src/*.cpp vendors_src/*.cxx  vendors_src/*.c)

add_library(${LibraryName} STATIC ${TR_SRC} ${TR_VENDORS_SRC})

target_include_directories(${LibraryName} PUBLIC  include)
target_include_directories(${LibraryName} PRIVATE vendors_include)
target_include_directories(${LibraryName} PRIVATE src)

target_link_libraries(${LibraryName} PRIVATE glfw imgui)
target_link_libraries(${LibraryName} PUBLIC glm)

target_compile_definitions(${LibraryName} PUBLIC GLM_ENABLE_EXPERIMENTAL=1)
