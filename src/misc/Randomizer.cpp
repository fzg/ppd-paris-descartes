#include "Randomizer.hpp"

Randomizer::Randomizer() {
}

Randomizer::~Randomizer() {

}

int Randomizer::Random(int a, int b) {
        std::random_device rd_;
        std::mt19937 gen_(rd_());
	std::uniform_int_distribution<> dis(a, b);
	return dis(gen_);
}
