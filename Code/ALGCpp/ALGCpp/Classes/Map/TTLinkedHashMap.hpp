//
//  TTLinkedHashMap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2021/1/3.
//

#ifndef TTLinkedHashMap_hpp
#define TTLinkedHashMap_hpp

#include "TTHashMap.hpp"

template <class K, class V>
class TTLinkedHashMapNode: public TTHashMapNode<K, V> {
public:
    TTHashMapNode<K, V> *prev = NULL;
    TTHashMapNode<K, V> *next = NULL;
    TTLinkedHashMapNode():TTHashMapNode<K, V>() {}
    ~TTLinkedHashMapNode() {}
};

template <class K, class V>
class TTLinkedHashMap: public TTHashMap<K, V> {
private:
    TTHashMapNode<K, V> *frist = NULL;
    TTHashMapNode<K, V> *last = NULL;
public:
    TTLinkedHashMap():TTHashMap<K, V>() {
        
    }
    
    ~TTLinkedHashMap() {
        
    }
};

#endif /* TTLinkedHashMap_hpp */
