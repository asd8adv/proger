#include "notificator.h"

Notificator* Notificator::NotificatorInstance = nullptr;;

//
/*********************************
*********class Notificator********
*********************************/

Notificator* Notificator::GetInstance() {
	if (NotificatorInstance == nullptr)
		NotificatorInstance = new Notificator();
	return NotificatorInstance;
}

void Notificator::notifListerens(EVENT ev) {
	auto it = listerens.find(ev);
	if (it != listerens.end()) {
		std::for_each(it->second.begin(), it->second.end(), [ev](ptrObject obj) {
			(obj)->onEvent(ev);
			});
	}
}

void Notificator::addSubscriber(EVENT ev, ptrObject sub) {
	listerens[ev].push_back(sub);
}

void Notificator::removeSubscriber(EVENT ev, ptrObject sub) {
	auto vec = &listerens[ev];
	auto it = std::find(vec->begin(), vec->end(), sub);
	if (it == vec->end()) {
		std::source_location location = std::source_location::current();
		std::cerr << "error subscriber not found! file:" << location.file_name() << " line:" << location.line() + 1;
		return;
	}
	vec->erase(it);
}

/*********************************
*****class NotificationObject*****
*********************************/
void NotificationObject::subcribe(EVENT ev, bool subscribe) {
	if (subscribe) {
		Notificator::GetInstance()->addSubscriber(ev, shared_from_this());
	}
	else {
		Notificator::GetInstance()->removeSubscriber(ev, shared_from_this());
	}
}