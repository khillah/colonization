#ifndef ENV_H
#define ENV_H

#include "col.h"
#include "objs.h"
#include "csv.h"

namespace col{
	using Terr = uint8;
	using TerrId = uint8;
	using Terrs = boost::multi_array<Terr, 2>;
	
	using Icons = map<Icon::Id, Icon>;
	using Players = map<Player::Id, Player>;
		
	using UnitTypes = map<UnitType::Id, UnitType>;

	using TerrTypes = map<TerrType::Id, TerrType>;
	
			
	TerrTypes load_terr_types();
	UnitTypes load_unit_types();

	
	
	//using IconsByLoc = map<Coords, IconsLst>;
	/*
	template <typename Cnt>
	struct Filtered {
		using baseiter = typename Cnt::const_iterator;
		using func_type = function<bool(Icon const&)>;
		
		Cnt const* cnt;
		func_type fun;
		
		struct Iter{
			baseiter p;
			func_type fun;
			
			Iter(baseiter p_, func_type fun) {
				//p(p_)
				this->fun = fun;
			}
			
			
			bool operator!= (const Iter& other) {
				return p != other.p;
			}
			
			Iter& operator++() {
				++p;
				return *this;
			}

			const typename Cnt::mapped_type & operator*() {
				 return (*p).second;
			}
		};
			
		Filtered(const Cnt &cnt, func_type fun) {
			this->cnt = &cnt;
			this->fun = fun;
		}
		
		Iter begin() const {
			return Iter(cnt->cbegin(), fun);
		}

		Iter end() const {
			return Iter(cnt->cend(), fun);
		}
		
	};
	*/
	
	/* Dir code is yx in mod 3-1 (2 -> -1)
	00 0  -1,-1
	01 1  -1,0 
	02 2  -1,1
	10 3  0,-1
	11 4  0,0
	12 5  0,1
	20 6  1,-1
	21 7  1,0
	22 8  1,1
	*/

	enum class Dir: int8{
		Q=0, W=1, E=2,
		A=3,      D=5,
		Z=6, X=7, C=8
	};
	
	inline Coords vec4dir(Dir const& d) {
		auto n = static_cast<int8>(d);
		return Coords((n % 3) - 1, (n / 3) - 1);
	}
	
	inline Dir dir4vec(Coords const& d) {
		return static_cast<Dir>((d[0] + 1) + (d[1] + 1) * 3);
	}
	
	namespace action {
		struct Action {
			
		};
				
		struct AttackMove: Action {
			Icon* icon;
			Dir dir;
			AttackMove(Icon & iid, Dir const& dirr) {
				icon = &iid;
				dir = dirr;
			}
		};
				
		struct Turn: Action {

		};
	}
	
	struct Env{
		// terrain layer - const
		// game layer - forest, plow, building, unit, resource, unit
		
		Coord w, h;
		
		Terrs terrs;  // static terr_id
		
		//IconsAt      // by loc
		Icons icons;  // by id

		// uint cur_x, cur_y;  

		
		uint32 mod;

		Players players;   // ls of player id

		Player* curr_player;		
		uint32 turn_no;
		
		UnitTypes uts; // static
		TerrTypes tts;
		
		Env() {
			mod = 0;
			curr_player = nullptr;
			turn_no = 0;
			w = h = 0;
			
			cout << "Loading terr types...";
			tts = load_terr_types();
			cout << " " << tts.size() << " loaded." << endl;
			
			cout << "Loading unit types...";
			uts = load_unit_types();
			cout << " " << uts.size() << " loaded." << endl;
		}
		
		Player* get_current_player() {
			return curr_player;
		}
		
		void exec(action::Turn const& a) {
			if (curr_player == nullptr) {
				throw runtime_error("curr_player is nullish: cannot end turn");
			}
			
			auto p = players.find(curr_player->id + 1);
			if (p != players.end()) {
				curr_player = &(*p).second;
			}
			else {
				curr_player = &players.at(0);
				++turn_no;
			}	

			++mod;
		}
		
		
		Icon::Id create_icon(UnitType::Id type_id, Player::Id player_id, Coords xy) {
			Icon::Id id = icons.size();
			
			if (uts.find(type_id) == uts.end()) {
				throw runtime_error(str(format("unit types: id not found: %||") % type_id));
			}
						
			icons[id] = Icon(
				id,
				uts.at(type_id),
				xy,
				players.at(player_id)
			);
			++mod;
			return id;		
		}
		
		void destroy_icon(Icon::Id id) {
			icons.erase(id);
			++mod;
		}
		
		TerrId get_terr_id(Coord x, Coord y) const {
			return terrs[y][x];
		}
		
