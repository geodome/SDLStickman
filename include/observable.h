#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <iostream>
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

template <typename T1, typename T2>
requires (!std::is_void_v<T1> && !std::is_void_v<T2>)
class Observable2 {
    std::string name;
    std::map<std::string, std::pair<std::shared_ptr<Observable2>, std::function<bool(const T1&, const T2&)>>> subscribers{};
    void _notify(T1& msg1, T2& msg2) {
        for(auto& [name, pair]: subscribers) {
            auto& [observer, to_notify] = pair;
            if(to_notify(msg1, msg2)) observer->_notify(msg1, msg2);
        }
    }
public:
    Observable2(const std::string& n): name{n} {}
    ~Observable2() {}
    std::shared_ptr<Observable2> then(const std::string& name, std::function<bool(const T1&, const T2&)> notifier) {
        if(subscribers.contains(name)) {
            auto msg = std::format("identifier {} is already used.", name);
            throw std::invalid_argument(msg);
        }
        auto observer = std::make_shared<Observable2<T1,T2>>(name);
        subscribers[name] = {observer, notifier};
        return observer;
    }
    void notify(T1 msg1, T2 msg2) {
        _notify(msg1, msg2);
    }
    bool erase(std::string id) {
        if(!subscribers.contains(id)) return false;
        subscribers.erase(id);
        std::cout << "Observer " << name << " removes " << id << std::endl;
        return true;
    }
};

#endif
