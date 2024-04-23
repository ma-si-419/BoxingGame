#include "DataManager.h"

void DataManager::LoadCsv()
{
    m_popLane.resize(99);

    std::string path = "data.csv";

    // ファイル読み込み
    std::wifstream ifs(path.c_str());
    if (!ifs)
    {
        assert(false);
        return;
    }

    std::wstring strBuf;
    std::vector<std::wstring> strConmaBuf;

    // 余分な部分の読み込み
    std::getline(ifs, strBuf);

    // データすべて読み込み
    while (std::getline(ifs, strBuf))
    {
        strConmaBuf = Split(strBuf, ',');

        // 左レーン取得
        int time = std::stoi(strConmaBuf[kTime]);

        std::wstring& leftLaneInfo = strConmaBuf[kLeftLane];
        auto& data = m_popLane[time];
        if (leftLaneInfo == L"0") {
            data.left = false;
        }
        else if (leftLaneInfo == L"1") {
            data.left = true;
        }

        // 右レーン取得
        std::wstring& rightLaneInfo = strConmaBuf[kRightLane];
        if (rightLaneInfo == L"0") {
            data.right = false;
        }
        else if (rightLaneInfo == L"1") {
            data.right = true;
        }
    }
}


std::vector<std::wstring> DataManager::Split(const std::wstring& str, const char del)
{
    // 区切り開始位置
    int first = 0;
    // 区切り最終位置
    int last = static_cast<int>(str.find_first_of(del));

    std::vector<std::wstring> result;

    while (first < str.size())
    {
        // 区切ったものを結果に入れていく
        std::wstring subStr(str, first, last - first);

        result.push_back(subStr);

        // 位置更新
        first = last + 1;
        last = static_cast<int>(str.find_first_of(del, first));
        if (last == std::wstring::npos)
        {
            last = static_cast<int>(str.size());
        }
    }

    return result;
}