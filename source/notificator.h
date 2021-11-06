#pragma once
#include <memory>
#include <map>
#include <deque>
#include <algorithm>
#include <iostream>
#include <source_location>

enum class EVENT {
    week_is_change,
    day_is_change,
    full_alco,
    full_stress,
    drink_alco,
    time_is_up,
    time_zone_next
};


class NotificationObject;

class Notificator {
public:
    using ptrObject = std::shared_ptr<NotificationObject>;

private:
    std::map<EVENT, std::deque<ptrObject>> listerens;

    static Notificator* NotificatorInstance;

    Notificator() {};
public:

    Notificator(Notificator& other) = delete;

    void operator=(const Notificator&) = delete;

    void notifListerens(EVENT ev);

	void addSubscriber(EVENT ev, ptrObject sub);

	void removeSubscriber(EVENT ev, ptrObject sub);

    static Notificator* GetInstance();

};



class NotificationObject :public std::enable_shared_from_this<NotificationObject> {
public:
    NotificationObject() {};

    virtual void onEvent(EVENT ev) {

    }
protected:
	void subcribe(EVENT ev, bool subscribe = true);
};

