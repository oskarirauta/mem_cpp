#pragma once

#include <string>

class mem_t {

	public:

		enum type { kb, mb, gb, percent };

		class size {

			friend mem_t;

			private:
				double _size;
				double _total;

				double value(mem_t::type _type) const;

				size() : _size(0), _total(0) {}
				size(const double& s, const double& t) : _size(s), _total(t) {}

			public:

				double operator [](mem_t::type _type) const;
				std::string to_string(mem_t::type _type = mem_t::type::kb) const;

				inline double kb() const { return this -> operator[](mem_t::kb); }
				inline double mb() const { return this -> operator[](mem_t::mb); }
				inline double gb() const { return this -> operator[](mem_t::gb); }
				inline double percent() const { return this -> operator[](mem_t::percent); }

		};

		struct store {

			size total;
			size used;
			size free;

		};

		store ram;
		store swap;

		void update();
		mem_t();
};
