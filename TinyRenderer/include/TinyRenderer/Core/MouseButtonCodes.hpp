//
// Created by Sayama on 13/09/2024.
//

#pragma once

// Imported from glfw3.h
namespace tr {
	enum class Mouse : int
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,
		Last = Button8,
		Left = Button1,
		Right = Button2,
		Middle = Button3,
	};
}

#define VXM_MOUSE_BUTTON_1         ::tr::Mouse::Button1
#define VXM_MOUSE_BUTTON_2         ::tr::Mouse::Button2
#define VXM_MOUSE_BUTTON_3         ::tr::Mouse::Button3
#define VXM_MOUSE_BUTTON_4         ::tr::Mouse::Button4
#define VXM_MOUSE_BUTTON_5         ::tr::Mouse::Button5
#define VXM_MOUSE_BUTTON_6         ::tr::Mouse::Button6
#define VXM_MOUSE_BUTTON_7         ::tr::Mouse::Button7
#define VXM_MOUSE_BUTTON_8         ::tr::Mouse::Button8
#define VXM_MOUSE_BUTTON_LAST      ::tr::Mouse::Last
#define VXM_MOUSE_BUTTON_LEFT      ::tr::Mouse::Left
#define VXM_MOUSE_BUTTON_RIGHT     ::tr::Mouse::Right
#define VXM_MOUSE_BUTTON_MIDDLE    ::tr::Mouse::Middle