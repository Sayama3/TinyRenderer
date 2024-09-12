//
// Created by Sayama on 11/09/2024.
//

#pragma once

#include <string_view>
#include <format>

namespace tr {

	class Logger
	{
	public:
		enum Type
		{
			Trace,
			Info,
			Warning,
			Error,
		};
	public:
		static void Log(Type type, std::string function, std::string file, uint64_t line, std::string_view message);
	};

} // tr

#define TR_TRACE(...) tr::Logger::Log(tr::Logger::Type::Trace, __FUNCTION__, __FILE__ , __LINE__, std::format(__VA_ARGS__))
#define TR_INFO(...) tr::Logger::Log(tr::Logger::Type::Info, __FUNCTION__, __FILE__ , __LINE__, std::format(__VA_ARGS__))
#define TR_WARNING(...) tr::Logger::Log(tr::Logger::Type::Warning, __FUNCTION__, __FILE__ , __LINE__, std::format(__VA_ARGS__))
#define TR_ERROR(...) tr::Logger::Log(tr::Logger::Type::Error, __FUNCTION__, __FILE__ , __LINE__, std::format(__VA_ARGS__))
#define TR_ASSERT(condition, ...) if(!(condition)) TR_ERROR(__VA_ARGS__)
#define TR_PROFILE_FUNCTION()
