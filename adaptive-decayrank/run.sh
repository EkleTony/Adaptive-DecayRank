g++ -std=c++11 -stdlib=libc++ -O3 main.cpp -o decayrank;
./decayrank "darpa.txt" " " 45 120  0 20 30

# CTU
# ./decayrank "ctu_modified_55.txt" " " 60 30 0 20 30

# RTM running
# ./decayrank "RTM_generated_graph.txt" " " 10 7 0 30 30

# RTM Synthetic graph works but overfits on low snapshots: 10 8 0 20 30
# --1. Increase graph snapshots to fit scale with the algorithm

# 1. Best DARPA: 
#./decayrank "darpa.txt" " " 60 50  0 20 30 

# Recent Best AUC=90
#./decayrank "darpa.txt" " " 40 128  0 20 30

# 2. Best CTU Data:
#./decayrank "ctu_modified_55.txt" " " 60 50 0 20 30

# Summary of parameters:
# These parameters are used to configure the data processing, 
# anomaly injection, and detection settings for the program.

# ==========
# ./decayrank "eucore_new.txt" " " 60 256 0 50 70
# ==========

# eucore_new.txt: Input dataset file.
# " ": Space delimiter used in the dataset.
# 60: Time step size for dividing the data into snapshots.
# 112: Starting snapshot for anomaly detection.
# 0: Anomaly injection scenario (0 means no injection).
# 50: Number of anomalies to inject (if applicable).
# 70: Size or magnitude of the injected anomalies (if applicable).
