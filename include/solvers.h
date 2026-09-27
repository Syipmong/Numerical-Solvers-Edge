#ifndef SOLVERS_H
#define SOLVERS_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
    float x; /* Position Cordinates*/
    float v; /* Velocity / Generalized Momentum*/
} state_t;

typedef struct {
    float omega_sq; /* Natural Frequency Squared: k/m*/
} oscillator_params_t;

/**
 * @brief Computes total Hamiltonian Energy: H(x, v) = 0.5 * v^2 + 0.5 * omega^2 * x^2.
 */
 float compute_hamiltonian(const state_t *state, const oscillator_params_t *params);

 /**
  * @brief Advances state by dt using classical 4th-order Runge-Kutta.
  * Requires 4 derivative evaluations per step. Non-symplectic.
  */
  state_t step_rk4(state_t current, float dt, const oscillator_params_t *params);

  /**
   * @brief Advances step by dt using semi-implicit (symplectic) Euler.
   * Requires 1 derivative evaluation per step . Preserves Symplectic 2-form.
   */
  state_t state_symplectic_euler(state_t current, float dt, const oscillator_params_t *params);

  #ifdef __cplusplus

}

#endif

#endif /* SOLVERS_H*/