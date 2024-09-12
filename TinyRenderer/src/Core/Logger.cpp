//
// Created by Sayama on 11/09/2024.
//

#include "TinyRenderer/Core/Logger.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <iostream>

using namespace std::string_literals;

namespace tr {
	std::string GetLogType(Logger::Type type)
	{
		switch (type) {

			case Logger::Trace: return "Trace"s;
			case Logger::Info: return "Info"s;
			case Logger::Warning: return "Warning"s;
			case Logger::Error: return "Error"s;
		}
		return ""s;
	}

	void Logger::Log(Logger::Type type, std::string function, std::string file, uint64_t line, std::string_view message) {
		std::cout << "[" << GetLogType(type) << "] [" << file << ":" << line << "] - " << message << std::endl;
	}
} // tr