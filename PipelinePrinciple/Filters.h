#pragma once
#include <functional>
#include <iostream>

namespace pip
{

	namespace filters
	{
		template <typename INPUT = double>
		struct Blur
		{

			/// <summary>
			/// If we make this type specific, i.e. INPUT = cv::Mat, the compiler will automatically grab the right function;
			/// Remove the template argument below if things come together!  
			/// </summary>
			std::function<bool(const INPUT&, double)> apply = [](const INPUT &input, double blurringFactor = 0)
			{
				std::cout << "\t - Blur filter applied with factor = " << blurringFactor << std::endl;
				return true;
			};
		};

		template <typename INPUT = double>
		struct Area
		{
			std::function<bool(const INPUT&, int)> apply = [](const INPUT &input, int areaFactor = 0)
			{
				std::cout << "\t - Area filter applied with factor = " << areaFactor << std::endl;
				return true;
			};
		};

		template <typename INPUT = double>
		struct Breach
		{
			std::function<bool(const INPUT&)> apply = [](const INPUT &input)
			{
				std::cout << "\t - Breach filter applied with no parameters " << std::endl;
				return true;
			};
		};
	};

	namespace properties
	{
		
		template <typename INPUT = double>
		struct FilterProperties
		{
			/// <summary>
			/// Area filter properties & functionality
			/// </summary>
			int areaFactor = 0;
			
			auto polymorf(const pip::filters::Area<INPUT>& arg)
			{
				return [&](const auto& i)
				{
					return arg.apply(i, areaFactor);
				};
			};

			double blurringFactor = 0.0;
			/// <summary>
			/// Bluring filter properties & functionality
			/// </summary>

			auto polymorf(const pip::filters::Blur<INPUT>& arg)
			{
				return [&](const auto& i)
				{
					return arg.apply(i, blurringFactor);
				};
			};

			/// <summary>
			/// Breach filter properties & functionality
			/// </summary>
			auto polymorf(const pip::filters::Breach<INPUT>& arg)
			{
				return [&](const auto& i)
				{
					return arg.apply(i);
				};
			};
		};
	};
};

