#include "Vector2Plus.h"

template<typename T>
T operator*(const vec2<T> a, const vec2<T> b) {
    return (a.x*b.x) + (a.y*b.y);
}

template<typename T>
T operator% (const vec2<T> a, const vec2<T> b) {
    return (a.x*b.y) - (a.y*b.x);
}

bool operator== (const vec2f a, const vec2f b) {
    return (abs(a.x-b.x)<EPS) && (abs(a.y-b.y)<EPS);
}

bool operator== (const vec2i a, const vec2i b) {
    return (a.x==b.x && a.y==b.y);
}

