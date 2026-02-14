#ifndef US_UTIL
#define US_UTIL

#include "xasm.inc"

inline std::string nomz_mnemo(const std::string &line)
{
	std::string res;
	bool in_space = false;

	for(char c : line)
	{
		if(std::isspace(c))
		{
			if(!in_space && !res.empty())
			{
				res += ' ';
				in_space = true;
			}
		}
		else if(c == ',')
		{
			if(!res.empty() && res.back() == ' ') res.pop_back();
			res += ',';
			in_space = false;
		}
		else
		{
			res += std::toupper(c);
			in_space = false;
		}
	}

	for(size_t i = 0; i < res.size(); i++)
	{
		if(res[i] == ',' && i + 1 < res.size() && res[i + 1] != ' ') res.insert(i + 1, " ");
	}

	return res;
}

#endif /* util.inc */
