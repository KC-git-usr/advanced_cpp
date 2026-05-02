//
// Created by Kumar Chakravarthy on 01-Jan-23.
//

#include <bits/stdc++.h>
#include <string>

using namespace std;

vector<vector<string>> groupAnagrams1(vector<string>& strs) {

    // segregate into boxes, each box having a unique key

    // take an element from the input vector
    // convert this string in a freq map
    // if this freq map is unique, create a new box
    // else add to an existing box

    vector<unordered_map<char, int>> keys;
    vector<vector<string>> result;

    for(int i = 0; i < strs.size(); ++i) {
        string str = strs[i];

        unordered_map<char, int> tmp_key;

        // create the freq map
        for(int j = 0; j < str.size(); ++j)
            tmp_key[str[j]]++;

        // check if this freq map is unique among the box keys
        bool new_key_flag = false;
        for(auto existing_key : keys) {
            if(existing_key.size() != tmp_key.size())
                continue;
            for(auto it = tmp_key.begin(); it != tmp_key.end(); ++it) {
                if(tmp_key[it->first] == existing_key[it->first])
                    continue;
                new_key_flag = true;
                break;
            }
        }

        if(new_key_flag) {
            keys.push_back(tmp_key);
            result[keys.size() - 1].push_back(str);
        } else {
            int index = -1;
            for(int k = 0; k < keys.size(); ++k) {
                unordered_map<char, int> current_key = keys[k];
                if(current_key.size() != tmp_key.size())
                    continue;
                for(auto it = tmp_key.begin(); it != tmp_key.end(); ++it) {
                    if(tmp_key[it->first] == current_key[it->first])
                        index = k;
                }
            }
            result[index].push_back(str);
        }
    }

    if(result.empty())
        return {{""}};
    return result;
}


string GetKey(string str) {
    vector<int> count(26, 0);
    for(int j = 0; j < str.size(); j++)
        count[str[j] - 'a']++;

    string key = "";
    for (int i = 0; i < 26; i++)
        key.append(to_string(count[i] + 'a'));

    return key;
}


vector<vector<string>> groupAnagrams2(vector<string>& strs) {
    unordered_map<string, vector<string>> hash_map;
    for (string str: strs) {
        string key = GetKey(str);
        hash_map[key].push_back(str);
    }

    vector<vector<string>> result;
    for (auto it = hash_map.begin(); it != hash_map.end(); ++it)
        result.push_back(it->second);

    return result;
}

int main() {
    vector<string> strs{"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> result = groupAnagrams2(strs);

    for(auto bucket : result)
        for(auto element : bucket)
            cout<< element << endl;
}