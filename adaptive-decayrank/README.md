# Adaptive-DecayRank: Real-Time Anomaly Detection in Dynamic Graphs

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview
**Adaptive-DecayRank** is a high-performance **real-time anomaly detection** framework designed for **dynamic graphs**. It extends **DecayRank** by incorporating **Bayesian updating** and an **adaptive decay factor**, making it **scalable, adaptive, and robust** for detecting node and edge anomalies in evolving graph streams.

This repository provides:
- **C++ implementation** of Adaptive-DecayRank.
- **Graph datasets**: DARPA, CTU-13, RTM-30.
- **Precision-Recall results and AUC analysis**.
- **Executable and parameterized command-line usage**.

---

## 📌 Key Features
✔ **Bayesian PageRank Updates** with an adaptive decay factor.  
✔ **Real-time anomaly detection** on **streaming graphs**.  
✔ **Low computational overhead**, scalable to **millions of edges**.  
✔ **Benchmark evaluation** on multiple datasets.  

---

## 🛠 Algorithm Overview

The core **Adaptive-DecayRank** algorithm is implemented in **`pagerank.cpp`**, which:
1. **Constructs dynamic graph snapshots** from the input dataset.
2. **Applies Bayesian PageRank updates** with an **adaptive decay factor**.
3. **Computes anomaly scores** for each node in the graph.
4. **Outputs detected anomalies** to `DecayRank.txt`.
5. **Computes True Positive Rate (TPR) & False Positive Rate (FPR)** stored in `tpr_fpr_forAUC.txt` for **AUC computation**.

---


