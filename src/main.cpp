#include "Context.h"

int main()
{
    Context context;
    std::string input;

    std::cout << "hello!" << std::endl;

    while (true)
    {
        std::cout << "mode list:" << std::endl;
        std::cout << "1. running mode" << std::endl;
        std::cout << "2. examination mode" << std::endl;
        std::cout << "please input mode (1 - 2), or input 'quit' to exit: ";
        std::cin >> input;

        if (input == "quit")
        {
            std::cout << "Bye~" << std::endl;
            break;
        }

        if (input == "1")
        {
            context.setStrategy(std::make_unique<RunningMode>());
        }
        else if (input == "2")
        {
            context.setStrategy(std::make_unique<ExaminationMode>());
        }
        else
        {
            std::cout << "invalid mode" << std::endl;
            continue;
        }

        while (true)
        {
            std::cout << "mode list:" << std::endl;
            std::cout << "1. two digits times one digits : 12 * 1" << std::endl;
            std::cout << "2. one digits plus one digits : 1 + 2" << std::endl;
            std::cout << "3. one digits times one digits : 1 * 2" << std::endl;
            std::cout << "4. three digits divide two digits : 12 厂 123" << std::endl;
            std::cout << "5. fraction compare : 1/2 ? 1/3" << std::endl;

            std::cout << "please input mode (1 - 5), or input 'quit' to exit: ";
            std::cin >> input;

            if (input == "quit")
            {
                std::cout << "Bye~" << std::endl;
                break;
            }

            if (input == "1")
            {
                context.getStrategy()->setMode(std::make_unique<TwoDigitsTimesOneDigit>());
            }
            else if (input == "2")
            {
                context.getStrategy()->setMode(std::make_unique<OneDigitPlusOneDigit>());
            }
            else if (input == "3")
            {
                context.getStrategy()->setMode(std::make_unique<OneDigitTimesOneDigit>());
            }
            else if (input == "4")
            {
                context.getStrategy()->setMode(std::make_unique<ThreeDigitsDivideTwoDigits>());
            }
            else if (input == "5")
            {
                context.getStrategy()->setMode(std::make_unique<FractionCompare>());
            }
            else
            {
                std::cout << "invalid mode" << std::endl;
                continue;
            }

            context.executeStrategy();
        }
    }

    return 0;
}
