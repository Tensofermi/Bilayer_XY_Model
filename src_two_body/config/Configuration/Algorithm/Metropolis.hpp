#pragma once

/* ------------------------------------------------------------------------------------*/
/* ------------------------------ Short-Range Interaction -----------------------------*/
/* ------------------------------------------------------------------------------------*/

void Configuration::Metropolis()
{
    long i_Site, j_Site, zi_coor, zj_coor;
    double theta_new;
    double dE;

    for (unsigned int i = 0; i < Vol; i++)
    {
        i_Site = rn.getRandomNum(Vol);
        
        theta_new = randAngle();

        //--- Calculate Delta Energy
        dE = 0.0;
        for (unsigned int j = 0; j < NNb; j++)
        {
            // check whether to skip or not
            zi_coor = Latt.getComponent(i_Site, 0);  // get z coordinate for i_Site
            if(zi_coor == 1 && j == 0) continue;     // skip top     (z=1, j=0)
            if(zi_coor == 0 && j == 5) continue;     // skip bottom  (z=0, j=5)

            j_Site = Latt.getNNSite(i_Site, j);
            zj_coor = Latt.getComponent(j_Site, 0);  // get z coordinate for k_Site
            
            if(zj_coor==zi_coor)
            {
                //--- in-layer interaction J
                dE += - J * cos(modAngle(theta_new - Site[j_Site])) + J * cos(modAngle(Site[i_Site] - Site[j_Site]));
            }
            else
            {
                //--- pairing interaction K
                dE += - K * cos(modAngle(theta_new - Site[j_Site])) + K * cos(modAngle(Site[i_Site] - Site[j_Site]));
            }

        }

        //--- Attempt to Update
        P_metro = exp(- Beta * dE);
        if(rn.getRandomDouble() < P_metro)
            Site[i_Site] = theta_new;
    }

}
