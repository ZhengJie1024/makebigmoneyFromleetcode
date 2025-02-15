#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;

class Solution {
    public:
        vector<vector<int> > permute(vector<int>& nums) {
            vector<vector<int> > result;
            int n = nums.size();
            vector<int> path(n, -1);
            backTrack(result, path, 0, 0, nums, n);
            return result;
        }
        void backTrack(vector<vector<int> >& result, vector<int>& path, int row, int hit_tag, vector<int>& nums, int n) {
            if (row == n) {
                result.push_back(vector<int>(path));
            } else {
                int available_pos = ((1 << n) - 1) & (~hit_tag);
                while (available_pos != 0) {
                    int pos = available_pos & (-available_pos);
                    available_pos = available_pos & (available_pos - 1);
                    int index = get_first_one_index(pos);
                    path[row] = nums[index - 1];
                    backTrack(result, path, row + 1, hit_tag | pos, nums, n);
                    path[row] = -1;
                }
            }
        }

        int get_first_one_index(int pos) {
            int i = 1;
            while ((pos & 1) == 0) {
                i++;
                pos >>= 1;
            }
            return i;
        }
};

int main()
{
    Solution A = Solution();
    vector<int> v = {1, 2, 3};
    std::vector<std::vector<int> > resutl = A.permute(v);
}
