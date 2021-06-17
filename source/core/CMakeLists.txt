add_library(Core
	peer.cpp
	sylvestrupp.cpp
	messages.cpp
)

target_link_libraries(Core Tools)
