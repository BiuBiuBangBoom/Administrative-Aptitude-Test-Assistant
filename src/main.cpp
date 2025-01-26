#include <string>
#include <iostream>

#include "Context.h"
#include "Mode.h"

int main()
{
    Context context;
    std::string input;

    std::cout << "hello!" << std::endl;

    while (true)
    {
        std::cout << "mode list:" << std::endl;
        std::cout << "1. running mode" << std::endl;
        std::cout << "2. running and test mode" << std::endl;
        std::cout << "3. examination mode" << std::endl;
        std::cout << "please input mode (1 - 3), or input 'quit' to exit: ";
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
            context.setStrategy(std::make_unique<RunningAndTestMode>());
        }
        else if (input == "3")
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
            std::cout << "6. PercentageConvertToFraction : 12%" << std::endl;
            std::cout << "7. three digits times one digits : 123 * 1" << std::endl;
            std::cout << "8. estimate growth : 1234 5.6%" << std::endl;
            std::cout << "9. two digits substaction one digit : 12 - 3" << std::endl;

            std::cout << "please input mode (1 - 8), or input 'quit' to exit: ";
            std::cin >> input;

            if (input == "quit")
            {
                std::cout << "Bye~" << std::endl;
                break;
            }

            switch (std::stoi(input))
            {
            case 1:
                context.getStrategy()->setMode(std::make_unique<TwoDigitsTimesOneDigit>());
                break;
            case 2:
                context.getStrategy()->setMode(std::make_unique<OneDigitPlusOneDigit>());
                break;
            case 3:
                context.getStrategy()->setMode(std::make_unique<OneDigitTimesOneDigit>());
                break;

            case 4:
                context.getStrategy()->setMode(std::make_unique<ThreeDigitsDivideTwoDigits>());
                break;

            case 5:
                context.getStrategy()->setMode(std::make_unique<FractionCompare>());
                break;

            case 6:
                context.getStrategy()->setMode(std::make_unique<PercentageConvertToFraction>());
                break;

            case 7:
                context.getStrategy()->setMode(std::make_unique<ThreeDigitsTimesOneDigit>());
                break;

            case 8:
                context.getStrategy()->setMode(std::make_unique<EstimateGrowth>());
                break;

            case 9:
                context.getStrategy()->setMode(std::make_unique<TwoDigitsSubOneDigit>());
                break;

            default:
                std::cout << "invalid mode" << std::endl;
                continue;
            }

            context.executeStrategy();
        }
    }

    return 0;
}
