#include <iostream>
#include <cmath>

int main() {
    double U[] = {
        0.349, 0.349, 0.349, 0.349, 0.350,
        0.350, 0.349, 0.350, 0.350, 0.349
    };

    int n = 10;
    double R = 12.0;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += U[i];
    }

    double U_avg = sum / n;
    double I[10];
    double lnI[10];

    for (int i = 0; i < n; i++) {
        I[i] = U[i] / R;
        lnI[i] = log(I[i]);
    }

    std::cout << "\nI = U / R (R = 12):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "I[" << i + 1 << "] = " << I[i] << " A" << std::endl;
    }

    std::cout << "\nln(I_k):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "lnI[" << i + 1 << "] = " << lnI[i] << std::endl;
    }

    return 0;
}