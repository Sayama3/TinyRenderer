cmake_minimum_required(VERSION 3.16)

#GLM Options
set(GLM_ENABLE_CXX_20       ON)

# ImGui Parameters
set(IMGUI_GLFW              ON)
set(IMGUI_OPENGL3           ON)
set(IMGUI_OPENGL3_LOADER    ON)

# GLFW Parameters
set(GLFW_BUILD_DOCS         OFF)
set(GLFW_INSTALL            OFF)

include(FetchContent)
FetchContent_Declare(
		glm
		GIT_REPOSITORY https://github.com/icaven/glm
		GIT_TAG master
)

FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw
		GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # v3.4
)

FetchContent_Declare(
		imgui
		GIT_REPOSITORY https://github.com/Sayama3/ImGui
		GIT_TAG docking #docking branch
)
FetchContent_MakeAvailable(glm glfw imgui)


target_link_libraries(imgui PUBLIC glfw)