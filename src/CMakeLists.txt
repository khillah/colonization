project (cc94)
cmake_minimum_required(VERSION 2.6)

find_package(SDL2 REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14")

include_directories(.)

set(HEADERS
	server/ams.hpp
	server/enums.hpp
	server/colony.hpp
	server/faction.hpp
	server/makeable.hpp
	server/col.hpp
	server/meta.hpp
	server/macro.hpp
	server/objs.hpp
	server/dir.hpp
	server/phys.hpp
	server/visenv.hpp
	server/error.hpp
	server/item.hpp
	server/roll.hpp
	server/prof.hpp
	server/csv.hpp
	server/unit.hpp
	server/field.hpp
	server/biome.hpp
	server/control.hpp
	server/env.hpp
	server/build.hpp
	server/terr.hpp
	server/storage.hpp
	server/serialize.hpp
	server/player.hpp
	server/type_name.hpp
	server/serialize_inc.hpp
	server/process.hpp
	server/base.hpp
	server/pre.hpp
	server/remote.hpp
	server/core.hpp
	server/workplace.hpp
	client/mcts.hpp
	client/renderer.hpp
	client/blocks.hpp
	client/command.hpp
	client/logic.hpp
	client/null_ai.hpp
	client/align.hpp
	client/event.hpp
	client/coldef.hpp
	client/layout.hpp
	client/view.hpp
	client/random_module.hpp
	client/agent.hpp
	client/props.hpp
	client/widget.hpp
	client/runner.hpp
	client/simple_ai.hpp
	client/renderer-pre.hpp
	client/console.hpp
	client/renderer-gui.hpp
	client/textrend.hpp
	client/base.hpp
	client/exts.hpp
	client/tree2.hpp
	client/path.hpp
	client/conf.hpp
	client/serialize2.hpp
	client/marks.hpp
	front/my.hpp
	front/shader.hpp
	front/color.hpp
	front/glm.hpp
	front/pixfont.hpp
	front/base.hpp
	front/input.hpp
	front/front.hpp
	ext/aga3.hpp
	ext/filesys.hpp
	ext/format.hpp
	ext/bitop.hpp
	ext/random.hpp
	ext/fail.hpp
	ext/aga2.hpp
	ext/geo2.hpp
	ext/vals.hpp
	ext/cstring.hpp
	ext/geo3.hpp
	ext/ext.hpp
	ext/darray.hpp
	ext/darray2.hpp
	catch/catch.hpp
)

set(SOURCES
	server/core.cpp
	server/control.cpp
	server/workplace.cpp
	server/storage.cpp
	server/env.cpp
	server/serialize.cpp
	server/field.cpp
	server/colony.cpp
	server/prof.cpp
	server/csv.cpp
	server/build.cpp
	server/roll.cpp
	server/objs.cpp
	server/unit.cpp
	client/blocks.cpp
	client/null_ai.cpp
	client/event.cpp
	client/renderer.cpp
	client/layout.cpp
	client/main.cpp
	client/conf.cpp
	client/simple_ai.cpp
	client/logic.cpp
	client/textrend.cpp
	client/runner.cpp
	client/props.cpp
	client/renderer-pre.cpp
	client/console.cpp
	front/input.cpp
	front/pixfont.cpp
	front/front.cpp
	front/my.cpp
	lodepng/lodepng.cpp
)

add_executable(cc94 ${INCLUDES} ${SOURCES})
target_link_libraries(cc94 libSDL2.so libSDL2_image.so libjsoncpp.a libGLEW.so libGL.so)
