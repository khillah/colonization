#pragma once

#include <server/col.hpp>
#include <server/env.hpp>
#include "console.hpp"
#include "layout.hpp"
#include "renderer-pre.hpp"

namespace col {

	void render(Front &app, col::Env & env, col::Console & con, int verbose);
	

	void preload_renderer(Front &app);

	void init_renderer(Console & con);


}

