#include <iostream>
#include <vector>
#include <functional> // to define ODESystem as a function type
#include <iomanip> // for table formatting

using namespace std;

// Define a clear type for the system of ODEs
using ODESystem = function<void(double, const vector<double>&, vector<double>&)>;

class RK4Solver {
private:
    int n;
    // Pre-allocate memory to prevent expensive re-allocations inside the hot loop
    vector<double> k1, k2, k3, k4, y_temp, dydx;

public:
    RK4Solver(int num_equations) : n(num_equations) {
        k1.resize(n); k2.resize(n); k3.resize(n); k4.resize(n);
        y_temp.resize(n); dydx.resize(n);
    }

    void solve(const ODESystem& system, double x0, vector<double> y, double h, double x_end) {
        // Set fixed precision for clean presentation output
        cout << fixed << setprecision(5);
        
        // Dynamic Table Header
        cout << string(40, '-') << "\n";
        cout << setw(10) << "x";
        for (int i = 0; i < n; i++) {
            cout << setw(12) << "y" << i + 1;
        }
        cout << "\n" << string(40, '-') << "\n";

        double x = x0;
        // Epsilon prevents floating-point rounding errors from skipping the final step
        double epsilon = h * 1e-5;

        while (x <= x_end + epsilon) {
            // Print current state
            cout << setw(10) << x;
            for (double val : y) {
                cout << setw(12) << val;
            }
            cout << "\n";

            // Break if we've reached the target boundary
            if (x >= x_end - epsilon) break;

            // RK4 Step 1: k1
            system(x, y, k1);
            for (int i = 0; i < n; i++) y_temp[i] = y[i] + 0.5 * h * k1[i];

            // RK4 Step 2: k2
            system(x + 0.5 * h, y_temp, k2);
            for (int i = 0; i < n; i++) y_temp[i] = y[i] + 0.5 * h * k2[i];

            // RK4 Step 3: k3
            system(x + 0.5 * h, y_temp, k3);
            for (int i = 0; i < n; i++) y_temp[i] = y[i] + h * k3[i];

            // RK4 Step 4: k4
            system(x + h, y_temp, k4);

            // Update y variables
            for (int i = 0; i < n; i++) {
                y[i] += (h / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
            }
            x += h;
        }
        cout << string(40, '-') << "\n";
    }
};

int main() {
    // ==============================================================================
    // GIVEN EQUATIONS
    // ==============================================================================
    ODESystem mySystem = [](double x, const vector<double>& y, vector<double>& dydx) {
        // y[0] represents y1
        // y[1] represents y2
        
        // Equation 1: dy1/dx = -0.5 * y1
        dydx[0] = -0.5 * y[0];
        
        // Equation 2: dy2/dx = 4 - 0.3 * y2 - 0.1 * y1
        dydx[1] = 4.0 - 0.3 * y[1] - 0.51; 
    };

    // Initial Conditions & Parameters
    int num_equations = 2;          // Total number of dependent variables
    double x0 = 0.0;                // Starting x
    vector<double> y0 = {4.0, 6.0}; // Initial values at x0: [y1, y2]
    double h = 0.5;                 // Step size
    double x_end = 2.0;             // Target x to integrate to
    // ==============================================================================

    // Execute Solver
    RK4Solver solver(num_equations);
    solver.solve(mySystem, x0, y0, h, x_end);

    return 0;
}