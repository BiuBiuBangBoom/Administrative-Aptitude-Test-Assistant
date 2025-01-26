#pragma once

#include <memory>
#include <Mode.h>

class ModeStrategy
{
public:
    virtual void execute() = 0;

    virtual void setMode(std::unique_ptr<BaseMode> mode);

    virtual ~ModeStrategy() = default;

    virtual bool processInput();

protected:
    std::unique_ptr<BaseMode> m_mode{nullptr};

private:
    bool m_onStart{true};
};

class RunningMode : public ModeStrategy
{
public:
    RunningMode() = default;

    virtual ~RunningMode() = default;

    virtual void execute() override;
};

class RunningAndTestMode : public ModeStrategy
{
public:
    RunningAndTestMode() = default;

    virtual ~RunningAndTestMode() = default;

    virtual void execute() override;
};

class ExaminationMode : public ModeStrategy
{
public:
    ExaminationMode() = default;

    virtual ~ExaminationMode() = default;

    virtual void execute() override;
};