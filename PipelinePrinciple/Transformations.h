#pragma once
#include <functional>
#include <iostream>

namespace pip
{
	namespace transformations
	{
		template <typename INPUT = double>
		struct ARCorrection
		{
			std::function<INPUT(INPUT, std::string&)> apply = [](const INPUT &input, std::string& correctionFactor)
			{
				std::cout << "\t - ARCorrection transformation applied with factor = " << correctionFactor << std::endl;
				return input * 2;
			};
		};
	};

	namespace properties
	{
		template <typename INPUT = double>
		struct TransformationProperties
		{
			/// <summary>
			/// ARCorrection transformation properties & functionality
			/// </summary>
			std::string correctionFactor = "hello?";

			auto polymorf(const pip::transformations::ARCorrection<INPUT>& arg)
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
