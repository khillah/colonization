project (cc94)
cmake_minimum_required(VERSION 2.6)

find_package(SDL2 REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wnarrowing")

set(HEADERS
	mcts.hpp
	renderer.hpp
	blocks.hpp
	command.hpp
	logic.hpp
	null_ai.hpp
	align.hpp
	event.hpp
	coldef.hpp
	layout.hpp
	view.hpp
	random_module.hpp
	agent.hpp
	props.hpp
	widget.hpp
	runner.hpp
	simple_ai.hpp
	renderer-pre.hpp
	console.hpp
	renderer-gui.hpp
	textrend.hpp
	base.hpp
	exts.hpp
	tree2.hpp
	path.hpp
	conf.hpp
	serialize2.hpp
	marks.hpp
)

set(SOURCES
	blocks.cpp
	null_ai.cpp
	event.cpp
	renderer.cpp
	layout.cpp
	main.cpp
	conf.cpp
	simple_ai.cpp
	logic.cpp
	textrend.cpp
	runner.cpp
	props.cpp
	renderer-pre.cpp
	console.cpp
	../server/build.cpp
)

add_executable(client ${INCLUDES} ${SOURCES})
target_link_libraries(client libSDL2.so libSDL2_image.so libjsoncpp.a)
