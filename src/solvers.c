#include "solvers.h"

static inline float acceleration(float x, const oscillator_params_t *params)
{
    return -params->omega_sq * x;
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

    /* Stage 2*/
    float x_k2 = s.x + 0.5f * dt * k1_x;
    float k2_x = s.v + 0.5f *dt * k1_v;
    float k2_v = acceleration(x_k2, params);

    /* Stage 3*/
    float x_k3 = s.x + 0.5f * dt * k2_x;
    float k3_x = s.v + 0.5f * dt * k2_v;
    float k3_v = acceleration(x_k3, params);

    /* Stage 4*/
    float x_k4 = s.x + dt * k3_x;
    float k4_x = s.v + dt * k3_v;
    float k4_v = acceleration(x_k4, params);

    state_t next;
    next.x = s.x + (dt / 6.0f) * (k1_x + 2.0f * k2_x + 2.0f * k3_x + k4_x);
    next.v = s.v + (dt / 6.0f) * (k1_v + 2.0f * k2_v + 2.0f * k3_v + k4_v);
    return next;
}

state_t step_symplectic_euler(state_t s, float dt, const oscillator_params_t *params)
{
    state_t next;

    /* Update Momentum via current position*/
    next.v = s.v + dt * acceleration(s.x, params);

    /*Update position using the updated momentum*/
    next.x = s.x + dt * next.v;
    return next;
}