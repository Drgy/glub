#include <iostream>
#include <functional>
/*includeLibs*/
/*window*/
int main () {
	WindowClass window;

	std::cout << "Creating window..." << std::flush;

	if (!window.create(640, 480, "/*name*/")) {
		std::cout << "FAILED" << std::endl;
		return 1;
	}

	std::cout << "OK" << std::endl;
	/*init*/

	std::function<void()> update = [&] () {
		/*update*/
	};

	window.start(update);

	return 0;
}
