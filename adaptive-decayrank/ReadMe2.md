# Adaptive-DecayRank: Real-Time Anomaly Detection in Dynamic Graphs

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Project Overview

**Adaptive-DecayRank** is a novel anomaly detection framework for **real-time anomaly detection in dynamic graphs**. It leverages **Bayesian PageRank updates** with an **adaptive decay factor** to efficiently detect **node anomalies and sudden structural changes**.

This repository contains:

- **C++ implementation** of Adaptive-DecayRank.
- **Benchmark datasets** (DARPA, CTU-13, RTM-30).
- **Precision-Recall results** and **scalability analysis**.

## Features

✔ **Real-time anomaly detection** on dynamic graph streams.  
✔ **Adaptive Bayesian updating** for better accuracy.  
✔ **Graph sketching** for scalability.  
✔ **Outperforms DecayRank, SendanSpot, DynAnom, etc.**

### **Build and Run**

Compile the source code using g++:

```bash
g++ -std=c++11 -stdlib=libc++ -O3 main.cpp -o decayrank
```

Run Adaptive-DecayRank on datasets:

```bash
./decayrank "darpa.txt" " " 45 120 0 20 30
```

## Usage

Execute **Adaptive-DecayRank** with the following parameters:

```bash
./decayrank "dataset.txt" "delimiter" time_step snapshot_start anomaly_mode num_anomalies anomaly_size
```

| Parameter     | Description                                      |
| ------------- | ------------------------------------------------ |
| `dataset.txt` | Input dataset file (DARPA, CTU-13, RTM).         |
| `" "`         | Space delimiter used in the dataset.             |
| `60`          | Time step size for dividing data into snapshots. |
| `128`         | Starting snapshot for anomaly detection.         |
| `0`           | Anomaly injection mode (0 = no injection).       |
| `20`          | Number of anomalies injected (if applicable).    |
| `30`          | Magnitude of injected anomalies (if applicable). |

## Algorithm Overview

### **📌 `pagerank.cpp` - Adaptive-DecayRank Algorithm**

1. **Graph Construction** - Reads snapshots and builds adjacency lists.
2. **Bayesian PageRank Update** - Updates ranks with prior belief distributions.
3. **Anomaly Scoring** - Computes anomaly scores and saves in `DecayRank.txt`.
4. **AUC Computation** - Computes TPR & FPR and saves to `tpr_fpr_forAUC.txt`.

## Output Files

| File Name                      | Description                                      |
| ------------------------------ | ------------------------------------------------ |
| `DecayRank.txt`                | Stores computed anomaly scores.                  |
| `tpr_fpr_forAUC.txt`           | Stores **TPR & FPR** values for AUC computation. |
| `precision_recall_results.txt` | Precision-Recall curve results.                  |

## Datasets

- **DARPA** - Intrusion detection dataset.
- **CTU-13** - Real-world botnet traffic dataset.
- **RTM-30** - Synthetic graph dataset.

🚀 **Adaptive-DecayRank** is designed for scalable, real-time anomaly detection in dynamic graphs. For inquiries, contact the corresponding author.
