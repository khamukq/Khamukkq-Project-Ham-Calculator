#include "randomgenerator.h"
#include <random>
#include <ctime>

struct RandomGenerator::Impl {
    std::mt19937 rng;
    Impl() : rng(static_cast<unsigned>(std::time(nullptr))) {}
};

RandomGenerator::RandomGenerator() : pImpl(std::make_unique<Impl>()) {}

RandomGenerator& RandomGenerator::instance() {
    static RandomGenerator inst;
    return inst;
}

int RandomGenerator::nextInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(pImpl->rng);
}

char RandomGenerator::getChar(const std::string& chars) {
    if (chars.empty()) return '\0';
    return chars[nextInt(0, chars.size() - 1)];
}