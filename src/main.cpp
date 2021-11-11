#include "SimilarityChecking/ISimilarityCkecker.h"
#include "SimilarityChecking/FeatureMatchingSimilarityChecker.h"
#include "SimilarityChecking/TemplateSimilarityChecker.h"
#include "SimilarityChecking/HistogrammSimilarityCkecker.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc.hpp>
#include <map>

int GetThreshold()
{
    std::cout << "Please, input similarity threshold (0-100): ";
    int threshold = 0;
    std::cin >> threshold;
    if (threshold < 0 || threshold > 100)
    {
        std::cout << "Threshold must be in interval from 0 to 100!" << std::endl;
        return GetThreshold();
    }

    return threshold;
}

std::vector<std::string> GetImagePaths()
{
    std::cout << "Please, input path to image and press 'Enter' to confirm. Input '*' to skip: " << std::endl;

    std::vector<std::string> paths;

    while (true)
    {
        std::string path = "";
        char ch;
        while (true) 
        {
            if ((ch = std::cin.get()) == '*')
            {
                return paths;
            }

            if (ch == '\n')
            {
                if (path != "")
                {
                    paths.push_back(path);
                }                
                break;
            }
            path += ch;
        }
    }
}

std::map<std::string, cv::Mat> ReadImages(std::vector<std::string> imagePaths)
{
    std::cout << "Reading images" << std::endl;

    std::map<std::string, cv::Mat> images;
    for (auto path : imagePaths)
    {
        try
        {
            auto image = cv::imread(path);

            if (!image.empty())
            {
                images.insert(std::make_pair(path, image));
            }            
        }
        catch (const std::exception& e)
        {
            std::cerr << "Can not read image at " << path << " as " << e.what() << std::endl;
        }
    }
    return images;
}

std::unique_ptr<similarity_checking::ISimilarityChecker> SelectAlgorithm()
{
    std::cout << "Please, select similarity checker:" << std::endl;
    std::cout << "0 - Histogramm based" << std::endl;
    std::cout << "1 - Template based" << std::endl;
    std::cout << "2 - Feature matching based" << std::endl;

    int input;
    std::cin >> input;

    switch (input)
    {
    case 0:
        return std::make_unique<similarity_checking::HistogrammSimilarityChecker>();
    case 1:
        return std::make_unique<similarity_checking::TemplateSimilarityChecker>();
    case 2:
        return std::make_unique<similarity_checking::FeatureMatchingSimilarityChecker>();
    default:
        break;
    }
}

int main(int, char**)
{
    int similarutyThreshold = GetThreshold();

    std::vector<std::string> imagePaths = GetImagePaths();

    std::map<std::string, cv::Mat> images = ReadImages(imagePaths);

    auto checker = SelectAlgorithm();

    for (auto image : images)
    {
        auto similarity = checker->GetSimilarity(images.begin()->second, image.second);

        if (similarity >= similarutyThreshold)
        {
            std::cout << images.begin()->first << ", " << image.first << ", " << similarity << "%" << std::endl;
        }
    }

    return 0;
}