#include "pch.h"
#include "../PipelinePrinciple/Pipeline.h"

typedef pip::CascadedOperation<
	pip::properties::FilterProperties<>,
	pip::filters::Blur<>,
	pip::filters::Breach<>,
	pip::filters::Area<>> ANYFILTEROPS;

typedef pip::CascadedOperation<
	pip::properties::TransformationProperties<>,
	pip::transformations::ARCorrection<>> ANYTRANSOPS;

TEST(TestCascadedOperations, TestIfOneFilterCanBeApplied)
{
	ANYFILTEROPS oneFilter(
		{
			pip::filters::Breach()
		});

	//	Update area factor or read it from generic webService (SOAP?) / GUI
	oneFilter.properties.areaFactor = 10;
	//......

	//	Apply filtering operations...
	oneFilter.filter<>(std::vector<double>{ 0, 1, 2, 3});
	EXPECT_EQ(1, 1);
}

TEST(TestCascadedOperations, TestIfOneOperationCanBeApplied)
{
	ANYTRANSOPS oneTransformation(
		{
			pip::transformations::ARCorrection()
		});

	oneTransformation.properties.correctionFactor = "updated parameter";
	oneTransformation.transform<>(std::vector<double>{ 0, 1, 2, 3});
	EXPECT_EQ(1, 1);
}


TEST(TestCascadedOperations, TestIfTwoFiltersCanBeApplied)
{
	ANYFILTEROPS twoFilters(
		{
			pip::filters::Area(),
			pip::filters::Breach()
		});

	twoFilters.properties.blurringFactor = 1.5;
	twoFilters.filter(std::vector<double>{ 0, 1, 2, 3});
	EXPECT_EQ(1, 1);
}

TEST(TestCascadedOperations, TestIfMultipleFiltersCanBeApplied)
{
	ANYFILTEROPS multipleFilters(
		{
			pip::filters::Area(),
			pip::filters::Breach(),
			pip::filters::Blur(),
			pip::filters::Breach(),
			pip::filters::Blur()
		}
	);

	multipleFilters.properties.areaFactor = 3;
	multipleFilters.properties.blurringFactor = 2;
	multipleFilters.filter(std::vector<double>{ 0, 1, 2, 3});
	EXPECT_EQ(1, 1);
}

