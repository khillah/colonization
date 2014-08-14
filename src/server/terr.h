#ifndef TERR34_H
#define TERR34_H

#include "phys.h"
#include "biome.h"
#include "objs.h"
#include "colony.h"


namespace col{



	using Alt = uint8;

	Alt const AltNone = 0;
	Alt const AltSea = 1;
	Alt const AltFlat = 2;
	Alt const AltHill = 3;
	Alt const AltMountain = 4;



	struct Terr {
		using Id = Coords;

		Biome biome{BiomeNone};
		Phys phys{PhysNone};
		Alt alt{AltNone};

		vector<Unit*> units;
		Colony* colony{nullptr};


		// Constructors
		//Terr(): biome(BiomePlains), phys(PhysNone), alt(SEA_LEVEL), colony(nullptr) {}

		explicit Terr(Alt const& alt = AltNone, Biome const& biome = BiomeNone, Phys const& phys = PhysNone):
			biome(biome), phys(phys), alt(alt)
		{}

		/*
		move_unit(Unit &u, Place &from) {

		}

		move_cargo(Cargo &c, Place &from) {

		}*/

		// Place
		PlaceType::type place_type() {
			return PlaceType::Terr;
		}

		// Workplace
		uint16 get_yield(Item const& item, bool const& is_expert) const;

		vector<Item> get_proditems() const {
			array<Item,9> field_items = {
				ItemFood,ItemSugar,ItemTobacco,
				ItemCotton,ItemFurs,ItemLumber,
				ItemOre,ItemSilver,ItemFish
			};

			vector<Item> xs;
			for (auto const& item: field_items) {
				if (get_yield(item, 0)) {
					xs.push_back(item);
				}
			}
			return xs;
		}

		int get_space_left() {
			return 999;
		}

		void add(Unit & u) {
			units.push_back(&u);
		}

		void sub(Unit & u) {
			units.erase(find(units.begin(), units.end(), &u));
		}

		bool assign(bool const& exec=1) {
			if (has(PhysWorker)) {
				return false;
			}
			if (exec) {
				add(PhysWorker);
			}
			return true;
		}

		bool leave(bool const& exec=1) {
			if (!has(PhysWorker)) {
				if (!exec) {
					throw Error("no worker to leave this place");
				}
				else {
					throw Critical("no worker to leave this place");
				}
			}
			if (exec) {
				sub(PhysWorker);
			}
			return true;
		}

		// Terr
		Colony& get_colony() {
			assert(colony != nullptr);
			return *colony;
		}

		Colony const& get_colony() const {
			assert(colony != nullptr);
			return *colony;
		}

		bool has_colony() const {
			return colony != nullptr;
		}

		Terr& set_colony(Colony &c) {
			colony = &c;
			return *this;
		}

		bool has_units() const {
			return units.size();
		}

		// features
		bool has(Phys const& p) const {
			return phys & p;
		}

		void add(Phys const& p) {
			phys = phys | p;
		}

		void sub(Phys const& p) {
			phys = phys & (~p);
		}

		Biome const& get_biome() const { return biome; }
		Terr & set_biome(Biome const& biome) { this->biome = biome; return *this; }

		Alt const& get_alt() const { return alt; }
		Terr & set_alt(Alt const& alt) { this->alt = alt; return *this; }

		Travel get_travel() const;

		bool is_water_tile() const {
			return alt == AltSea;
		}

	};









}
#endif