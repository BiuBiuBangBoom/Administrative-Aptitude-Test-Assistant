#include "Context.h"

void Context::setStrategy(std::unique_ptr<ModeStrategy> strategy)
{
    m_strategy = std::move(strategy);
}

void Context::executeStrategy()
{
    if (m_strategy)
    {
        m_strategy->execute();
    }
}