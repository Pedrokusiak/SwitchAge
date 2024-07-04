#ifndef EVENTPORT_HPP
#define EVENTPORT_HPP

class EventPort {
public:
    virtual ~EventPort() = default;
    virtual bool pollEvent() = 0;
    virtual bool isQuitEvent() const = 0;
    virtual bool isKeyDownEvent() const = 0;
    virtual int getKey() const = 0;
};

#endif // EVENTPORT_HPP
