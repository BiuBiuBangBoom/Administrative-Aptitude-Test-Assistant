#pragma once

#include "Mode.h"

class Context
{
private:
    std::unique_ptr<ModeStrategy> m_strategy{nullptr};

public:
    void setStrategy(std::unique_ptr<ModeStrategy> strategy);

    std::unique_ptr<ModeStrategy> &getStrategy();

    void executeStrategy();

private:
    std::unique_ptr<ModeStrategy> m_strategy;
};