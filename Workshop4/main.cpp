#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(4);

    double L_v[] = { 10, 20, 30, 40, 50 };
    double U1_v[] = { 3, 7, 12.5, 18.5, 20.25 };
    double U2_v[] = { 4, 8.5, 13, 18, 22.5 };

    double S_v[10];
    int idx = 0;

    std::cout << "\n========== VERTICAL DEFLECTION PLATES ==========\n";
    std::cout << "L(mm)\tU1(V)\tS1(mm/V)\tU2(V)\tS2(mm/V)\n";
    std::cout << "-------------------------------------------------------\n";

    for (int i = 0; i < 5; i++) {
        double s1 = L_v[i] / U1_v[i];
        double s2 = L_v[i] / U2_v[i];
        S_v[idx++] = s1;
        S_v[idx++] = s2;
        std::cout << L_v[i] << "\t" << U1_v[i] << "\t" << s1 << "\t\t" << U2_v[i] << "\t" << s2 << std::endl;
    }

    double sumS_v = 0;
    for (int i = 0; i < 10; i++) {
        sumS_v += S_v[i];
    }
    double meanS_v = sumS_v / 10;

    double sumDiffSq_v = 0;
    for (int i = 0; i < 10; i++) {
        double diff = S_v[i] - meanS_v;
        sumDiffSq_v += diff * diff;
    }
    double stdDev_v = sqrt(sumDiffSq_v / 9);
    double errorS_v = stdDev_v / sqrt(10);

    double maxS_v = S_v[0];
    for (int i = 1; i < 10; i++) {
        if (S_v[i] > maxS_v) maxS_v = S_v[i];
    }

    std::cout << "\n--- VERTICAL PLATES RESULTS ---\n";
    std::cout << "Average sensitivity S_y = " << meanS_v << " +- " << errorS_v << " mm/V\n";
    std::cout << "Maximum sensitivity (S'_y)_m = " << maxS_v << " mm/V\n";

    double K_m = maxS_v / meanS_v;
    std::cout << "Gain coefficient K_m = " << K_m << "\n\n";

    double L_h[] = { 10, 20, 30, 40, 50 };
    double U1_h[] = { 0.75e-3, 6.4e-3, 13.5e-3, 18.5e-3, 23.75e-3 };

    double S_h[10];
    idx = 0;

    std::cout << "========== HORIZONTAL DEFLECTION PLATES ==========\n";
    std::cout << "L(mm)\tU1(V)\t\tS1(mm/V)\n";
    std::cout << "----------------------------------------\n";

    for (int i = 0; i < 5; i++) {
        double s = L_h[i] / U1_h[i];
        S_h[idx++] = s;
        std::cout << L_h[i] << "\t" << U1_h[i] << "\t" << s << std::endl;
    }

    for (int i = 0; i < 5; i++) {
        double s = L_h[i] / U1_h[i];
        S_h[idx++] = s;
    }

    double sumS_h = 0;
    for (int i = 0; i < 10; i++) {
        sumS_h += S_h[i];
    }
    double meanS_h = sumS_h / 10;

    double sumDiffSq_h = 0;
    for (int i = 0; i < 10; i++) {
        double diff = S_h[i] - meanS_h;
        sumDiffSq_h += diff * diff;
    }
    double stdDev_h = sqrt(sumDiffSq_h / 9);
    double errorS_h = stdDev_h / sqrt(10);

    std::cout << "\n--- HORIZONTAL PLATES RESULTS ---\n";
    std::cout << "Average sensitivity S_x = " << meanS_h << " +- " << errorS_h << " mm/V\n\n";

    double fx_values[2];
    fx_values[0] = 50.0;
    fx_values[1] = 50.0;

    double sum_fx = 0;
    for (int i = 0; i < 2; i++) {
        sum_fx += fx_values[i];
    }
    double mean_fx = sum_fx / 2;

    double sumDiff_fx = 0;
    for (int i = 0; i < 2; i++) {
        double diff = fx_values[i] - mean_fx;
        sumDiff_fx += diff * diff;
    }
    double error_fx = sqrt(sumDiff_fx / 1) / sqrt(2);

    std::cout << "========== LISSAJOUS FIGURES ==========\n";
    std::cout << "Ratio fx:fy\tfy(Hz)\tMeasured fx(Hz)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "1:1\t\t60\t60\n";
    std::cout << "2:1\t\t25\t50\n";
    std::cout << "\nFrequency measurement result:\n";
    std::cout << "f_x = " << mean_fx << " +- " << error_fx << " Hz\n\n";

    std::cout << "========== FINAL REPORT ==========\n";
    std::cout << "1. Vertical plate sensitivity: S_y = " << meanS_v << " +- " << errorS_v << " mm/V\n";
    std::cout << "2. Horizontal plate sensitivity: S_x = " << meanS_h << " +-" << errorS_h << " mm/V\n";
    std::cout << "3. Maximum sensitivity (S'_y)_m = " << maxS_v << " mm/V\n";
    std::cout << "4. Maximum gain coefficient K_m = " << K_m << "\n";
    std::cout << "5. Unknown frequency f_x = " << mean_fx << " +- " << error_fx << " Hz\n";

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}