#pragma once

namespace bs {

	class Application {
		
	public:
		Application();
		virtual ~Application();

		virtual void init();
		virtual void run();

	};

}