#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace bs {

	class Log {

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	};

}

#define BS_CORE_TRACE(...)	::bs::Log::getCoreLogger()->trace(__VA_ARGS__)
#define BS_CORE_INFO(...)	::bs::Log::getCoreLogger()->info(__VA_ARGS__)
#define BS_CORE_WARN(...)	::bs::Log::getCoreLogger()->warn(__VA_ARGS__)
#define BS_CORE_ERROR(...)	::bs::Log::getCoreLogger()->error(__VA_ARGS__)
#define BS_CORE_FATAL(...)	::bs::Log::getCoreLogger()->fatal(__VA_ARGS__)