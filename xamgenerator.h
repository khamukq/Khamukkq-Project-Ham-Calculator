#ifndef XAMGENERATOR_H
#define XAMGENERATOR_H

#include <vector>
#include <string>
#include "passwordgenerator.h"

class XamGenerator : public PasswordGenerator {
public:
    std::string generate(const GeneratorParams& params) override;
};

#endif