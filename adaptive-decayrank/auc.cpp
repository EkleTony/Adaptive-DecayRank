#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

double compute_auc(const std::vector<double> &scores, const std::vector<bool> &labels, const std::string &output_file)
{
    size_t n = scores.size();
    std::vector<std::pair<double, bool>> score_label_pairs(n);

    for (size_t i = 0; i < n; ++i)
    {
        score_label_pairs[i] = std::make_pair(scores[i], labels[i]);
    }

    // Sort by score in descending order
    std::sort(score_label_pairs.begin(), score_label_pairs.end(), std::greater<std::pair<double, bool>>());

    double tp = 0;
    double fp = 0;
    double tp_prev = 0;
    double fp_prev = 0;
    double auc = 0;
    double prev_score = -1;

    double positive_count = std::count(labels.begin(), labels.end(), true);
    double negative_count = labels.size() - positive_count;

    std::vector<double> tpr;
    std::vector<double> fpr;

    for (size_t i = 0; i < n; ++i)
    {
        if (score_label_pairs[i].first != prev_score)
        {
            auc += (fp - fp_prev) * (tp + tp_prev) / 2.0;
            prev_score = score_label_pairs[i].first;
            tp_prev = tp;
            fp_prev = fp;

            tpr.push_back(tp / positive_count); // TPR
            fpr.push_back(fp / negative_count); // FPR
        }
        if (score_label_pairs[i].second)
        {
            tp += 1;
        }
        else
        {
            fp += 1;
        }
    }

    // Include the last point
    tpr.push_back(1.0);
    fpr.push_back(1.0);

    auc += (fp - fp_prev) * (tp + tp_prev) / 2.0;
    auc /= (positive_count * negative_count);

    // Write TPR and FPR to file
    std::ofstream file(output_file);
    if (file.is_open())
    {
        for (size_t i = 0; i < tpr.size(); ++i)
        {
            file << fpr[i] << " " << tpr[i] << "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing TPR and FPR.\n";
    }

    return auc;
}
