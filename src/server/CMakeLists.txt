project (cc94)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wnarrowing")

set(HEADERS 
	ams.hpp
	enums.hpp
	colony.hpp
	faction.hpp
	makeable.hpp
	col.hpp
	meta.hpp
	macro.hpp
	objs.hpp
	dir.hpp
	phys.hpp
	visenv.hpp
	error.hpp
	item.hpp
	roll.hpp
	prof.hpp
	csv.hpp
	unit.hpp
	field.hpp
	biome.hpp
	control.hpp
	env.hpp
	build.hpp
	terr.hpp
	storage.hpp
	serialize.hpp
	player.hpp
	type_name.hpp
	serialize_inc.hpp
	process.hpp
	base.hpp
	pre.hpp
	remote.hpp
	core.hpp
	workplace.hpp
)

set(SOURCES
	core.cpp
	control.cpp
	workplace.cpp
	storage.cpp
	env.cpp
	serialize.cpp
	field.cpp
	colony.cpp
	prof.cpp
	csv.cpp
	build.cpp
	roll.cpp
	objs.cpp
	unit.cpp
)

add_executable(server ${HEADERS} ${SOURCES})
