#pragma once
#include <variant>
#include <ranges>
#include "Filters.h"
#include "Transformations.h"

namespace pip
{
	template <typename PropertySheet, typename ...Ops>
	struct CascadedOperation
	{
		PropertySheet properties;
		std::vector<std::variant <Ops...>> operations;

		CascadedOperation(const std::vector<std::variant <Ops...>> &operations) : operations(operations) {};

		auto filter(const std::vector<double> &input)
		{
			std::vector<double> filteredInput;
			for (const auto& operation : operations)
			{
				std::visit([&](auto&& arg) 
				{
					for (const auto& i : input | std::views::filter(properties.polymorf(arg)))
					{
						filteredInput.push_back(i);
					}
				}, operation);
			};

			return filteredInput;
		}

		auto transform(const std::vector<double>& input)
		{
			std::vector<double> transformedInput = input;
			for (const auto& operation : operations)
			{
				auto result = std::visit([&](auto&& arg)
					{						
						for (const auto& i : input | std::views::transform(properties.polymorf(arg)))
						{
							transformedInput.push_back(i);
						}
						return transformedInput;
					}, operation);

				transformedInput = result;
			};

			return transformedInput;
		}
	};

};