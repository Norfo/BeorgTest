#pragma once

#include "SimilarityChecking/TemplateSimilarityChecker.h"

namespace similarity_checking
{
    TemplateSimilarityChecker::TemplateSimilarityChecker()
    {
    }

    TemplateSimilarityChecker::~TemplateSimilarityChecker()
    {
    }

    int TemplateSimilarityChecker::GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage)
    {
        const int gridSize = 10;

        auto rowStep = referenceImage.rows / gridSize;
        auto colStep = referenceImage.cols / gridSize;

        int matchingCells = 0;

        for (size_t i = 0; i < gridSize; i++)
        {
            for (size_t j = 0; j < gridSize; j++)
            {
                auto startRow = i * rowStep;
                auto startCol = j * colStep;
                auto actualRow = startRow + rowStep;
                auto actualCol = startCol + colStep;
                auto rectWidth = actualCol > referenceImage.cols ? referenceImage.cols - actualCol : colStep;
                auto rectHeight = actualRow > referenceImage.rows ? referenceImage.rows - actualRow : rowStep;
                cv::Rect rect = cv::Rect(startCol, startRow, rectWidth, rectHeight);

                auto patch = referenceImage(rect);
                cv::Mat matchingResult;

                cv::matchTemplate(examineImage, patch, matchingResult, cv::TM_CCOEFF_NORMED);

                double minVal;
                double maxVal;
                cv::minMaxLoc(matchingResult, &minVal, &maxVal);

                if (maxVal > MAXIMUM_PATCH_SIMILARITY_THRESHOLD)
                {
                    ++matchingCells;
                }
            }
        }

        return matchingCells;
    }
}