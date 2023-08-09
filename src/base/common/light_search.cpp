/*
 *  Created on: Jul 19, 2019
 *      Author: Alexander Ksenofontov
 */

#include <iostream>
#include <stack>
#include <string>

using stack = std::stack<std::pair<size_t, size_t>>;

bool match_text(const std::string& text, const std::string& match)
{
    stack tasks;
    tasks.push(std::make_pair(0, 0));
    while (!tasks.empty()) {
        auto task = tasks.top();
        tasks.pop();

        size_t index_t = task.first;
        size_t index_m = task.second;
        while (index_t < text.size() && index_m < match.size()) {
            if (match[index_m] == '?') {
                index_t++;
                index_m++;
            } else if (match[index_m] == '*') {
                tasks.push(std::make_pair(index_t + 1, index_m));
                index_m++;
            } else if (match[index_m] == text[index_t]) {
                index_t++;
                index_m++;
            } else
                break;
        }
        if (index_t == text.size()) {
            if (index_m == match.size())
                return true;

            if (index_m == match.size() - 1 && match[index_m] == '*')
                return true;
        }
    }
    return false;
}
