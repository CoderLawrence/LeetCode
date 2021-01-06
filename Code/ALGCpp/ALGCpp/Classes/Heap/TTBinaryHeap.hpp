//
//  TTBinaryHeap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2021/1/4.
//

#ifndef TTBinaryHeap_hpp
#define TTBinaryHeap_hpp

#include "TTHeap.hpp"
#include <optional>

/// 默认是实现大顶堆的二叉堆
/// 这里使用数组实现
template <class T>
class TTBinaryHeap: public TTHeap<T> {
private:
    T *m_data;
    int m_size = 0;
    int m_capacity = 0;
    static constexpr int DEFUALT_CAPACITY = 10;
    
    /// e1 > e2  >> 1；e1 == e2 >> 0；e1 < e2 >> -1
    int compare(const T &e1, const T &e2) {
        return e1 > e2 ? 1 : e1 == e2 ? 0 : -1;
    }
    
    void emptyCheck() {
        if (m_size == 0) {
            throw out_of_range("TTBinaryHeap:: heap is empty");
        }
    }
    
    void nullElementCheck(const T &e) {
        optional<T> op = make_optional<T>(e);
        if (!op.has_value()) {
            throw invalid_argument("TTBinaryHeap:: element must be not null");
        }
    }
    
    void ensureCapacity(const int capacity) {
        int oldCapacity = m_capacity;
        if (oldCapacity >= capacity) return;
        int newCapacity = oldCapacity + (oldCapacity >> 1);
        T *newElements =  new T[newCapacity];
        for (int i = 0; i < m_size; i++) {
            newElements[i] = m_data[i];
        }
        
        m_data = newElements;
        m_capacity = newCapacity;
    }
    
    //上滤： 复杂度跟树的高度有关O(logN)
    void siftUp(int index) {
        T e = m_data[index];
        while (index > 0) {
            //pindex (父节点索引) foor((i - 1) / 2)向下取整;
            int pindex = (index - 1) >> 1;
            T p = m_data[pindex];
            if (compare(e, p) <= 0) return;
            T temp = m_data[index];
            m_data[index] = m_data[pindex];
            m_data[pindex] = temp;
            index = pindex;
        }
    }
    
    void siftDown(int index) {
        T e = m_data[index];
        while (index < m_size) {
            //获得子节点(i * 2) + 2
            int right = (index >> 1) + 2;
            int left = (index >> 1) + 1;
            T leftNode = m_data[left];
            T rightNode = m_data[right];
            if (e <= left) {
                
            } else if (e <= right) {
                
            } else {
                return;
            }
        }
    }
public:
    TTBinaryHeap() {
        m_capacity = DEFUALT_CAPACITY;
        m_data = new T[m_capacity];
    }
    
    ~TTBinaryHeap() {
        clear();
        delete [] m_data;
    }
    
    /// 获取堆大小
    int size() const {
        return m_size;
    }
    
    /// 判断堆是否为空
    bool isEmpty() const {
        return m_size == 0;
    }
    
    /// 添加元素
    void add(const T &element) {
        nullElementCheck(element);
        ensureCapacity(m_size + 1);
        m_data[m_size++] = element;
        siftUp(m_size - 1);
    }
    
    /// 获取对顶元素
    T get() {
        emptyCheck();
        return m_data[0];
    }
    
    /// 删除堆顶元素
    T remove() {
        emptyCheck();
        int lastIndex = --m_size;
        T element = m_data[0];
        m_data[0] = m_data[lastIndex];
        m_data[lastIndex] = NULL;
        siftDown(0);
        return element;
    }
    
    void clear () {
        for (int i = 0; i < m_size; i++) {
            m_data[i] = NULL;
        }
        
        m_size = 0;
    }
    
    void print() {
        for (int i = 0; i < m_size; i++) {
            cout << m_data[i] << endl;
        }
    }
};

#endif /* TTBinaryHeap_hpp */
