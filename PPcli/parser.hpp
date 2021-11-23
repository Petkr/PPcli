#pragma once
#include "PP/ref_wrap.hpp"
#include "PP/vector.hpp"
#include "PP/view/concept.hpp"
#include "PP/view/copy.hpp"
#include "PP/containers/tuple.hpp"

#include <algorithm>

namespace PPcli
{
class parser
{
	struct option
	{
		bool* present;
		PP::vector<PP::ref_wrap<std::string&>> variables;

		option(bool& present, PP::concepts::view auto&& variables)
		    : present(&present)
		    , variables(PP_F(variables))
		{}
	};

	PP::vector<PP::tuple::container<std::string_view, option>> option_map;

	auto find(std::string_view name)
	{
		auto i = std::lower_bound(option_map.begin(),
		                          option_map.end(),
		                          name,
		                          [](auto& pair, std::string_view name)
		                          {
			                          return pair[PP::value_0] < name;
		                          });
		if ((*i)[PP::value_0] == name)
			return i;
		else
			return option_map.end();
	}

public:
	parser(auto&... options)
	{
		(option_map.push_back(
		     PP::in_place,
		     [&options]{ return options.name(); },
		     [&options]{ return option(options.presence(), options.variables()); }),
		 ...);

		std::sort(option_map.begin(),
		          option_map.end(),
		          [](auto& a, auto& b)
		          {
			          return a[PP::value_0] < b[PP::value_0];
		          });
	}
	void parse(int argc, char** argv, auto argument_oi, auto unrecognised_oi)
	{
		for (auto& [name, o] : option_map)
			*o.present = false;

		auto end = argv + argc;

		for (char** i = argv + 1; i != end;)
		{
			char* cla = *i;

			if (cla[0] == '-')
			{
				auto option = cla + 1;

				auto var_i = find(option);

				if (var_i != option_map.end())
				{
					auto& o = (*var_i)[PP::value_1];

					*o.present = true;

					i = PP::view::copy(
					    o.variables | PP::transform(PP::static__cast *
					                                PP::type<std::string&>),
					    PP::view::pair(i + 1, end))[PP::value_1];
				}
				else
				{
					*unrecognised_oi++ = option;
					++i;
				}
			}
			else
			{
				*argument_oi++ = cla;
				++i;
			}
		}
	}
};
}
