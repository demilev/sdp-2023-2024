#pragma once

template <typename T>
class Set
{
public:
    virtual bool contains(const T &data) = 0;
    virtual void add(const T &data) = 0;
    virtual void remove(const T &data) = 0;
    virtual int size() = 0;
    virtual bool empty() = 0;
};
