#pragma once

#include "SimilarityChecking/FeatureMatchingSimilarityChecker.h"

namespace similarity_checking
{
    FeatureMatchingSimilarityChecker::FeatureMatchingSimilarityChecker()
    {
    }

    FeatureMatchingSimilarityChecker::~FeatureMatchingSimilarityChecker()
    {
    }

    int FeatureMatchingSimilarityChecker::GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage)
    {
        auto orbDetector = cv::ORB::create(KEYPOINTS_COUNT);
        std::vector<cv::KeyPoint> referenceKeyPoints;
        std::vector<cv::KeyPoint> examineKeyPoints;
        cv::Mat referenceDescriptors;
        cv::Mat examineDescriptors;

        orbDetector->detectAndCompute(referenceImage, cv::Mat(), referenceKeyPoints, referenceDescriptors);
        orbDetector->detectAndCompute(examineImage, cv::Mat(), examineKeyPoints, examineDescriptors);

        auto matcher = cv::BFMatcher::create(cv::NORM_L2);

        std::vector<cv::DMatch> matches;
        matcher->match(examineDescriptors, referenceDescriptors, matches);

        int similarity = 0;

        for (auto match : matches)
        {
            if (match.distance < MAXIMUM_DISTANCE_SIMILARITY_THRESHOLD)
            {
                ++similarity;
            }
        }

        return static_cast<int>((similarity / static_cast<double>(KEYPOINTS_COUNT)) * 100);
    }
}