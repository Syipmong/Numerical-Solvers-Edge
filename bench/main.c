#include <stdio.h>

#include "solvers.h"

#define TOTAL_STEPS 10000
#define TIME_STEP 0.05f

int main(void)
{
    oscillator_params_t params = {.omega_sq = 1.0f };

    state_t rk4_state = { .x = 1.0f, .v = 0.0f };
    state_t se_state = { .x = 1.0f, .v = 0.0f };

    float initial_energy = compute_hamiltonian(&rk4_state, &params);

    FILE *fp = fopen("drift_data.csv", "w");
    if (!fp)
    {
        printf("Failed to open output file. \n");
        return 1;
    }
    fprintf(fp, "Step, Time, RK4_EnergyDRift, SE_EnergyDrift\n");

    for (int step = 0; step <= TOTAL_STEPS; ++step)
    {
        float current_time = (float) step * TIME_STEP;
        float rk4_energy = compute_hamiltonian(&rk4_state, &params);
        float se_energy = compute_hamiltonian(&se_state, &params);
        
        float rk4_drift = rk4_energy - initial_energy;
        float se_drift = se_energy - initial_energy;

        if (step % 50 == 0)
        {
            fprintf(fp, "%d, %.2f, %.6e, %.6e\n", step, current_time, rk4_drift, se_drift);
        }

        rk4_state = step_rk4(rk4_state, TIME_STEP, &params);
        se_state = state_symplectic_euler(se_state, TIME_STEP, &params);
    }

    fclose(fp);
    printf("Simulation completed over %d steps. Data logged to drift_data.csv\n", TOTAL_STEPS);

    return 0;
}