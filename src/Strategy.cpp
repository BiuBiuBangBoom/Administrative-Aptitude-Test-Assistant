#include <string>
#include <iostream>

#include "Strategy.h"
#include "Mode.h"
#include "Common.h"

void ModeStrategy::setMode(std::unique_ptr<BaseMode> mode)
{
    m_mode = std::move(mode);
    m_onStart = true;
}

bool ModeStrategy::processInput()
{
    std::string str;
    std::cout << "input:";

    if (m_onStart)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        m_onStart = false;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::getline(std::cin, str);
    auto end = std::chrono::high_resolution_clock::now();

    if (str == "quit")
    {
        return false;
    }

    auto costTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();

    m_mode->m_costTime.push_back(costTime);
    m_mode->m_response.push_back(str);

    return true;
}

void RunningMode::execute()
{
    bool continueFlag = true;
    auto index = 0;

    while (continueFlag)
    {
        std::cout << "-------------------------------------------" << std::endl;

        std::cout << "question " << index + 1 << std::endl;

        m_mode->generateAndPrintQuestion();
        continueFlag = processInput();

        if (continueFlag)
        {
            std::cout << "correct answer: " << m_mode->m_answer[index] << std::endl;
            std::cout << "cost time:      " << std::fixed << std::setprecision(3)
                      << static_cast<double>(m_mode->m_costTime[index]) / 1000 << "s"
                      << std::endl;
        }

        index++;
    }
}

void RunningAndTestMode::execute()
{
    bool continueFlag = true;
    auto index = 0;

    while (continueFlag)
    {
        std::cout << "-------------------------------------------" << std::endl;

        std::cout << "question " << index + 1 << std::endl;

        m_mode->generateAndPrintQuestion();
        continueFlag = processInput();

        if (continueFlag)
        {
            std::cout << "correct answer: " << m_mode->m_answer[index] << std::endl;
            std::cout << "cost time:      " << std::fixed << std::setprecision(3)
                      << static_cast<double>(m_mode->m_costTime[index]) / 1000 << "s"
                      << std::endl;

            if (m_mode->checkAnswer(index))
            {
                std::cout << greenStr("correct") << std::endl;
            }
            else
            {
                std::cout << redStr("wrong") << std::endl;
            }
        }

        index++;
    }

    m_mode->printStatics();
}

void ExaminationMode::execute()
{
    bool continueFlag = true;

    auto index = 0;

    while (continueFlag)
    {
        std::cout << "question " << index + 1 << std::endl;

        m_mode->generateAndPrintQuestion();

        continueFlag = processInput();

        std::cout << "-------------------------------------------" << std::endl;

        index++;
    }

    m_mode->printStatics();
}