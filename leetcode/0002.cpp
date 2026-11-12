#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> mp;
       for (auto& str : strs) {
           std::string key = str;
           sort(key.begin(), key.end());
           mp[key].push_back(str);
       }
       std::vector<std::vector<std::string>> ans;
       ans.reserve(mp.size());
       for (auto& [_, values] : mp) {
           ans.push_back(values);
       }
       return ans;
    }
};
void printans (const std::vector<std::vector<std::string>>& strs) {
    std::cout << '[';
    for (size_t i = 0; i < strs.size(); ++i) {
        if (i) std::cout << ',';
        std::cout << '[';
        for (size_t j = 0; j < strs[i].size(); ++j) {
            if (j) std::cout << ',';
            std::cout << '"' << strs[i][j] << '"';
        }
        std::cout << ']';
    }
    std::cout << "]\n";
}

std::vector<std::string> parseWords(const std::string& input) {
    std::vector<std::string> words;
    size_t i = 0;
    while (i < input.size()) {
        if (input[i] == '"') {
            size_t j = input.find('"', i + 1);
            if (j == std::string::npos) break;
            words.push_back(input.substr(i + 1, j - i - 1));
            i = j + 1;
        } else {
            ++i;
        }
    }
    return words;
}

int main() {
    std::string input, line;
    while (std::getline(std::cin, line)) {
        input += line;
    }

    std::vector<std::string> strs = parseWords(input);

    Solution sol;
    auto result = sol.groupAnagrams(strs);

    // 排序让输出稳定，方便对照题目示例
    for (auto& group : result) {
        std::sort(group.begin(), group.end());
    }
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });

    printans(result);
    return 0;
}
