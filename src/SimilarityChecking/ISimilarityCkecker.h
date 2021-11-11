#pragma once

#include <opencv2/core.hpp>

namespace similarity_checking
{
    class ISimilarityChecker
    {
    public:
        virtual ~ISimilarityChecker() = default;

    public:
        ISimilarityChecker() = default;
        ISimilarityChecker(const ISimilarityChecker&) = delete;
        ISimilarityChecker& operator=(const ISimilarityChecker&) = delete;
        ISimilarityChecker(ISimilarityChecker&&) = delete;
        ISimilarityChecker& operator=(ISimilarityChecker&&) = delete;

    public:
        virtual int GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage) = 0;
    };
}