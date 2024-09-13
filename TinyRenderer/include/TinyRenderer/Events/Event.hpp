//
// Created by Sayama on 13/09/2024.
//

#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <functional>

#ifndef BIT
#define BIT(X) (1 << X)
#endif

namespace tr {

	enum class EventType : int {
		None = 0,
		WindowClose, WindowResize, WindowMinify, WindowFocus, WindowLostFocus, WindowMoved, /*WindowDrop,*/
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonRepeat, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

	enum EventCategory : int {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	class Event
	{
		friend class EventDispatcher;
	public:
		bool m_Handled = false;

		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string string() const { return GetName(); }
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool>(T&);
	private:
		Event& m_Event;
	public:
		inline EventDispatcher(Event& event) : m_Event(event)
		{
		}

		// F is deduced by the compiler
		template<typename T, typename F>
		inline bool Dispatch(const F& func) {
			if(m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.string();
	}

	using EventCallBackFn = std::function<void(::tr::Event&)>;

} // tr

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; } \
                                virtual EventType GetEventType() const override { return GetStaticType(); } \
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
