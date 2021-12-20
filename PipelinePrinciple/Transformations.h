#pragma once
#include <functional>
#include <iostream>

namespace pip
{
	namespace transformations
	{
		struct ARCorrection
		{
			std::function<double(double, std::string&)> apply = [](double input, std::string& correctionFactor)
			{
				std::cout << "\t - ARCorrection transformation applied with factor = " << correctionFactor << std::endl;
				return input * 2;
			};
		};
	};

	namespace properties
	{
		struct TransformationProperties
		{
			/// <summary>
			/// ARCorrection transformation properties & functionality
			/// </summary>
			std::string correctionFactor = "hello?";

			auto polymorf(const pip::transformations::ARCorrection& arg)
			{
				auto myFilter = [&](const auto& i)
				{
					return arg.apply(i, correctionFactor);
				};
				return myFilter;
			}
		};
	};
};
