#include <bspch.h>
#include <brickstone.h>
#include <sandbox/sandbox.h>

bs::Application* getApplication() {

	return new Sandbox();

}