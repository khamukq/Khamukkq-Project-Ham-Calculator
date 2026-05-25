#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <string>

struct GeneratorParams {
    bool useUppercase = true;
    bool useDigits = true;
    bool useSymbols = true;
    int length = 12;
    int wordCount = 3;
    bool useHyphens = true;
};

class PasswordGenerator {
public:
    virtual ~PasswordGenerator() = default;
    virtual std::string generate(const GeneratorParams& params) = 0;
};

#endif