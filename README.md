# Runge-Kutta 4th Order Method for a System of ODEs

## Problem Overview

This program numerically solves a system of first-order ordinary differential equations (ODEs) using the classical fourth-order Runge-Kutta method (RK4).

The code prints the values of the independent variable $x$ and the dependent variables $y_1, y_2$ at each step.

## Mathematical Formulation

The general system is written as:

$$
\frac{dy_1}{dx} = f_1(x, y_1, y_2)
$$

$$
\frac{dy_2}{dx} = f_2(x, y_1, y_2)
$$

In this program, the implemented system is:

$$
\frac{dy_1}{dx} = -0.5\,y_1
$$

$$
\frac{dy_2}{dx} = 4 - 0.3\,y_2 - 0.51
$$

with initial conditions:

$$
x_0 = 0, \quad y_1(0) = 4, \quad y_2(0) = 6
$$

The step size used is:

$$
h = 0.5
$$

and the solution is computed up to:

$$
x = 2
$$

## RK4 Approach

For each step, RK4 computes four slope estimates for every equation.

For a vector system, let the derivative vector be:

$$
\mathbf{y}' = \mathbf{f}(x, \mathbf{y})
$$

The RK4 intermediate values are:

$$
\mathbf{k}_1 = \mathbf{f}(x_n, \mathbf{y}_n)
$$

$$
\mathbf{k}_2 = \mathbf{f}\left(x_n + \frac{h}{2}, \mathbf{y}_n + \frac{h}{2}\mathbf{k}_1\right)
$$

$$
\mathbf{k}_3 = \mathbf{f}\left(x_n + \frac{h}{2}, \mathbf{y}_n + \frac{h}{2}\mathbf{k}_2\right)
$$

$$
\mathbf{k}_4 = \mathbf{f}(x_n + h, \mathbf{y}_n + h\mathbf{k}_3)
$$

Then the next solution point is updated using:

$$
\mathbf{y}_{n+1} = \mathbf{y}_n + \frac{h}{6}(\mathbf{k}_1 + 2\mathbf{k}_2 + 2\mathbf{k}_3 + \mathbf{k}_4)
$$

For each dependent variable, this means:

$$
y_{1,n+1} = y_{1,n} + \frac{h}{6}(k_{1,1} + 2k_{2,1} + 2k_{3,1} + k_{4,1})
$$

$$
y_{2,n+1} = y_{2,n} + \frac{h}{6}(k_{1,2} + 2k_{2,2} + 2k_{3,2} + k_{4,2})
$$

## Written Procedure

1. Start from the initial point $x_0$ with known values of $y_1$ and $y_2$.
2. Compute $\mathbf{k}_1$ using the derivative values at the current point.
3. Use $\mathbf{k}_1$ to estimate the midpoint and compute $\mathbf{k}_2$.
4. Use $\mathbf{k}_2$ to compute $\mathbf{k}_3$ at the midpoint again.
5. Use $\mathbf{k}_3$ to compute $\mathbf{k}_4$ at the next full step.
6. Combine all four slopes to get the next values of the solution.
7. Repeat the process until the final $x$ value is reached.

## Program Output

The program displays a table containing:

- $x$ values
- $y_1$ values
- $y_2$ values

Each row represents the approximated solution at one RK4 step.

## Notes

- The solver is written for a general system of ODEs, so the number of equations can be changed easily.
- The output is formatted using fixed precision for readability.