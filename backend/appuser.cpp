#include "appuser.h"

QString AppUser::typeToStr(int type)
{
    switch (type)
    {
    case AppUser::Racer:
        return "Racer";
    case AppUser::Cashier:
        return "Cashier";
    case AppUser::Administrator:
        return "Administrator";
    }

    return "";
}
