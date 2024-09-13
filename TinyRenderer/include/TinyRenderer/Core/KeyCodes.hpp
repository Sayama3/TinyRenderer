//
// Created by Sayama on 13/09/2024.
//

#pragma once

// Imported from GLFW3.h

namespace tr
{
	enum class Key : int {
		/* The unknown key */
		Unknown =            -1,

		Space =              32,
		Apostrophe =         39  /* ' */,
		Comma =              44  /* , */,
		Minus =              45  /* - */,
		Period =             46  /* . */,
		Slash =              47  /* / */,
		Key0 =               48,
		Key1 =               49,
		Key2 =               50,
		Key3 =               51,
		Key4 =               52,
		Key5 =               53,
		Key6 =               54,
		Key7 =               55,
		Key8 =               56,
		Key9 =               57,
		Semicolon =          59  /* ; */,
		Equal =              61  /* = */,
		A =                  65,
		B =                  66,
		C =                  67,
		D =                  68,
		E =                  69,
		F =                  70,
		G =                  71,
		H =                  72,
		I =                  73,
		J =                  74,
		K =                  75,
		L =                  76,
		M =                  77,
		N =                  78,
		O =                  79,
		P =                  80,
		Q =                  81,
		R =                  82,
		S =                  83,
		T =                  84,
		U =                  85,
		V =                  86,
		W =                  87,
		X =                  88,
		Y =                  89,
		Z =                  90,
		LeftBracket =        91,  /* [ */
		Backslash =          92,  /* \ */
		RightBracket =       93,  /* ] */
		GraveAccent =        96,  /* ` */
		World_1 =            161, /* non-US #1 */
		World_2 =            162, /* non-US #2 */

		/*Function keys*/
		Escape =             256,
		Enter =              257,
		Tab =                258,
		Backspace =          259,
		Insert =             260,
		Delete =             261,
		Right =              262,
		Left =               263,
		Down =               264,
		Up =                 265,
		PageUp =             266,
		PageDown =           267,
		Home =               268,
		End =                269,
		CapsLock =           280,
		ScrollLock =         281,
		NumLock =            282,
		PrintScreen =        283,
		Pause =              284,
		F1 =                 290,
		F2 =                 291,
		F3 =                 292,
		F4 =                 293,
		F5 =                 294,
		F6 =                 295,
		F7 =                 296,
		F8 =                 297,
		F9 =                 298,
		F10 =                299,
		F11 =                300,
		F12 =                301,
		F13 =                302,
		F14 =                303,
		F15 =                304,
		F16 =                305,
		F17 =                306,
		F18 =                307,
		F19 =                308,
		F20 =                309,
		F21 =                310,
		F22 =                311,
		F23 =                312,
		F24 =                313,
		F25 =                314,
		KP_0 =               320,
		KP_1 =               321,
		KP_2 =               322,
		KP_3 =               323,
		KP_4 =               324,
		KP_5 =               325,
		KP_6 =               326,
		KP_7 =               327,
		KP_8 =               328,
		KP_9 =               329,
		KPDecimal =          330,
		KPDivide =           331,
		KPMultiply =         332,
		KPSubtract =         333,
		KPAdd =              334,
		KPEnter =            335,
		KPEqual =            336,
		LeftShift =          340,
		LeftControl =        341,
		LeftAlt =            342,
		LeftSuper =          343,
		RightShift =         344,
		RightControl =       345,
		RightAlt =           346,
		RightSuper =         347,
		Menu =               348,
		Last =               Menu,
	};
}

