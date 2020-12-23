//
//  TTTreeMap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/23.
//

#ifndef TTTreeMap_hpp
#define TTTreeMap_hpp

#include "TTMap.hpp"

template <class K, class V>
class TTTreeMap: public TTMap<K, V> {
public:
    TTTreeMap() {}
    ~TTTreeMap() {}
    
    int size() {
        return 0;
    }
    
    bool isEmpty() {
        return false;
    }
    
    void clear() {
        
    }
    
    V put(const K &key, const V &value) {
        return NULL;
    }
    
    V get(const K &key) {
        return NULL;
    }
    
    V remove(const K &key) {
        return NULL;
    }
    
    bool containsKey(const K &key) {
        return false;
    }
    
    bool containsValue(const V &value) {
        return false;
    }
};

#endif /* TTTreeMap_hpp */
