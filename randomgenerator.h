#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <string>
#include <memory>

class RandomGenerator {
public:
    static RandomGenerator& instance();
    int nextInt(int min, int max);
    char getChar(const std::string& chars);

private:
    RandomGenerator();
    ~RandomGenerator() = default;  // ← добавь эту строку
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif