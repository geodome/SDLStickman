#include <functional>
#include <map>
#include <stdexcept>
#include <format>
#include <memory>

template<typename T>
class Observable {
    std::string name;
    std::map<std::string,std::function<bool(const T&)>> subscribers;
    std::map<std::string,std::shared_ptr<Observable<T>>> observers;
    void _notify(const T& data) {
        for(auto [name, to_notify]: subscribers) {
            if(to_notify(data)) observers[name]->_notify(data);
        }
    }
public:
    static std::shared_ptr<Observable<T>> factory(std::string name) {
        return std::make_shared<Observable<T>>(name);
    }
    Observable(std::string n): name{n} {}
    ~Observable() {}
    std::shared_ptr<Observable<T>> then(std::string name, std::function<bool(const T&)> notifier) {
        if (observers.contains(name)) throw std::invalid_argument(std::format("the name {} is already used", name));
        subscribers[name] = notifier;
        observers[name] = std::make_shared<Observable<T>>(name);
        return observers[name];
    }
    void notify(const T data) {
        _notify(data);
    }
    void erase(std::string name) {
        if(!observers.contains(name)) return;
        subscribers.erase(name);
        observers.erase(name);
    }
};
