#include <iostream>
#include "mem.hpp"

int main(int argc, char **argv) {

	std::cout << "mem_cpp test\n" << std::endl;

	mem_t* mem = new mem_t();

	std::cout << "ram total:  " << mem -> ram.total.to_string(mem_t::kb) << "kb / " <<
			mem -> ram.total[mem_t::mb] << "mb / " << mem -> ram.total[mem_t::gb] << "gb " <<
			mem -> ram.total[mem_t::percent] << "%" << std::endl;

	std::cout << "ram used:   " << mem -> ram.used.to_string(mem_t::kb) << "kb / " <<
			mem -> ram.used[mem_t::mb] << "mb / " << mem -> ram.used[mem_t::gb] << "gb " <<
			mem -> ram.used[mem_t::percent] << "%" << std::endl;

	std::cout << "ram free:   " << mem -> ram.free.to_string(mem_t::kb) << "kb / " <<
			mem -> ram.free[mem_t::mb] << "mb / " << mem -> ram.free[mem_t::gb] << "gb " <<
			mem -> ram.free[mem_t::percent] << "%" << "\n" << std::endl;

        std::cout << "swap total: " << mem -> swap.total.to_string(mem_t::kb) << "kb / " <<
                        mem -> swap.total[mem_t::mb] << "mb / " << mem -> swap.total[mem_t::gb] << "gb " <<
                        mem -> swap.total[mem_t::percent] << "%" << std::endl;

        std::cout << "swap used:  " << mem -> swap.used.to_string(mem_t::kb) << "kb / " <<
                        mem -> swap.used[mem_t::mb] << "mb / " << mem -> swap.used[mem_t::gb] << "gb " <<
                        mem -> swap.used[mem_t::percent] << "%" << std::endl;

        std::cout << "swap free:  " << mem -> swap.free.to_string(mem_t::kb) << "kb / " <<
                        mem -> swap.free[mem_t::mb] << "mb / " << mem -> swap.free[mem_t::gb] << "gb " <<
                        mem -> swap.free[mem_t::percent] << "%" << "\n" << std::endl;

	delete mem;

	return 0;
}
