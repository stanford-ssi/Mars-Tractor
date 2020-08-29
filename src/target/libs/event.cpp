#include <event.hpp>
Event::Event(const Event& obj)
{
    hasEvent = obj.hasEvent;
    signal = obj.signal;
}
Event::~Event() {}