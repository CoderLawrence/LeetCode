//
//  TTMap.hpp
//  ALGCpp
//
//  Created by Lawrence on 2020/12/17.
//

#ifndef TTMap_hpp
#define TTMap_hpp

template <class K, class V>
class TTMap {
public:
    TTMap() {}
    ~TTMap() {}
    
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual V put(const K &key, const V &value) = 0;
    virtual V get(const K &key) = 0;
    virtual V remove(const K &key) = 0;
    virtual bool containsKey(const K &key) = 0;
    virtual bool containsValue(const V &value) = 0;
};

#endif /* TTMap_hpp */
