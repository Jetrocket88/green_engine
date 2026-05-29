#ifndef SERVICE_H
#define SERVICE_H 

#include <unordered_map>
#include <typeindex>
#include <assert.h>

class Services {
    static std::unordered_map<std::type_index, void*> s_services;

public:
    template<typename T>
    static void provide(T* service) {
        s_services[typeid(T)] = service;
    }

    template<typename T>
    static T* get() {
        auto it = s_services.find(typeid(T));
        assert(it != s_services.end() && "Services not registered!\n") ;
        return static_cast<T*>(it->second);
    }
};
#endif //SERVICE_H
