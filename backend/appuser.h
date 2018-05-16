#ifndef APPUSER_H
#define APPUSER_H

#include <QString>

class AppUser
{
public:
    static const int Racer = 1;
    static const int Cashier = 2;
    static const int Administrator = 3;

    static QString typeToStr(int type);
};

#endif // APPUSER_H
