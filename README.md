# Numerical-Solvers-Edge

Ordinary differential equation (ODE) integrators evaluated on Hamiltonian systems under 32-bit floating-point precision.

## Theoretical Focus

Classical Runge-Kutta algorithms produce low truncation errors per cycle but fail to preserve the symplectic structure of Hamiltonian phase space. Over long integration windows, artificial dissipation occurs. Symplectic Euler preserves invariant manifolds, holding total energy error strictly bounded.

### Governing Equation: Undamped Linear Oscillator

$$\frac{dx}{dt} = v, \quad \frac{dv}{dt} = -\omega^2 x$$

$$\mathcal{H}(x, v) = \frac{1}{2}v^2 + \frac{1}{2}\omega^2 x^2$$

## Computational Performance

| Method | Order | Force Evaluations / Step | Phase Space Invariant | Memory Overhead |
| :--- | :--- | :--- | :--- | :--- |
| **Symplectic Euler** | 1 | 1 | Preserved | 8 Bytes |
| **Runge-Kutta 4 (RK4)** | 4 | 4 | Dissipative / Drifting | 8 Bytes |

## Build and Execution

```bash
cmake -B build
cmake --build build
./build/bench_solvers
python scripts/plot_drift.py
```

On Windows with the Visual Studio generator, use:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\bench_solvers.exe
python .\scripts\plot_drift.py
```

The benchmark writes `drift_data.csv`, and the plotting script saves
`drift_plot.png`.

Install the plotting dependency once with:

```powershell
python -m pip install matplotlib
```
