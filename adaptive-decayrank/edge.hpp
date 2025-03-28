#ifndef EDGE
#define EDGE
#include <vector>

// Edge stream is expressed using timeEdge
struct timeEdge
{
    timeEdge(std::vector<int> &tokens)
    {
        t = tokens[0];
        src = tokens[1];
        trg = tokens[2];

        if (tokens.size() == 3)
            atk = false;
        else
            atk = tokens[3] == 1;
    }

    int src;
    int trg;
    int t;
    bool atk;
};

// Sparse matrix is expressed using outEdge
struct outEdge
{
    outEdge()
    {
        total_w = 0;
        timestamp = 0;
    }

    double total_w;
    int timestamp;
    std::vector<int> out;
    std::vector<double> weight; // Changed to double to handle fractional weights
};

#endif
