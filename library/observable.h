#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <functional>
#include <map>
#include <stdexcept>
#include <format>
#include <memory>


template <typename T>
requires (!std::is_void_v<T>)
class Observable {
    std::string name;
    std::map<std::string, std::pair<std::shared_ptr<Observable>, std::function<bool(const T&)>>> subscribers{};
    void _notify(T& msg) {
        for(auto& [name, pair]: subscribers) {
            auto& [observer, to_notify] = pair;
            if(to_notify(msg)) observer->_notify(msg);
        }
    }
public:
    Observable(const std::string& n): name{n} {}
    ~Observable() {}
    std::shared_ptr<Observable> then(const std::string& name, std::function<bool(const T&)> notifier) {
        if(subscribers.contains(name)) {
            auto msg = std::format("identifier {} is already used.", name);
            throw std::invalid_argument(msg);
        }
        auto observer = std::make_shared<Observable<T>>(name);
        subscribers[name] = {observer, notifier};
        return observer;
    }
    void notify(T msg) {
        _notify(msg);
    }
    bool erase(std::string id) {
        if(!subscribers.contains(id)) return false;
        subscribers.erase(id);
        std::cout << "Observer " << name << " removes " << id << std::endl;
        return true;
    }
};

#endif
