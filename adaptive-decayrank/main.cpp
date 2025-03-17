#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>
#include <ctime>
#include <cstring>
#include <set>

#include "accuracy.cpp"
#include "anomaly_detect.cpp"
#include "anomaly_inject.cpp"
#include "pagerank.cpp"
#include "read_data.cpp"
#include "auc.cpp"

#define attackLimit 60

using namespace std;

int main(int argc, char *argv[])
{
    clock_t start_total = clock(); // Start the total timer

    clock_t start = clock();

    string path = argv[1];
    string delimiter = argv[2];
    int timeStep = atoi(argv[3]);
    int initSS = atoi(argv[4]);
    int injectScene = atoi(argv[5]);
    int injectNum = atoi(argv[6]);
    int injectSize = atoi(argv[7]);
    bool INJECT = (injectScene != 0);

    // READ DATA
    vector<timeEdge> edges;
    vector<int> snapshots;
    set<int> anomalous_nodes_desc;
    int n, m, timeNum;
    read_data(path, delimiter, timeStep, edges, snapshots, n, m, timeNum, anomalous_nodes_desc);
    int total_snapshots = timeNum / timeStep + 1;
    int effective_snapshots = snapshots.size() - (initSS / timeStep);
    int anomalous_nodes = anomalous_nodes_desc.size();
    outEdge *A = new outEdge[n];

    // Output graph information
    cout << "============GRAPH Info==============" << endl;
    cout << "#node: " << n
         << ", #edges: " << edges.size()
         << ", #timeStamp: " << timeNum
         << ", #snapshots: " << total_snapshots
         << ", #init snapshots: " << initSS
         << ", #effective_snapshots: " << effective_snapshots
         << ", #Anomalous-nodes: " << anomalous_nodes << endl;
    cout << "===================================" << endl;

    cout << "========= HELLO! Welcome to the Summer Series! =======" << endl;

    // ANOMALY_SCORE
    int testNum = 900;
    if (strcmp(argv[1], "darpa.txt") == 0)
    {
        testNum = total_snapshots - initSS;
    }
    bool *attack = new bool[testNum];
    double *anomScore = new double[testNum];
    for (int i = 0; i < testNum; i++)
    {
        anomScore[i] = 0;
        attack[i] = false;
    }

    // PAGERANK
    double **pagerank1 = new double *[3];
    double **pagerank2 = new double *[3];
    for (int i = 0; i < 3; i++)
    {
        pagerank1[i] = new double[n];
        pagerank2[i] = new double[n];
        for (int j = 0; j < n; j++)
            pagerank1[i][j] = pagerank2[i][j] = 0;
    }

    // MEAN AND VARIANCE
    double **mean = new double *[4];
    double **var = new double *[4];
    for (int i = 0; i < 4; i++)
    {
        mean[i] = new double[n];
        var[i] = new double[n];
        for (int j = 0; j < n; j++)
            mean[i][j] = var[i][j] = 0;
    }

    // INJECTED SNAPSHOT
    vector<int> injectSS;
    if (INJECT)
        inject_snapshot(injectNum, initSS, testNum, snapshots, injectSS);

    cout << "Preprocess done: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

    int eg = 0;
    int snapshot = 0;
    int attackNum = 0;
    int injected = 0;
    int current_m = 0;
    double previous_score = 100.0;

    start = clock();
    int print_e = 10;
    for (int ss = 0; ss < snapshots.size(); ss++)
    {
        while (edges[eg].t < snapshots[ss] * timeStep)
        {
            inject(A, edges[eg].src, edges[eg].trg, 1);
            current_m++;
            if (edges[eg].atk)
                attackNum++;
            eg++;
            if (eg == print_e)
            {
                cout << eg << "," << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
                print_e *= 10;
            }
            if (eg == edges.size())
                break;
        }

        if (INJECT && injectSS[injected] == snapshots[ss])
        {
            current_m += inject_anomaly(injectScene, A, n, injectSize);
            attackNum += attackLimit;
            injected++;
            if (injected == injectSS.size())
                INJECT = false;
        }

        snapshot = snapshots[ss];
        int numSteps = 10;
        pagerank(A, pagerank1[snapshot % 3], n, current_m, 1, numSteps);
        pagerank(A, pagerank2[snapshot % 3], n, current_m, 2, numSteps);

        double decay_factor = 0.25; // 15 (best )Adjust the decay factor as needed
        double score = compute_anomaly_score(snapshot, pagerank1, pagerank2, mean, var, n, decay_factor);

        if (snapshot >= initSS)
        {
            anomScore[snapshot - initSS] = score;
            attack[snapshot - initSS] = attackNum >= attackLimit;
            previous_score = score;
        }
        attackNum = 0;
    }

    string filePath = "DecayRank.txt";

    ofstream writeFile;
    writeFile.open(filePath.c_str(), ofstream::out);
    for (int i = 0; i < testNum; i++)
        writeFile << anomScore[i] << " " << int(attack[i]) << endl;
    writeFile.close();

    for (int i = 1; i < 17; i++)
        compute_accuracy(anomScore, attack, testNum, 50 * i);

    // Compute and output accuracy and AUC
    vector<double> anomScoreVec(anomScore, anomScore + testNum);
    vector<bool> attackVec(attack, attack + testNum);
    double auc = compute_auc(anomScoreVec, attackVec, "tpr_fpr_forAUC.txt");
    cout << "AUC: " << auc << std::endl;

    delete[] A;
    delete[] anomScore;

    for (int i = 0; i < 3; i++)
    {
        delete[] pagerank1[i];
        delete[] pagerank2[i];
    }
    delete[] pagerank1;
    delete[] pagerank2;

    for (int i = 0; i < 4; i++)
    {
        delete[] mean[i];
        delete[] var[i];
    }
    delete[] mean;
    delete[] var;

    cout << "Total time without I/O: " << (double)(clock() - start_total) / CLOCKS_PER_SEC << " seconds" << endl;

    return 1;
}
