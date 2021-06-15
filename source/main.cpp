#include "core/sylvestrupp.h"

#include <iostream>

int main() {
	Sylvestrupp slv;
	slv.start();

	HelloMessage msg;
	std::cout << msg.asJson() << std::endl;
}
