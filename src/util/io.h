#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iosfwd>

class b2Vec2;

std::ostream& operator<<(std::ostream& out, b2Vec2 v);

#endif // IO_H_INCLUDED
