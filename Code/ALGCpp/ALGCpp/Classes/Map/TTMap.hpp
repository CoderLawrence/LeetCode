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
private:
    int m_size;
public:
    TTMap():m_size(0) {}
    ~TTMap() {}
    
    int size() const {
        return m_size;
    }
    
    bool isEmpty() const {
        return m_size == 0;
    }
    
    void clear() {
        m_size = 0;
    }
    
    V put(const K &key, const V &value) {
        
    }
    
    V get(const K &key) {
        
    }
    
    void remove(const K &key) {
        
    }
    
    bool containsKey(const K &key) {
        
    }
    
    bool containsValue(const V &value) {
        
    }
};

#endif /* TTMap_hpp */