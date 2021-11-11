#include "SimilarityChecking/HistogrammSimilarityCkecker.h"

namespace similarity_checking
{
    HistogrammSimilarityChecker::HistogrammSimilarityChecker()
    {
    }

    HistogrammSimilarityChecker::~HistogrammSimilarityChecker()
    {
    }

    int HistogrammSimilarityChecker::GetSimilarity(const cv::Mat& referenceImage, const cv::Mat& examineImage)
    {
        cv::Mat referenceImageHsv;
        cv::cvtColor(referenceImage, referenceImageHsv, cv::COLOR_BGR2HSV);
        auto referenceHistogramm = CalculateHistogramm(referenceImageHsv);

        cv::Mat examineImageHsv;
        cv::cvtColor(examineImage, examineImageHsv, cv::COLOR_BGR2HSV);
        auto examineHistogramm = CalculateHistogramm(examineImageHsv);

        auto distance = cv::compareHist(referenceHistogramm, examineHistogramm, cv::HISTCMP_BHATTACHARYYA);

        return ConvertDistanceToSimilarity(distance);
    }

    cv::Mat HistogrammSimilarityChecker::CalculateHistogramm(const cv::Mat image)
    {
        int hueBins = 30;
        int saturationBins = 30;
        int histogrammSize[] = { hueBins, saturationBins };

        float hueRanges[] = { 0, 180 };
        float saturationRanges[] = { 0, 256 };
        const float* ranges[] = { hueRanges, saturationRanges };

        cv::Mat histogramm;
        int channels[] = { 0, 1 }; 
        calcHist(&image, 1, channels, cv::Mat(), histogramm, 2, histogrammSize, ranges, true, false);

        return histogramm;
    }

    int HistogrammSimilarityChecker::ConvertDistanceToSimilarity(double distance)
    {        
        return static_cast<int>((1 - distance) * 100.0);
    }
}