#include <cmath>
#include <vector>
#include "edge.hpp"

#define EPSILON 0.0002
#define c 0.95            // best =0.22, .32
#define DECAY_FACTOR 0.95 // best = 0.5, .65

// Node structure with timestamp
/*
struct outEdge
{
    int timestamp;           // Add timestamp for each node
    std::vector<int> out;    // List of outgoing nodes
    std::vector<int> weight; // Corresponding weights
}; */

// Function to compute PageRank values for a dynamic graph
double *pagerank(outEdge *A, double *b, int n, int m, int version, int numSteps)
{
    // Arrays to store intermediate PageRank values during iterations
    double *nq = new double[n];
    double *nq_prev = new double[n];

    // Initialization of PageRank values based on the specified version
    if (version == 1)
    {
        for (int i = 0; i < n; i++)
            b[i] = c / n;
    }
    else
    {
        for (int i = 0; i < n; i++)
            b[i] = c / n; // You need to adjust this based on your requirements
    }

    // Initialization of intermediate arrays
    for (int i = 0; i < n; i++)
    {
        nq[i] = 0;
        nq_prev[i] = b[i];
    }

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
        for (int i = 0; i < n; i++)
            new_nq[i] = 0;

        // Updating PageRank values based on the graph structure and edge weights
        for (int i = 0; i < n; i++)
        {
            if (old_nq[i] == 0)
                continue;

            // PageRank update based on the specified version
            double delta;
            if (version == 1)
            {
                if (A[i].out.size() == 0)
                    continue;

                delta = (1 - c) * old_nq[i] / A[i].out.size();

                // Updating new_nq values
                for (int j : A[i].out)
                {
                    new_nq[j] += delta * A[i].weight[j];
                }
            }
            else
            {
                // Adjust this part based on your representation
                // You need to incorporate the weights into your calculation
                // For example, if A[i].weight[j] is the weight of edge (i, j),
                // you would use it in the calculation.
            }
        }

        // Applying decay factor to new_nq
        for (int i = 0; i < n; i++)
        {
            new_nq[i] *= exp(-DECAY_FACTOR * (step - A[i].timestamp));
        }

        // Updating the PageRank scores
        for (int i = 0; i < n; i++)
        {
            b[i] += new_nq[i];
        }
    }

    // Normalizing the final PageRank scores
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += b[i];

    for (int i = 0; i < n; i++)
        b[i] /= sum;

    // Memory cleanup
    delete[] nq;
    delete[] nq_prev;

    // Returning the final PageRank values
    return b;
}