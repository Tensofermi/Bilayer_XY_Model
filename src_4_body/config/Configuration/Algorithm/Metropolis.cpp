#include "../Configuration.hpp"

/* ------------------------------------------------------------------------------------*/
/* ------------------------------ Short-Range Interaction -----------------------------*/
/* ------------------------------------------------------------------------------------*/

void Configuration::Metropolis()
{
    long i_Site, j_Site;
    double theta_new, phi_new_i, phi_i, phi_j;
    double dE;

    for (unsigned int i = 0; i < Vol; i++)
    {
        // i_Site = rn.getRandomNum(Vol);

        i_Site = i;
        
        theta_new = randAngle();

        //--- Calculate Delta Energy
        dE = 0.0;
        for (unsigned int j = 0; j < NNb; j++)
        {
            // check whether to skip or not
            if(j == 0) continue;     // skip top   
            if(j == 5) continue;     // skip bottom

            j_Site = Latt.getNNSite(i_Site, j);

            //--- in-layer interaction J
            dE += - J * cos(modAngle(theta_new - Site[j_Site])) + J * cos(modAngle(Site[i_Site] - Site[j_Site]));
            
            phi_new_i = modAngle(theta_new + Site[Latt.getNNSite(i_Site, 0)]);
            phi_i = modAngle(Site[i_Site] + Site[Latt.getNNSite(i_Site, 0)]);
            phi_j = modAngle(Site[j_Site] + Site[Latt.getNNSite(j_Site, 0)]);
            //--- pairing interaction K
            dE += - K * cos(modAngle(phi_new_i - phi_j)) + K * cos(modAngle(phi_i - phi_j));

        }

        //--- Attempt to Update
        P_metro = exp(- Beta * dE);
        if(rn.getRandomDouble() < P_metro)
            Site[i_Site] = theta_new;
    }

}

