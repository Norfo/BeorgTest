#pragma once

#include "SimilarityChecking/ISimilarityCkecker.h"

#include <opencv2/imgproc.hpp>

namespace similarity_checking
{
    class TemplateSimilarityChecker : public ISimilarityChecker
    {
    public:
        TemplateSimilarityChecker();
        ~TemplateSimilarityChecker();

    public:
        TemplateSimilarityChecker(const TemplateSimilarityChecker&) = delete;
        TemplateSimilarityChecker& operator=(const TemplateSimilarityChecker&) = delete;
        TemplateSimilarityChecker(TemplateSimilarityChecker&&) = delete;
        TemplateSimilarityChecker& operator=(TemplateSimilarityChecker&&) = delete;

    public:
        int GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage) override;

    private:
        const double MAXIMUM_PATCH_SIMILARITY_THRESHOLD = .7;
    };
}