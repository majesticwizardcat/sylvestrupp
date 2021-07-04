add_library(Core
	peer.cpp
	sylvestrupp.cpp
	messages.cpp
	marabu-objects.cpp
	network.cpp
)

target_link_libraries(Core Tools)
