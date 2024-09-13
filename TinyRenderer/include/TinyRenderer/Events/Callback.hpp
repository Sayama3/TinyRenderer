//
// Created by Sayama on 13/09/2024.
//

#pragma once

#include "Event.hpp"

namespace tr
{
	class Callback
	{
	public:
		virtual ~Callback() = default;
		virtual bool operator()(Event& event) = 0;
	};
}