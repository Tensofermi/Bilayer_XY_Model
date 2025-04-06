#include "../Configuration.hpp"

double Configuration::getEnergyUnit(long _site_i_a, long _site_j_a, long _site_i_b, long _site_j_b)
{
    //     i_b    J    j_b
    //      o-----------o
    //      |
    //      | K
    //      |
    //      o-----------o
    //     i_a    J    j_a
        
    double Ea = - J * cos(Site[_site_i_a] - Site[_site_j_a]);
    double Eb = - J * cos(Site[_site_i_b] - Site[_site_j_b]);
    double Ep = - K * cos(Site[_site_i_a] + Site[_site_i_b] - Site[_site_j_a] - Site[_site_j_b]);
    
    return Ea + Eb + Ep;
}

double Configuration::getEnergyUnit(double _theta_i_a, double _theta_j_a, double _theta_i_b, double _theta_j_b)
{
    //     i_b    J    j_b
    //      o-----------o
    //      |
    //      | K
    //      |
    //      o-----------o
    //     i_a    J    j_a

    double Ea = - J * cos(_theta_i_a - _theta_j_a);
    double Eb = - J * cos(_theta_i_b - _theta_j_b);
    double Ep = - K * cos(_theta_i_a + _theta_i_b - _theta_j_a - _theta_j_b);
    
    return Ea + Eb + Ep;
}

/* ------------------------------------------------------------------------------------*/
/* ---------------------------------- Spin Operation ----------------------------------*/
/* ------------------------------------------------------------------------------------*/

double Configuration::randAngle()
{
    // Angle \in [-π, π)
    return rn.getRandomDouble(0, 2 * M_PI)  - M_PI;
}

void Configuration::exchangeLayer()
{
    std::vector<double> temp = Site;

    for (long i = 0; i < L*L; i++)
    {
        Site[i] = temp[Latt.getNNSite(i, 0)];
        Site[Latt.getNNSite(i, 0)] = temp[i];
    }
}

void Configuration::randRotation()
{
    double theta = randAngle();
    for (int i = 0;  i < Vol; i++)
    {
        Site[i] = modAngle(Site[i] + theta);
    }
}

void Configuration::yaxisFlip(long _site)
{
    Site[_site] = modAngle( - Site[_site]);
}

void Configuration::pointFlip(long _site)
{
    Site[_site] = modAngle(Site[_site] + M_PI);
}

void Configuration::pointFlip_(long _site)
{
    Site[_site] = modAngle(Site[_site] - M_PI);
}

