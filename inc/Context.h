#pragma once

#include "Mode.h"

class Context
{
private:
    std::unique_ptr<ModeStrategy> m_strategy;

public:
    void setStrategy(std::unique_ptr<ModeStrategy> strategy);

    void executeStrategy();
};