#define TR_KEY_UNKNOWN ::tr::Key::Unknown
#define TR_KEY_SPACE ::tr::Key::Space
#define TR_KEY_APOSTROPHE ::tr::Key::Apostrophe
#define TR_KEY_COMMA ::tr::Key::Comma
#define TR_KEY_MINUS ::tr::Key::Minus
#define TR_KEY_PERIOD ::tr::Key::Period
#define TR_KEY_SLASH ::tr::Key::Slash
#define TR_KEY_0 ::tr::Key::Key0
#define TR_KEY_1 ::tr::Key::Key1
#define TR_KEY_2 ::tr::Key::Key2
#define TR_KEY_3 ::tr::Key::Key3
#define TR_KEY_4 ::tr::Key::Key4
#define TR_KEY_5 ::tr::Key::Key5
#define TR_KEY_6 ::tr::Key::Key6
#define TR_KEY_7 ::tr::Key::Key7
#define TR_KEY_8 ::tr::Key::Key8
#define TR_KEY_9 ::tr::Key::Key9
#define TR_KEY_SEMICOLON ::tr::Key::Semicolon
#define TR_KEY_EQUAL ::tr::Key::Equal
#define TR_KEY_A ::tr::Key::A
#define TR_KEY_B ::tr::Key::B
#define TR_KEY_C ::tr::Key::C
#define TR_KEY_D ::tr::Key::D
#define TR_KEY_E ::tr::Key::E
#define TR_KEY_F ::tr::Key::F
#define TR_KEY_G ::tr::Key::G
#define TR_KEY_H ::tr::Key::H
#define TR_KEY_I ::tr::Key::I
#define TR_KEY_J ::tr::Key::J
#define TR_KEY_K ::tr::Key::K
#define TR_KEY_L ::tr::Key::L
#define TR_KEY_M ::tr::Key::M
#define TR_KEY_N ::tr::Key::N
#define TR_KEY_O ::tr::Key::O
#define TR_KEY_P ::tr::Key::P
#define TR_KEY_Q ::tr::Key::Q
#define TR_KEY_R ::tr::Key::R
#define TR_KEY_S ::tr::Key::S
#define TR_KEY_T ::tr::Key::T
#define TR_KEY_U ::tr::Key::U
#define TR_KEY_V ::tr::Key::V
#define TR_KEY_W ::tr::Key::W
#define TR_KEY_X ::tr::Key::X
#define TR_KEY_Y ::tr::Key::Y
#define TR_KEY_Z ::tr::Key::Z
#define TR_KEY_LEFT_BRACKET ::tr::Key::LeftBracket
#define TR_KEY_BACKSLASH ::tr::Key::Backslash
#define TR_KEY_RIGHT_BRACKET ::tr::Key::RightBracket
#define TR_KEY_GRAVE_ACCENT ::tr::Key::GraveAccent
#define TR_KEY_WORLD_1 ::tr::Key::World_1
#define TR_KEY_WORLD_2 ::tr::Key::World_2
#define TR_KEY_ESCAPE ::tr::Key::Escape
#define TR_KEY_ENTER ::tr::Key::Enter
#define TR_KEY_TAB ::tr::Key::Tab
#define TR_KEY_BACKSPACE ::tr::Key::Backspace
#define TR_KEY_INSERT ::tr::Key::Insert
#define TR_KEY_DELETE ::tr::Key::Delete
#define TR_KEY_RIGHT ::tr::Key::Right
#define TR_KEY_LEFT ::tr::Key::Left
#define TR_KEY_DOWN ::tr::Key::Down
#define TR_KEY_UP ::tr::Key::Up
#define TR_KEY_PAGE_UP ::tr::Key::PageUp
#define TR_KEY_PAGE_DOWN ::tr::Key::PageDown
#define TR_KEY_HOME ::tr::Key::Home
#define TR_KEY_END ::tr::Key::End
#define TR_KEY_CAPS_LOCK ::tr::Key::CapsLock
#define TR_KEY_SCROLL_LOCK ::tr::Key::ScrollLock
#define TR_KEY_NUM_LOCK ::tr::Key::NumLock
#define TR_KEY_PRINT_SCREEN ::tr::Key::PrintScreen
#define TR_KEY_PAUSE ::tr::Key::Pause
#define TR_KEY_F1 ::tr::Key::F1
#define TR_KEY_F2 ::tr::Key::F2
#define TR_KEY_F3 ::tr::Key::F3
#define TR_KEY_F4 ::tr::Key::F4
#define TR_KEY_F5 ::tr::Key::F5
#define TR_KEY_F6 ::tr::Key::F6
#define TR_KEY_F7 ::tr::Key::F7
#define TR_KEY_F8 ::tr::Key::F8
#define TR_KEY_F9 ::tr::Key::F9
#define TR_KEY_F10 ::tr::Key::F10
#define TR_KEY_F11 ::tr::Key::F11
#define TR_KEY_F12 ::tr::Key::F12
#define TR_KEY_F13 ::tr::Key::F13
#define TR_KEY_F14 ::tr::Key::F14
#define TR_KEY_F15 ::tr::Key::F15
#define TR_KEY_F16 ::tr::Key::F16
#define TR_KEY_F17 ::tr::Key::F17
#define TR_KEY_F18 ::tr::Key::F18
#define TR_KEY_F19 ::tr::Key::F19
#define TR_KEY_F20 ::tr::Key::F20
#define TR_KEY_F21 ::tr::Key::F21
#define TR_KEY_F22 ::tr::Key::F22
#define TR_KEY_F23 ::tr::Key::F23
#define TR_KEY_F24 ::tr::Key::F24
#define TR_KEY_F25 ::tr::Key::F25
#define TR_KEY_KP_0 ::tr::Key::KP_0
#define TR_KEY_KP_1 ::tr::Key::KP_1
#define TR_KEY_KP_2 ::tr::Key::KP_2
#define TR_KEY_KP_3 ::tr::Key::KP_3
#define TR_KEY_KP_4 ::tr::Key::KP_4
#define TR_KEY_KP_5 ::tr::Key::KP_5
#define TR_KEY_KP_6 ::tr::Key::KP_6
#define TR_KEY_KP_7 ::tr::Key::KP_7
#define TR_KEY_KP_8 ::tr::Key::KP_8
#define TR_KEY_KP_9 ::tr::Key::KP_9
#define TR_KEY_KP_DECIMAL ::tr::Key::KPDecimal
#define TR_KEY_KP_DIVIDE ::tr::Key::KPDivide
#define TR_KEY_KP_MULTIPLY ::tr::Key::KPMultiply
#define TR_KEY_KP_SUBTRACT ::tr::Key::KPSubtract
#define TR_KEY_KP_ADD ::tr::Key::KPAdd
#define TR_KEY_KP_ENTER ::tr::Key::KPEnter
#define TR_KEY_KP_EQUAL ::tr::Key::KPEqual
#define TR_KEY_LEFT_SHIFT ::tr::Key::LeftShift
#define TR_KEY_LEFT_CONTROL ::tr::Key::LeftControl
#define TR_KEY_LEFT_ALT ::tr::Key::LeftAlt
#define TR_KEY_LEFT_SUPER ::tr::Key::LeftSuper
#define TR_KEY_RIGHT_SHIFT ::tr::Key::RightShift
#define TR_KEY_RIGHT_CONTROL ::tr::Key::RightControl
#define TR_KEY_RIGHT_ALT ::tr::Key::RightAlt
#define TR_KEY_RIGHT_SUPER ::tr::Key::RightSuper
#define TR_KEY_MENU ::tr::Key::Menu
#define TR_KEY_LAST ::tr::Key::Last
