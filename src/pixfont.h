#ifndef PIXFONT_H
#define PIXFONT_H


#include "col.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace col {


	struct PixFont{

		struct PixGlyph{
			sf::Rect<int> rect;

		};

		void render_glyph(
			sf::Image &trg,
			int const& t_x,
			int const& t_y,
			PixGlyph const& g,
			sf::Color const& fgcol
			//sf::Color const& bgcol
		) const {

			int g_x = g.rect.left;
			int g_y = g.rect.top;

			for (int i = 0; i < g.rect.width; ++i) {
				for (int j = 0; j < g.rect.height; ++j){

					auto c = this->img.getPixel(g_x + i, g_y + j);
					if (c.a) {
						trg.setPixel(t_x + i, t_y + j, fgcol);
					}
					else {
						//trg.setPixel(t_x + i, t_y + j, bgcol);
					}

				}
			}
		}





		struct PixReader {

			struct OutOfBound{};

			sf::Image const* img;
			PixReader(sf::Image const& img) {
				this->img = &img;
			}

			sf::Color getpix(uint16 i, uint16 j) {
				auto dim = img->getSize();
				if (i >= dim.x || j >= dim.y) {
					throw OutOfBound();
				}
				return img->getPixel(i,j);
			}
		};


		map<uint16, PixGlyph> glyphs;
		sf::Texture tex;
		sf::Image img;

		PixFont() {}

		void load(string const& path) {

			if (!tex.loadFromFile(path)) {
				throw std::runtime_error("cant't load font file: " + path);
			}
			tex.setSmooth(false);


			img = tex.copyToImage();

			auto ind = img.getPixel(0,1);

			PixReader r(img);

			uint16 i = 0, j = 0;
			uint16 i_begin = 0, i_end = 0;
			uint16 j_begin = 0, j_end = 0;

			uint16 char_code = 0;

			while (1) try {
				i = 0;

				// find v.ind
				while (r.getpix(0,j) != ind) ++j;
				j_begin = j;

				// read v.ind
				while (r.getpix(0,j) == ind) ++j;
				j_end = j;

				j = j + 1;

				while (1) try {
					// find horizontal indicator
					while (r.getpix(i,j) != ind) ++i;
					i_begin = i;

					// read h.ind
					while (r.getpix(i,j) == ind) ++i;
					i_end = i;

					auto &g = glyphs[char_code];
					g.rect.top = j_begin;
					g.rect.height = j_end - j_begin;
					g.rect.left = i_begin;
					g.rect.width = i_end - i_begin;

					++char_code;
				}
				catch (PixReader::OutOfBound) {
					break;
				}
			}
			catch (PixReader::OutOfBound){
				break;
			}


		}


	};

}

#endif