		TerrId& terr_id(Coord x, Coord y) {
			return terrs[y][x];
		}
		
		TerrType& get_terr_type(Coords const& xy) {
			return tts.at(get_terr_id(xy[0], xy[1]));
		}
		
		Icon const* get_icon_at(Coords const& xy) const {
			for (auto &p: icons) {				
				auto &c = p.second;
				if (c.pos == xy) {
					return &c;
				}
			}
			return nullptr;			
		}
		
		
		
		Icon& icon4id(Icon::Id const& id) {
			return icons.at(id);			
		}
		
		
		Icon* get_icon_at(Coords const& xy) {
			for (auto &p: icons) {				
				auto &c = p.second;
				if (c.pos == xy) {
					return &c;
				}
			}
			return nullptr;
			
		}
		
		Icon& ref_icon_at(Coords const& pos) {
			auto p = get_icon_at(pos);
			if (p) {
				return *p;
			}
			throw runtime_error("no icon at location");
		}
		
		bool can_attack_move(Icon const& u, Dir const& dir) {
			// square empty
			auto& ut = *(u.type);
			auto dest = u.pos + vec4dir(dir);
			auto tt = get_terr_type(dest);
			
			if (!(ut.movement_type & tt.movement_type)) {
				return false;
				// throw runtime_error("cant move - noncompatible type");
			}
			// compatible terrain type
				
			if (ut.movement < tt.movement_cost + u.movement_used) {
				return false;
				// throw runtime_error("cant move - not enough moves");
			}
			// enough movement
			
			auto x = get_icon_at(dest);
			if (x != nullptr && x->player == u.player) {
				return 0;				
				//throw std::runtime_error("cannot move: square already occupied");
			}
			// dest square empty or occupied by enemy
			
			return true;			
		}
		
		
		
		void exec(action::AttackMove const& a) {
			
			Icon* p = a.icon;
			
			if (!can_attack_move(*p, a.dir)) {
				throw std::runtime_error("cannot attack move");			
			}
			
			auto dest = p->pos + vec4dir(a.dir);
			auto q = get_icon_at(dest);
			auto tt = get_terr_type(dest);
			
			if (q == nullptr) {
				// move
				
				p->movement_used += tt.movement_cost;
				p->pos = dest;
			}
			else {
				//attack
				auto attack_base = p->type->attack;
				auto attack = attack_base;
				auto combat_base = q->type->combat;
				auto combat = combat_base + uint8(0.25 * tt.defensive * combat_base);

				assert(attack > 0);

				auto r = roll(0, attack + combat);

				// cout << "combat " << r << endl;

				if (r <= attack) {
					p->movement_used = p->type->movement;
					p->pos = dest;

					destroy_icon(q->id);
				}
				else {
					destroy_icon(p->id);
				}

			}
			
			++mod;			
		}
		
		
		//RangeXY<Icons> all(Coord x, Coord y) const {
		//	return RangeXY<Icons>(icons, x, y);			
		//}
		
		
		
		
		
		
		//Icon::Id create_icon(istream &f) {
		//	Icon icon(read_obj<Icon>(*this, f));
		//	env.icons[icon.id] = icon;
		//	return icon.id;
		//}
				
				
		Icon& get(Icon::Id id) {
			return icons.at(id);
		}
		
		
		void set_owner(const Icon::Id &icon_id, const Player::Id &player_id) {
			icons.at(icon_id).player = &players.at(player_id);
			++mod;			
		}
		
		void add_player(const Player &t) {
			//assert(icon.id > 0);
			cout << "Adding player: " << t.id << endl;
			players[t.id] = t;
			if (curr_player == nullptr) {
				curr_player = &players.at(t.id);
			}
			++mod;
		}
		
		Player& get_player(const Player::Id &id) {
			return players[id];			
		}
		
		const Player& get_player(const Player::Id &id) const {
			auto p = players.find(id);
			if (p != players.end()) {
				return (*p).second;
			}
			else {
				throw std::runtime_error(str(format("no player with id=%||") % id));
			}
		}
		
		void del_player(const Player::Id &id) {
			players.erase(id);
			++mod;
		}
		
		Player::Id next_key_player() {
			return players.size();
		}
		
		
		
		

	};
	

	
	namespace io {
		template <typename C>
		typename C::mapped_type* read_ptr(C &cs, istream &f) {
			return &cs.at(read<typename C::key_type>(f));
		}

		template <typename T>
		T read_obj(Env &env, istream &f);

		template <typename T>
		size_t write_obj(ostream &f, T const &t);
	}
	

}

#endif