//
//  TTHashMap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/26.
//

#ifndef TTHashMap_hpp
#define TTHashMap_hpp

#include "TTMap.hpp"

template <K, V>
class TTHashMap: public TTMap<K, V> {
private:
    int m_size;
public:
    TTHashMap() {
        m_size = 0;
    }
    
    ~TTHashMap() {
        
    }
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        
    }
    
    V put(K &key, V &value) {
        
    }
    
    V get(const K &key) {
        
    }
    
    V remove(K &key) {
        
    }
    
    bool containsKey(K &key) {
        
    }
    
    bool containsValue(V &value) {
        
    }
};

#endif /* TTHashMap_hpp */
