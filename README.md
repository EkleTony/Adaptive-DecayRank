# Adaptive-DecayRank: Real-Time Anomaly Detection in Dynamic Graphs

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview

**Adaptive-DecayRank** is a novel anomaly detection framework for **real-time anomaly detection in dynamic graphs**. It leverages **Bayesian PageRank updates** with an **adaptive decay factor** to efficiently detect **node anomalies and sudden structural changes**.

📄 Published in *Applied Sciences (MDPI)*:  
https://www.mdpi.com/2076-3417/15/6/3360

---

## Adaptive-DecayRank Framework

![Adaptive-DecayRank Framework](adaptive_decayrank_framework.svg)

*Figure 1: Adaptive-DecayRank framework. The pipeline consists of (1) Graph Input and Snapshot Generation, (2) Dynamic Node Scoring, (3) Adaptive Bayesian Updating of decay factors, and (4) Normalization and Real-Time Anomaly Detection.*

The **Adaptive-DecayRank** framework begins by transforming dynamic graph input into timestamp-based snapshots, which form the foundation for node score computation. The algorithm then iteratively updates node scores while dynamically adjusting the decay factor through Bayesian inference. This adaptive mechanism ensures sensitivity to structural changes in evolving graphs, enabling rapid detection of anomalous behavior.

Finally, normalized anomaly detection metrics are applied to identify nodes exhibiting significant deviations over time. The framework integrates real-time updates, adaptive decay mechanisms, and robust anomaly scoring tailored for dynamic graph environments.

---

## Features

✔ Real-time anomaly detection on **dynamic graph streams**  
✔ Modified **Dynamic PageRank algorithm** for improved detection accuracy  
✔ Efficient **Adaptive Bayesian Updating** for scalability  
✔ Demonstrated improvements over **AnomRank, SedanSpot, DynAnom**, and related baselines

## Dataset
We provide the following benchmark datasets for dynamic graph anomaly detection:
- DARPA – Cyber attack dataset **[Link](https://www.ll.mit.edu/r-d/datasets/1998-darpa-intrusion-detection-evaluation-dataset)**
- CTU-13 – Botnet traffic dataset - **[CTU-13 dataset](https://www.stratosphereips.org/datasets-ctu13)**  

- RTM-30 – Synthetic anomaly dataset
### Dataset Preparation
1. Download & Unzip the datasets.
2. Move all extracted dataset files to the Adaptive-DecayRank folder.
3. Ensure the dataset files are in the same directory before compilation.

## Compile the C++ code
-- run bash file ".\run.sh"

## Summary of Code Structure
1. pagerank.cpp
  Implements Adaptive-DecayRank algorithm with Bayesian updating.
 Computes anomaly scores for each node in the evolving graph.
2. read_data.cpp
  Reads, processes, and prepares temporal graph data.
  Handles snapshot generation based on step size.
3. Algorithm Process
  The anomaly scores are stored in DecayRank.txt
  True Positive Rate (TPR) and False Positive Rate (FPR) are stored in tpr_fpr_forAUC.txt
  The AUC values are used to plot the Precision-Recall and AUC curve.


## Installation
Clone the repository:
```bash
git clone https://github.com/YOUR_GITHUB_USERNAME/Adaptive-DecayRank.git
cd Adaptive-DecayRank
