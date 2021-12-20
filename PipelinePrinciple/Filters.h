#pragma once
#include <functional>
#include <iostream>

namespace pip
{

	namespace filters
	{
		struct Blur
		{
			std::function<bool(double, double)> apply = [](double input, double blurringFactor = 0)
			{
				std::cout << "\t - Blur filter applied with factor = " << blurringFactor << std::endl;
				return true;
			};
		};

		struct Area
		{
			std::function<bool(double, int)> apply = [](double input, int areaFactor = 0)
			{
				std::cout << "\t - Area filter applied with factor = " << areaFactor << std::endl;
				return true;
			};
		};

		struct Breach
		{
			std::function<bool(double)> apply = [](double input)
			{
				std::cout << "\t - Breach filter applied with no parameters " << std::endl;
				return true;
			};
		};
	};

	namespace properties
	{
		struct FilterProperties
		{
			/// <summary>
			/// Area filter properties & functionality
			/// </summary>
			int areaFactor = 0;

			auto polymorf(const pip::filters::Area& arg)
			{
				auto myFilter = [&](const auto& i)
				{
					return arg.apply(i, areaFactor);
				};
				return myFilter;
			}

			/// <summary>
			/// Bluring filter properties & functionality
			/// </summary>
			double blurringFactor = 0.0;

			auto polymorf(const pip::filters::Blur& arg)
			{
				auto myFilter = [&](const auto& i)
				{
					return arg.apply(i, blurringFactor);
				};
				return myFilter;
			}

			/// <summary>
			/// Breach filter properties & functionality
			/// </summary>
			auto polymorf(const pip::filters::Breach& arg)
			{
				auto myFilter = [&](const auto& i)
				{
					return arg.apply(i);
				};
				return myFilter;
			}
		};
	};
};

