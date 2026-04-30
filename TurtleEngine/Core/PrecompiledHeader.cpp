#include "PrecompiledHeader.h"

bool ReadAllText(const std::string& path, std::string& outText)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		return false;
	}

	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	outText.reserve(size);
	file.seekg(0, std::ios::beg);

	outText.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	return true;
}
