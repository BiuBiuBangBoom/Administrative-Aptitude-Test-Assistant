#pragma once

#include "Mode.h"

class Context
{
public:
    void setStrategy(std::unique_ptr<ModeStrategy> strategy);

    void executeStrategy();

private:
    std::unique_ptr<ModeStrategy> m_strategy;
};