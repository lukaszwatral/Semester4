#include <iostream>

int main()
{
    int wartosci_funkcji[10];
    for (int i = 0; i < 10; i++) {
        wartosci_funkcji[i] = 2*i*i*i + 3*i*i - i + 5;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << wartosci_funkcji[i] << "\n";
    }
}