#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

namespace
{
	const char* const kOutPath = "FileManager.bin";

	enum Index : int
	{
		kTime,
		kLeftLane,
		kRightLane
	};

	constexpr float kVar = 1.0f;
	struct Header
	{
		float var = kVar;
		int size = 0;
	};
}
struct PopData
{
	bool right;
	bool left;
};
class DataManager
{
private:
	std::vector<PopData> m_popLane;
	std::vector<std::wstring> Split(const std::wstring& str, const char del);
public:
	void LoadCsv();
	std::vector<PopData> GetData() { return m_popLane; }

};