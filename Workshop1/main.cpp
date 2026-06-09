#include <iostream>

int main() {
    double U[] = {
        0.3512, 0.3506, 0.3513, 0.3513, 0.3510, 0.3502, 0.3500, 0.3501, 0.3500, 0.3503,
        0.3503, 0.3504, 0.3504, 0.3509, 0.3505, 0.3505, 0.3507, 0.3508, 0.3512, 0.3509,
        0.3510, 0.3509, 0.3510, 0.3512, 0.3511, 0.3516, 0.3512, 0.3510, 0.3509, 0.3511,
        0.3500, 0.3501, 0.3501, 0.3500, 0.3504, 0.3501, 0.3502, 0.3500, 0.3511, 0.3514,
        0.3513, 0.3511, 0.3513, 0.3500, 0.3499, 0.3501, 0.3514, 0.3513, 0.3502, 0.3504
    };

    int n = 50;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += U[i];
    }

    double U_avg = sum / n;

    double d[50];
    double d_squared[50];

    for (int i = 0; i < n; i++) {
        d[i] = U[i] - U_avg;
        d_squared[i] = d[i] * d[i];
    }

    std::cout << "U_average = " << U_avg << std::endl;
    std::cout << "\nd (random deviations):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "d[" << i + 1 << "] = " << d[i] << std::endl;
    }

    std::cout << "\nd^2:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "d_squared[" << i + 1 << "] = " << d_squared[i] << std::endl;
    }

    return 0;
}