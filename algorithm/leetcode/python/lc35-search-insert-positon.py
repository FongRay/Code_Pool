class Solution(object):
    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        i = 0
        while i < len(nums):
            if target <= nums[i]:
                return i
            else:
                i += 1
        else:
            return i
