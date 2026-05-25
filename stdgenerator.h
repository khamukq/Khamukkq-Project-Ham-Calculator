#ifndef STDGENERATOR_H
#define STDGENERATOR_H

#include "passwordgenerator.h"

class StandardGenerator : public PasswordGenerator {
public:
    std::string generate(const GeneratorParams& params) override;
};

#endif