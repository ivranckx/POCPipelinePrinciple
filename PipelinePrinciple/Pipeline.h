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

		CascadedOperation(const std::vector<std::variant<Ops...>> &operations) : operations(operations) {};

		template <typename INPUT = double>
		auto filter(const std::vector<INPUT> &input)
		{
			std::vector<INPUT> filteredInput;
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

		template <typename INPUT = double>
		auto transform(const std::vector<INPUT>& input)
		{
			std::vector<INPUT> transformedInput = input;
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