#include <cmath>
#include <fstream>
#include <filesystem>
#include "common.hpp"
#include "logger.hpp"
#include "mem.hpp"

static double size_division(double val) {

	if ((int)val < 103 )
		return 0;

	val = val / 1024;
	int v = (int)((val * 10) + 0.5);
	return (double)v * 0.1;
}

double mem_t::size::operator [](mem_t::type _type) const {

	return this -> value(_type);
}

std::string mem_t::size::to_string(mem_t::type _type) const {

	return common::to_string(this -> value(_type));
}

double mem_t::size::value(mem_t::type _type) const {

	if ( _type == mem_t::kb )
		return this -> _size;
	else if ( this -> _size == 0 )
		return 0;

	// percentage here, if kb <= 1030
	if ( this -> _size == 0 && _type == mem_t::percent )
		return (double)0;
	else if ( this -> _total == 0 && _type == mem_t::percent )
		return (double)100.0;
	else if ( this -> _total > 0 && this -> _total <= 104858 && _type == mem_t::percent ) {
		double p = this -> _size / this -> _total;
		unsigned long ip = static_cast<unsigned long>(p * 10000 + 5);
		ip *= 0.1;
		return (double)ip * 0.1;
	}

	double _mb;
	if ( this -> _total > this -> _size && this -> _size < 103 )
		_mb = 0;
	else if ( this -> _total > this -> _size && this -> _size > this -> _total - 10 )
		_mb = this -> _total / 1024;
	else _mb = size_division(this -> _size);

	if ( _type == mem_t::mb )
		return _mb;
	else if ( _type == mem_t::percent ) {

		double p = _mb / ( this -> _total / 1024 );
		unsigned long ip = static_cast<unsigned long>(p * 10000 + 5);
		ip *= 0.1;
		return (double)ip * 0.1;
	}

	double _gb;
	if ( this -> _total > this -> _size && _mb < 103 )
		_gb = 0;
	else if ( this -> _total > this -> _size && _mb > (( this -> _total / 1024 ) - 10 ))
		_gb = this -> _total / 1024 / 1024;
	else _gb = size_division(_mb);

	return _gb;
}

void mem_t::update() {

	if ( !std::filesystem::exists("/proc/meminfo")) {

		logger::error["meminfo"] << "cannot access /proc/meminfo" << std::endl;
		return;
	}

	std::fstream fd("/proc/meminfo", std::ios::in);

	if ( !fd.good()) {

		if ( fd.is_open())
			fd.close();
		logger::error["meminfo"] << "cannot read /proc/meminfo" << std::endl;
		return;
	}

	unsigned long mem_total = 0;
	unsigned long mem_used = 0;
	unsigned long mem_free = 0;
	unsigned long swap_total = 0;
	unsigned long swap_used = 0;
	unsigned long swap_free = 0;

	std::string line;
	while ( std::getline(fd, line)) {

		std::string key, value;
		if ( auto pos = line.find_first_of(':'); pos != std::string::npos ) {

			key = common::to_lower(common::trim_ws(line.substr(0, pos)));
			value = common::trim_ws(line.substr(pos + 1, line.size() - ( pos + 1 )));
			if ( !std::isdigit(value.front()))
				continue;

		} else continue;

		if ( !common::is_any_of(key, { "memtotal", "memfree", "swaptotal", "swapfree" }))
			continue;

		if ( auto pos = value.find_first_not_of("1234567890"); pos != std::string::npos )
			value = common::trim_ws(value.substr(0, pos));

		unsigned long v;
		try {
			v = std::stoul(value.empty() ? "0" : value);
		} catch ( const std::exception& e ) {
			logger::error["meminfo"] << "failure to parse '" << key << "'" << std::endl;
			continue;
		}

		if ( key == "memtotal" ) mem_total = v;
		else if ( key == "memfree" ) mem_free = v;
		else if ( key == "swaptotal" ) swap_total = v;
		else if ( key == "swapfree" ) swap_free = v;
	}

	fd.close();

	if ( mem_total >= mem_free )
		mem_used = mem_total - mem_free;
	if ( swap_total >= swap_free )
		swap_used = swap_total - swap_free;

	this -> ram.total = mem_t::size(mem_total, 0);
	this -> ram.used = mem_t::size(mem_used, mem_total);
	this -> ram.free = mem_t::size(mem_free, mem_total);

	this -> swap.total = mem_t::size(swap_total, 0);
	this -> swap.used = mem_t::size(swap_used, swap_total);
	this -> swap.free = mem_t::size(swap_free, swap_total);

}

mem_t::mem_t() {

	this -> update();
}
