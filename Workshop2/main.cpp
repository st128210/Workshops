#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(6);

    double h = 0.272;
    double delta_h = 0.001;
    double v0 = 1.050;
    double delta_v0 = 0.005;
    double delta_t_priv = 0.000001;
    double t_student = 2.042;
    int n = 30;

    double t_al[30] = { 152.481, 152.974, 152.394, 152.563, 152.358, 152.933, 152.470, 152.620, 152.963, 152.795,
                       152.265, 152.223, 152.625, 152.511, 152.138, 152.032, 152.707, 152.131, 152.724, 152.663,
                       152.702, 152.169, 152.342, 152.521, 152.416, 152.882, 152.658, 152.622, 152.168, 152.290 };

    double t_br[30] = { 152.287, 152.368, 153.279, 152.400, 152.512, 152.854, 152.553, 152.935, 152.336, 152.354,
                       152.358, 152.624, 152.863, 152.324, 152.397, 152.420, 153.031, 153.070, 152.440, 152.966,
                       152.845, 152.376, 152.033, 152.294, 152.327, 152.662, 152.273, 152.507, 152.477, 152.881 };

    double t_st[30] = { 152.276, 151.768, 151.951, 151.964, 151.939, 151.990, 151.935, 152.072, 152.247, 151.962,
                       151.967, 152.112, 152.081, 151.881, 152.390, 152.094, 152.084, 152.019, 152.268, 151.989,
                       153.017, 152.296, 151.957, 152.231, 152.107, 152.490, 152.954, 152.168, 152.984, 152.037 };

    double t_wd[30] = { 152.988, 152.949, 152.970, 152.820, 152.652, 152.942, 152.205, 152.835, 152.459, 152.354,
                       152.935, 152.975, 152.113, 152.954, 152.936, 152.111, 152.228, 152.931, 152.897, 152.416,
                       152.511, 152.301, 152.547, 152.687, 152.392, 152.378, 152.421, 152.255, 152.587, 152.330 };

    double t_pl[30] = { 152.916, 152.312, 152.912, 152.936, 152.136, 152.092, 152.348, 152.813, 152.971, 152.125,
                       152.932, 152.150, 152.083, 152.859, 152.806, 152.900, 152.258, 152.016, 152.371, 152.310,
                       152.168, 152.003, 152.789, 152.108, 152.822, 152.168, 152.478, 152.376, 152.974, 152.956 };

    double t_ld[30] = { 152.786, 152.377, 152.398, 152.656, 152.830, 152.455, 152.685, 152.595, 152.300, 152.841,
                       152.076, 152.640, 152.545, 152.179, 152.493, 152.247, 152.239, 152.100, 152.432, 152.776,
                       152.906, 152.493, 152.319, 152.002, 152.380, 152.235, 152.322, 152.568, 152.361, 152.346 };

    double dt_calc[6];
    double t_mean_ms_arr[6];
    double s_t_ms_arr[6];
    double delta_t_sluch_ms_arr[6];
    double g_calc[6];
    double delta_g[6];
    const char* materials[6] = { "Al", "Br", "St", "W", "Pl", "L" };
    double* t_arrays[6] = { t_al, t_br, t_st, t_wd, t_pl, t_ld };

    for (int mat = 0; mat < 6; mat++) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += t_arrays[mat][i];
        }
        double t_mean_ms = sum / n;
        t_mean_ms_arr[mat] = t_mean_ms;
        double t_sec = t_mean_ms / 1000.0;

        double sum_sq = 0;
        for (int i = 0; i < n; i++) {
            double diff = t_arrays[mat][i] - t_mean_ms;
            sum_sq += diff * diff;
        }
        double s_t_ms = sqrt(sum_sq / (n - 1));
        s_t_ms_arr[mat] = s_t_ms;
        double s_t_mean_ms = s_t_ms / sqrt(n);

        double delta_t_sluch_ms = t_student * s_t_mean_ms;
        delta_t_sluch_ms_arr[mat] = delta_t_sluch_ms;
        double delta_t_ms = sqrt(delta_t_sluch_ms * delta_t_sluch_ms + (delta_t_priv / 3) * (delta_t_priv / 3));
        double dt = delta_t_ms / 1000.0;
        dt_calc[mat] = dt;

        double numerator = h - v0 * t_sec;
        double g = 2 * numerator / (t_sec * t_sec);
        g_calc[mat] = g;

        double dg_dh = 2 / (t_sec * t_sec);
        double dg_dv0 = -2 / t_sec;
        double dg_dt = -4 * numerator / (t_sec * t_sec * t_sec) - 2 * v0 / (t_sec * t_sec);

        double delta_g_val = sqrt(dg_dh * dg_dh * delta_h * delta_h +
            dg_dv0 * dg_dv0 * delta_v0 * delta_v0 +
            dg_dt * dg_dt * dt * dt);
        delta_g[mat] = delta_g_val;
    }

    std::cout << "\n========== TIME MEASUREMENT UNCERTAINTY ==========\n\n";
    std::cout << "Material      t_mean (ms)    s_t (ms)      Delta t_sluch (ms)    Delta t (ms)\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    for (int mat = 0; mat < 6; mat++) {
        std::cout << std::left << std::setw(14) << materials[mat]
            << std::right << std::setw(12) << std::setprecision(3) << t_mean_ms_arr[mat]
            << std::setw(14) << std::setprecision(3) << s_t_ms_arr[mat]
            << std::setw(20) << std::setprecision(3) << delta_t_sluch_ms_arr[mat]
            << std::setw(14) << std::setprecision(3) << dt_calc[mat] * 1000 << std::endl;
    }

    std::cout << "\n========== TABLE 4. FREE FALL ACCELERATION g ==========\n\n";
    std::cout << "Material      g (m/s^2)       Delta g (m/s^2)       g +- Delta g\n";
    std::cout << "----------------------------------------------------------------\n";

    for (int mat = 0; mat < 6; mat++) {
        std::cout << std::left << std::setw(14) << materials[mat]
            << std::right << std::setw(10) << std::setprecision(4) << g_calc[mat]
            << std::setw(18) << std::setprecision(4) << delta_g[mat]
            << std::setw(18) << std::setprecision(4) << g_calc[mat] << " +- " << delta_g[mat] << std::endl;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}