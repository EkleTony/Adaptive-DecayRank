#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include "edge.hpp"

#define EPSILON 0.0001
#define c 0.35            // Damping factor
#define DECAY_FACTOR 0.55 // Base decay factor
#define ALPHA 1.0         // Hyperparameter for Bayesian updating
#define BETA 1.0          // Hyperparameter for Bayesian updating

// Function to compute PageRank values for a dynamic graph
double *pagerank(outEdge *A, double *b, int n, int m, int version, int numSteps)
{
    // Arrays to store intermediate PageRank values during iterations
    double *nq = new double[n]();
    double *nq_prev = new double[n]();

    // Adaptive decay factors for each node
    std::vector<double> adaptive_decay_factors(n, DECAY_FACTOR);
    std::vector<double> posterior_alpha(n, ALPHA);
    std::vector<double> posterior_beta(n, BETA);

    // Initialization of PageRank values based on the specified version
    for (int i = 0; i < n; i++)
    {
        b[i] = c / n; // Initial PageRank value
    }

    // Initialization of intermediate arrays
    for (int i = 0; i < n; i++)
    {
        nq[i] = 0;
        nq_prev[i] = b[i];
    }

    // Random number generator for Bayesian updating
    std::default_random_engine generator;
    std::gamma_distribution<double> gamma_distribution_alpha(ALPHA, 1.0);
    std::gamma_distribution<double> gamma_distribution_beta(BETA, 1.0);

    // Temporal PageRank iteration loop
    for (int step = 0; step < numSteps; ++step)
    {
        double *new_nq;
        double *old_nq;

        // Alternating between two arrays to avoid unnecessary copying
        if (step % 2 == 0)
        {
            new_nq = nq;
            old_nq = nq_prev;
        }
        else
        {
            new_nq = nq_prev;
            old_nq = nq;
        }

        // Resetting new_nq values
        std::fill(new_nq, new_nq + n, 0);

        // Updating PageRank values based on the graph structure and edge weights
        for (int i = 0; i < n; i++)
        {
            if (old_nq[i] == 0)
                continue;

            double delta;
            if (A[i].out.size() == 0)
                continue;

            delta = (1 - c) * old_nq[i] / A[i].out.size();

            // Updating new_nq values
            for (int j = 0; j < A[i].out.size(); j++)
            {
                new_nq[A[i].out[j]] += delta * A[i].weight[j];
            }
        }

        // Applying adaptive decay factor to new_nq using Bayesian inference
        for (int i = 0; i < n; i++)
        {
            double time_diff = step - A[i].timestamp;

            // Update decay factor using Bayesian inference
            double observed_change = std::abs(new_nq[i] - old_nq[i]);
            posterior_alpha[i] += observed_change;
            posterior_beta[i] += (1 - observed_change);

            double updated_decay_factor = gamma_distribution_alpha(generator) / gamma_distribution_beta(generator);
            adaptive_decay_factors[i] = std::min(updated_decay_factor, 1.0); // Ensure decay factor remains in a valid range

            new_nq[i] *= exp(-adaptive_decay_factors[i] * time_diff);
        }

        // Checking convergence using a more efficient statistical test
        double diff = std::inner_product(new_nq, new_nq + n, old_nq, 0.0, std::plus<double>(), [](double a, double b)
                                         { return std::abs(a - b); });

        // Apply a simple threshold-based convergence check for demonstration purposes
        if (diff < EPSILON)
        {
            break;
        }

        // Updating the PageRank scores
        for (int i = 0; i < n; i++)
        {
            b[i] += new_nq[i];
        }
    }

    // Normalizing the final PageRank scores
    double sum = std::accumulate(b, b + n, 0.0);
    for (int i = 0; i < n; i++)
    {
        b[i] /= sum;
    }

    // Memory cleanup
    delete[] nq;
    delete[] nq_prev;

    // Returning the final PageRank values
    return b;
}
