
# Adaptive-DecayRank: Real-Time Anomaly Detection in Dynamic Graphs

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview
**Adaptive-DecayRank** is a novel anomaly detection framework for **real-time anomaly detection in dynamic graphs**. It leverages **Bayesian PageRank updates** with an **adaptive decay factor** to efficiently detect **node anomalies and sudden structural changes**.

## Features
✔ Real-time anomaly detection on **dynamic graph streams**.  
✔ **Modified dynamic PageRank algorithm** for improved detection accuracy.  
✔ Efficient **Adaptive Bayesian Updating** for scalability.  
✔ Outperforms **AnomRank, SedanSpot, DynAnom**, etc.

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
