#pragma once
#ifndef OVERLOAD_IF_HPP
#define OVERLOAD_IF_HPP

template <bool flag, class T>
struct overload_if {
   public:
    typedef T type;
};
template <class T>
struct overload_if<false, T> {};

#endif
