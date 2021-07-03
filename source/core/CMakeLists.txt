add_library(Core
	peer.cpp
	sylvestrupp.cpp
	messages.cpp
	marabu-objects.cpp
)

target_link_libraries(Core Tools)
