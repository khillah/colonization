#ifndef BUILD2_H
#define BUILD2_H

#include "objs.h"

namespace col{

	// colonist   spec type, spec level
	// frigate


	struct BuildType{
		using Id = uint32;

		Id id;
		string name;


		BuildType() {}

		BuildType(Id const& id, string const& name = ""):
			id(id),
			name(name)
		{}

		BuildType(vector<string> const& xs) {
			assert(xs.size() >= 2);
			name = trim_copy(xs[0]);
			id = stoi(xs[1]);
		}

	};

	struct Build: Workplace {

		BuildType const* type;
		int8 free_slots;

		Build(BuildType const& type):
			Workplace(),
			type(&type),
			free_slots(3)
		{}

		Build() = default;
		Build(Build &&) = default;
		Build(Build const&) = default;
		Build& operator=(Build const&) = default;


		BuildType::Id get_type_id() const {
			return type->id;
		}

		// Workplace

		PlaceType::type place_type() {
			return PlaceType::Build;
		}


		uint16 get_yield(Item const& item, bool const& is_expert) const {
			return 3;
		}

		bool assign() {
			if (!free_slots) {
				return false;
			}
			free_slots -= 1;
			return true;
		}

		bool leave() {
			if (free_slots < 3) {
				return false;
			}
			free_slots += 1;
			return true;
		}

	};

	using buildp = unique_ptr<Build>;


	ostream& operator<<(ostream &out, Build const& obj);


}

#endif