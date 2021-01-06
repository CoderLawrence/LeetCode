//
//  TTHeap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2021/1/4.
//

#ifndef TTHeap_hpp
#define TTHeap_hpp

template <class T>
class TTHeap {
public:
    /// 获取堆大小
    virtual int size() const = 0;
    /// 判断堆是否为空
    virtual bool isEmpty() const = 0;
    /// 添加元素
    virtual void add(const T &element) = 0;
    /// 获取对顶元素
    virtual T get() = 0;
    /// 删除堆顶元素
    virtual T remove() = 0;
    virtual void clear() = 0;
};

#endif /* TTHeap_hpp */
