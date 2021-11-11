#pragma once

#include "SimilarityChecking/ISimilarityCkecker.h"

#include <opencv2/ximgproc.hpp>

namespace similarity_checking
{
    class FeatureMatchingSimilarityChecker : public ISimilarityChecker
    {
    public:
        FeatureMatchingSimilarityChecker();
        ~FeatureMatchingSimilarityChecker();

    public:
        FeatureMatchingSimilarityChecker(const FeatureMatchingSimilarityChecker&) = delete;
        FeatureMatchingSimilarityChecker& operator=(const FeatureMatchingSimilarityChecker&) = delete;
        FeatureMatchingSimilarityChecker(FeatureMatchingSimilarityChecker&&) = delete;
        FeatureMatchingSimilarityChecker& operator=(FeatureMatchingSimilarityChecker&&) = delete;

    public:
        int GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage) override;

    private:
        const int KEYPOINTS_COUNT = 1000;
        const double MAXIMUM_DISTANCE_SIMILARITY_THRESHOLD = 300.0;
    };
}