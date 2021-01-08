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
#include <vector>

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
        T element = m_data[index];
        ///其实就是第一个叶子结点的前一个节点开始，因为这样才有子节点进行比较（完全二叉树的性质）
        int half = m_size >> 1;
        while (index < half) { //必须保证index位置为非叶子节点
            //获得子节点(i * 2) + 1，默认为左子节点
            int childIndex = (index << 1) + 1;
            T child = m_data[childIndex];
            int rightIndex = childIndex + 1;
            //比较左右子节点，看哪个子节点的值比较大
            if (rightIndex < m_size && compare(m_data[rightIndex], child) > 0) {
                childIndex = rightIndex;
                child = m_data[rightIndex];
            }
            
            if (compare(element, child) >= 0) break;
            m_data[index] = child;
            index = childIndex;
        }
        
        m_data[index] = element;
    }
    
    void heapify() {
        // 自下而上的下滤
        for (int i = (m_size >> 1) - 1; i >= 0; i--) {
            siftDown(i);
        }
    }
public:
    TTBinaryHeap() {
        m_capacity = DEFUALT_CAPACITY;
        m_data = new T[m_capacity];
    }
    
    /// 批量建堆接口
    TTBinaryHeap(const vector<T> &elements) {
        int len =  (int)elements.size();
        if (len <= 0) {
            m_capacity = DEFUALT_CAPACITY;
            m_data = new T[m_capacity];
        } else { //批量建堆
            m_size = len;
            m_capacity = max(len, DEFUALT_CAPACITY);
            m_data = new T[m_capacity];
            for (int i = 0; i < m_size; i++) {
                m_data[i] = elements[i];
            }
            
            heapify();
        }
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
    
    T replace(const T &element) {
        nullElementCheck(element);
        T root = NULL;
        if (m_size == 0) {
            m_data[0] = element;
            m_size++;
        } else {
            root = m_data[0];
            m_data[0] = element;
            siftDown(0);
        }
        
        return root;
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
