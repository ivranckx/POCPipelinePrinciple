#pragma once

#include "Filters.h"
#include "Transformations.h"
#include "Pipeline.h"

namespace pip
{
    template < //   All template parameters are of the cascaded operations type
        typename PreprocessingOps,  
        typename FilterOps,        
        typename ValidSealPostProcessingOps,   
        typename InValidSealPostProcessingOps> 
    struct SuperSealProcessor
    {
        PreprocessingOps preOps;
        FilterOps filterOps;
        ValidSealPostProcessingOps validPostOps;
        InValidSealPostProcessingOps invalidPostOps;

        SuperSealProcessor(const PreprocessingOps& ppOps, const FilterOps& fOps, const ValidSealPostProcessingOps& vsOps, const InValidSealPostProcessingOps& isOps) :
            preOps(ppOps),
            filterOps(fOps),
            validPostOps(vsOps),
            invalidPostOps(isOps)
        {
        };

        auto process(const cv::Mat1b& sealImage)
        {
            cv::Mat labels, stats, centroids;
            cv::connectedComponentsWithStats(sealImage, labels, stats, centroids);
            
            const auto sealCandidates = ranges::views::iota(1, stats.rows) | ranges::view::transform([&](const auto& colIndex)
                    {
                        const auto i = [&](const auto& rowIndex)
                        {
                            return stats.at<int>(cv::Point(rowIndex, colIndex));
                        };
                        const auto specs = ranges::views::iota(0, 4) | ranges::view::transform(i);
                        const auto roi = cv::Rect(specs[0], specs[1], specs[2], specs[3]);
                        return std::make_pair(sealImage(roi), roi);
                    };
            );

            const auto invalidSeals = sealCandidates
                | ranges::view::filter(std::not1(filterOps.filter))
                | ranges::to_vector;

            const auto validSeals = sealCandidates
                | ranges::views::transform(preOps.process)
                | ranges::view::filter(filterOps.filter)
                | ranges::views::transform(postOps.process)
                | ranges::to_vector;

            return std::make_pair(validSeals, invalidSeals);
        };
    };

};