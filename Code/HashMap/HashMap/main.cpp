//
//  main.cpp
//  HashMap
//
//  Created by Lawrence on 2020/12/8.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//MARK: - ------------------- 中等难度 -----------------
/*
 380. 常数时间插入、删除和获取随机元素
 https://leetcode-cn.com/problems/insert-delete-getrandom-o1/
 解题思路：题目要求复杂度为On(1)，所以使用了hashmap+数组
 */
class RandomizedSet {
private:
    int m_size = 0;
    vector<int> nums;
    unordered_map<int, int> indexs;
public:
    RandomizedSet() {

    }
    
    bool insert(int val) {
        if (indexs.count(val)) {
            return false;
        } else {
            indexs[val] = m_size;
            nums.push_back(val);
            m_size++;
            return true;
        }
    }
    
    bool remove(int val) {
        if (indexs.count(val)) {
            //获取元素对应数组的索引
            int index = indexs[val];
            //将数组元素最后一个的索引改成要删除元素的索引
            indexs[nums.back()] = index;
            //当前要删除的元素与数组最后一个元素的位置交换
            swap(nums[index], nums.back());
            //删除当前要删除的元素
            nums.pop_back();
            //删除索引缓存
            indexs.erase(val);
            m_size--;
            return true;
        } else {
            return false;
        }
    }
    
    int getRandom() {
        return nums[rand() % m_size];
    }
};

//MARK: - ---------------------- 困难题 --------------------

/*
 710. 黑名单中的随机数
 解题思路: hash大法
 https://leetcode-cn.com/problems/random-pick-with-blacklist/
 */
class Blacklist {
private:
    int sz;
    unordered_map<int, int> mapping;
public:
    Blacklist(int N, vector<int>& blacklist) {
        //先将所有黑名单数字加入 map
        sz = N - (int)blacklist.size();
        for (int b: blacklist) {
            //目的仅仅是把键存入哈希表
            //方便快速判断数字是否在黑名单中
            mapping[b] = 1;
        }
        
        int last = N - 1;
        for (int b: blacklist) {
            //不应该不必要建立映射，因为是黑名单的数字不用返回
            if (b >= sz) {
                continue;
            }
            
            //跳过所有黑名单中的数字
            while (mapping.count(last)) {
                last--;
            }
            
            //将黑名单中的索引映射到合法数字
            mapping[b] = last;
            last--;
        }
    }
    
    int pick() {
        //随机选取一个索引，小于N - blacklist.size()范围内的
        int index = rand() % sz;
        //这个索引命中了黑名单
        //需要被映射到其他位置
        if (mapping.count(index)) {
            return mapping[index];
        }
        
        //若没有命中黑名单，则直接返回
        return index;
    }
};

int main(int argc, const char * argv[]) {
    cout << "-- RandomizedSet --" << endl;
    RandomizedSet randomSet;
    randomSet.insert(1);
    randomSet.remove(2);
    randomSet.insert(2);
    randomSet.getRandom();
    randomSet.remove(1);
    randomSet.insert(2);
    randomSet.getRandom();
    
    return 0;
}
