#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

class Solution {
    public:
        Solution(): max_pos_(0),
                    max_len_(0) {
        }

        void clear() {
            max_pos_ = 0;
            max_len_ = 0;
        }

        // O(n^2)
        string longestPalindrome_1(string s) {
            int s_sz = s.size();
            // substr's length is odd
            for (int i = 1; i < s_sz - 1; ++i) {
                int j = 1;
                while (j <= i && i + j < s_sz && s[i-j] == s[i+j]) ++j; 
                if (2 * j - 1 > max_len_) {
                    max_pos_ = i - j + 1;
                    max_len_ = 2 * j - 1;
                }
            }
            // substr's length is even
            for (int i = 0; i < s_sz - 1 ; ++i) {
                if (s[i] != s[i+1]) {
                    continue;
                }
                int j = 1;
                while (j <= i && i + 1 + j < s_sz && s[i-j] == s[i+1+j]) ++j;
                if (2 * j > max_len_) {
                    max_pos_ = i - j + 1;
                    max_len_ = 2 * j;
                }
            }
            return s.substr(max_pos_, max_len_);
        }

        // O(nlogn)
        void get_longest_pali(string s, int off_pos) {
            int s_sz = s.size();
            if (s_sz < 2 || s_sz <= max_len_) 
                return;
            int mid = s_sz >> 1;
            int extend_left[s_sz + 1];
            int extend_right[s_sz + 1]; 
            string r_s(s);
            std::reverse(r_s.begin(), r_s.end());
            // s[mid..sz] ->
            string s_right = s.substr(mid);
            extend_kmp(r_s, s_right, extend_left);
            extend_left[s_sz] = 0;
            // s[0..mid) <-
            string s_left = s.substr(0, mid);
            std::reverse(s_left.begin(), s_left.end());
            extend_kmp(s, s_left, extend_right);
            extend_right[s_sz] = 0;

            for (int i = 0; i < mid; ++i) {
                if (extend_right[i] >= (mid - i) / 2) {
                    int len = extend_left[s_sz-i] * 2 + mid - i; 
                    if (len > max_len_) {
                        max_pos_ = off_pos + i - extend_left[s_sz-i];
                        max_len_ = len;
                    }
                }
            }
            for (int i = mid; i < s_sz; ++i) {
                if (extend_left[s_sz-i] >= (i - mid) / 2) {
                    int len = extend_right[i] * 2 + i - mid;
                    if (len > max_len_) {
                        max_pos_ = off_pos + mid - extend_right[i];
                        max_len_ = len;
                    }
                }
            }

            get_longest_pali(s.substr(0, mid), 0);
            get_longest_pali(s.substr(mid), mid);
        }

        string longestPalindrome_2(string s) {
            get_longest_pali(s, 0);
            return s.substr(max_pos_, max_len_);
        }

        // O(n)
        string longestPalindrome(string s) {
            
        }

    private:

        // extend[i] -> S[i..n]与T的最长公共前缀 
        void extend_kmp(const string& S, const string& T, int* extend) {
            int t_sz = T.size();
            // next[i] -> T[i..m]与T的最长公共前缀
            int next[t_sz + 1];  
            next[0] = t_sz; 
            int i = 0;
            while (T[i] == T[i+1] && i + 1 < t_sz) ++i;
            next[1] = i;
            // p0 -> [1..k-1]中匹配到最远位置(next[p0] + p0 - 1)的起点
            int p0 = 1;
            for (int k = 2; k < t_sz; ++k) {
                if (next[k-p0] < next[p0] + p0 - k) {
                    next[k] = next[k-p0]; 
                } else {
                    int j = next[p0] + p0 - k;
                    j = j < 0 ? 0 : j;
                    while (j + k < t_sz && T[j+k] == T[j]) ++j;
                    next[k] = j;
                    // next[p0] + p0 <= next[k] + k, 更新p0
                    p0 = k;
                }
            }

            i = 0;
            int s_sz = S.size();
            while (S[i] == T[i] && i < s_sz && i < t_sz) ++i;
            extend[0] = i;
            p0 = 0;
            for (int k = 1; k < s_sz; ++k) {
                if (next[k-p0] < extend[p0] + p0 - k) {
                    extend[k] = next[k-p0];
                } else {
                    int j = extend[p0] + p0 - k;
                    j = j < 0 ? 0 : j;
                    while (j + k < s_sz && j < t_sz && S[j+k] == T[j]) ++j;
                    extend[k] = j;
                    p0 = k;
                }
            }
        }

    public:
        int max_pos_;

        int max_len_;
};

int main() {
    Solution sol;
    /*
    // hdu 3294
    char a_ch;
    string old_str;
    string new_str;
    while (cin >> a_ch >> old_str) {
        new_str = old_str;
        for (int i = 0; i < new_str.size(); ++i) {
            new_str[i] = 'a' + (26 + new_str[i] - a_ch) % 26;
        }
        sol.longestPalindrome_2(new_str);
        if (sol.max_len_ <= 1) {
            cout << "No solution!\n";
        } else { 
            cout << sol.max_pos_ << " " << sol.max_pos_ + sol.max_len_ - 1 << endl;
            cout << new_str.substr(sol.max_pos_, sol.max_len_) << endl;
        }
        sol.clear();
    }
    */
    return 0;
}

