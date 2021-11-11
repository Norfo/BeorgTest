#pragma once

#include "SimilarityChecking/ISimilarityCkecker.h"

#include <opencv2/imgproc.hpp>

namespace similarity_checking
{
    class HistogrammSimilarityChecker : public ISimilarityChecker
    {
    public:
        HistogrammSimilarityChecker();
        ~HistogrammSimilarityChecker();

    public:
        HistogrammSimilarityChecker(const HistogrammSimilarityChecker&) = delete;
        HistogrammSimilarityChecker& operator=(const HistogrammSimilarityChecker&) = delete;
        HistogrammSimilarityChecker(HistogrammSimilarityChecker&&) = delete;
        HistogrammSimilarityChecker& operator=(HistogrammSimilarityChecker&&) = delete;

    public:
        int GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage) override;

    private:
        cv::Mat CalculateHistogramm(const cv::Mat image);
        int ConvertDistanceToSimilarity(double distance);
    };
}