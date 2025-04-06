#include "Configuration.hpp"

void Configuration::updateCnf()
{
//--- Short-Range Algorithm
    // Metropolis();

    double select_P = rn.getRandomDouble();
    if (select_P < 0.2)
        SwendsenWang_A();
    else if (select_P < 0.4)
        SwendsenWang_B1();
    else if (select_P < 0.6)
        SwendsenWang_B2();
    else if (select_P < 0.8)
        SwendsenWang_C();        
    else
        Metropolis();
}
