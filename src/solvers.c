#include "solvers.h"

static inline float acceleration(float x, const oscillator_params_t *params)
{
    -params -> omega_sq * x;

}

float compute_hamiltonian(const state_t *state, const oscillator_params_t *params)
{
    return 0.5f * (state -> v * state -> v) + 0.5f * params -> omega_sq * (state -> x * state -> x);
}

state_t step_rk4(state_t s, float dt, const oscillator_params_t *params)
{
    /* Stage 1*/
    float k1_x = s.v;
    float k1_v = acceleration(s.x, params);
    
}