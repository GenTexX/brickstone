#pragma once

#include <spdlog/spdlog.h>


namespace bs {

	class Log {

	private:

	public:
		template <typename T>
		static void trace(const char* t, const T args...) { spdlog::trace(t, args); }
		static void trace(const char* t) { spdlog::trace(t); }

		template <typename T>
		static void info(const char* i, const T args...) { spdlog::info(i, args); }
		static void info(const char* i) { spdlog::info(i); }

		template <typename T>
		static void warn(const char* w, const T args...) { spdlog::warn(w, args); }
		static void warn(const char* w) { spdlog::warn(w); }

		template <typename T>
		static void critical(const char* w, T args...) { spdlog::critical(w, args); }
		static void critical(const char* w) { spdlog::critical(w); }
		template <typename T>
		static void error(const char* w, const T args...) { spdlog::error(w, args); }
		static void error(const char* w) { spdlog::error(w); }

	};

}