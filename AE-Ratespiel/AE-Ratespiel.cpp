#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <thread>

#include "Windows.h"

int main()
{
    SetConsoleTitleA("Ratespiel!");

    std::cout << "Willkommen beim Ratespiel!" << std::endl;

    std::random_device m_RandomDevice;
    std::mt19937_64 m_RandomGenerator(m_RandomDevice());
    std::uniform_int_distribution<> m_Distributor(1, 10);
    std::string m_Input;
    
    int m_TargetValue = m_Distributor(m_RandomGenerator);

    for (int i = 0; i < 3; i++)
    {
        std::string m_retryCount = std::to_string(3 - i);
        std::cout << "Sie haben " << m_retryCount << (m_retryCount == "1" ? " versuch!" : " versuche!") << std::endl;
        std::cout << "\r\nGeben Sie Ihre Zahl ein: ";

        std::cin >> m_Input;

        try
        {
            int m_InputValue = std::stoi(m_Input);

            if (m_InputValue <= 0 || m_InputValue >= 11)
            {
                std::cout << "Die Eingabe muss zwischen 1 und 10 liegen!" << std::endl;
                i--;
                continue;
            }

            if (m_InputValue == m_TargetValue)
            {
                std::cout << "Herzlichen Glueckwunch! Sie haben die richtige Zahl erraten und garnichts gewonnen!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                return 0;
            }

            if (m_InputValue < m_TargetValue)
                std::cout << "Die gesuchte Zahl ist groesser als " << std::to_string(m_InputValue) << "!" << std::endl;
            else if (m_InputValue > m_TargetValue)
                std::cout << "Die gesuchte Zahl ist kleiner als " << std::to_string(m_InputValue) << "!" << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << std::endl << "Falsche Eingabe!" << std::endl;
            i--;
            continue;
        }
    }

    std::cout << std::endl << std::endl << "Leider haben Sie verloren! Die gesuchte Zahl war " << std::to_string(m_TargetValue) << std::endl << "Vielleicht klappt es ja ein anderes mal!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
