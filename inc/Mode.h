#pragma once

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <memory>
#include <numeric>
#include <random>
#include <vector>
#include <string>
#include <iostream>

class ModeStrategy
{
public:
    virtual void execute() = 0;
    virtual ~ModeStrategy() = default;
};

class BaseMode : public ModeStrategy
{
public:
    virtual void execute() override;

private:
    virtual void generateAndPrintQuestion() = 0;
    bool processInput();
    void printStatics();

protected:
    std::vector<std::string> m_question;
    std::vector<std::string> m_answer;
    std::vector<std::string> m_response;
    std::vector<long long> m_costTime;
};

template <typename Operation>
class ArithmeticMode : public BaseMode
{
public:
    ArithmeticMode(int minA, int maxA, int minB, int maxB);

public:
    virtual void generateAndPrintQuestion() override;

private:
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_numADist;
    std::uniform_int_distribution<> m_numBDist;
};

template <typename Operation>
ArithmeticMode<Operation>::ArithmeticMode(int minA, int maxA, int minB, int maxB)
    : m_gen(m_rd()), m_numADist(minA, maxA), m_numBDist(minB, maxB){};

template <typename Operation>
void ArithmeticMode<Operation>::generateAndPrintQuestion()
{
    Operation op;

    auto numA = m_numADist(m_gen);
    auto numB = m_numBDist(m_gen);

    auto questionStr = std::to_string(numA) + " " + op.symbol() + " " + std::to_string(numB);
    // print question
    std::cout << questionStr << std::endl;

    m_question.push_back(questionStr);
    m_answer.push_back(std::to_string(op.apply(numA, numB)));
}

class Operation
{
public:
    virtual int apply(int a, int b) const = 0;
    virtual std::string symbol() const = 0;
    virtual ~Operation() {}
};

class MultiplyOperation : public Operation
{
public:
    int apply(int a, int b) const override;
    std::string symbol() const override;
};

class AddOperation : public Operation
{
public:
    int apply(int a, int b) const override;
    std::string symbol() const override;
};

class DivideOperation : public Operation
{
public:
    int apply(int a, int b) const override;
    std::string symbol() const override;
};

using TwoDigitsTimesOneDigit = ArithmeticMode<MultiplyOperation>;
using OneDigitPlusOneDigit = ArithmeticMode<AddOperation>;
using OneDigitTimesOneDigit = ArithmeticMode<MultiplyOperation>;
using ThreeDigitsDivideTwoDigits = ArithmeticMode<DivideOperation>;