#include <stdio.h>

#include "solvers.h"

#define TOTAL_STEPS 10000
#define TIME_STEPS 0.05f

int main(void)
{
    oscillator_params_t params = {.omega_sq = 1.0f };

    state_t rk4_state = { .x = 1.0f, .v = 0.0f };
    state_t se = { .x = 1.0f, .v = 0.0f };

    float initial_energy = compute_hamiltonian(&rk4_state, &params);

    FILE *fp = fopen("drift_data.csv", "w");
    if (!fp)
    {
        printf("Failed to open output file. \n");
        return 1;
    }
    fprintf(fp, "Step, Time, RK4_EnergyDRift, SE_EnergyDrift\n");
    
}