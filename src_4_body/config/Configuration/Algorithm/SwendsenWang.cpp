#include "../Configuration.hpp"

/* ------------------------------------------------------------------------------------*/
/* ------------------------------ Short-Range Interaction -----------------------------*/
/* ------------------------------------------------------------------------------------*/

void Configuration::SwendsenWang_A()
{
    /*
        Keep theta_i_a - theta_i_b = Const. 

         i_b         j_b
          o           o
          |           |
          |           |         E_curr
          |           |
          o           o
         i_a         j_a


         i_b        - j_b
          o           o
          |           |
          |           |         E_flip
          |           |
          o           o
         i_a        - j_a         

    */

    long i_Site, j_Site;
    double E_curr, E_flip;
    double theta_i_a, theta_j_a, theta_i_b, theta_j_b;

    cluster.reset();

    //--- Randomly rotation all sites
    randRotation();

    //--- Percolation-like Process
    for (i_Site = 0; i_Site < L*L; i_Site++)
    {
        //--- Unite all the z-direction bonds
        cluster.unite(i_Site, Latt.getNNSite(i_Site, 0));

        //--- check y-direction
        j_Site = Latt.getNNSite(i_Site, 1);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 0)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 0)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = getEnergyUnit(theta_i_a, -theta_j_a, theta_i_b, -theta_j_b);
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

        //--- check x-direction
        j_Site = Latt.getNNSite(i_Site, 2);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 0)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 0)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = getEnergyUnit(theta_i_a, -theta_j_a, theta_i_b, -theta_j_b);
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

    }

    // -1 means not examined yet; 0 means not flip; 1 means flip
    std::fill(cluster_flip_tag.begin(), cluster_flip_tag.end(), -1); 
    //--- Update spins
    for (i_Site = 0; i_Site < Vol; i_Site++)
    {
        // find the root of the cluster
        int root = cluster.find(i_Site);

        // if cluster root is not examined yet, assign 0 or 1 to the root
        if (cluster_flip_tag[root] == -1)
            cluster_flip_tag[root] = rn.getRandomDouble() < 0.5 ? 0 : 1;

        // flip the site based on the root
        if (cluster_flip_tag[root] == 1)
        {
            yaxisFlip(i_Site);
        }

    }

}



void Configuration::SwendsenWang_B1()
{
    /*
        Keep layer B unchanged.

        i_a          j_a
         o————————————o               E_curr

        i_a        j_a + pi           E_flip = - E_curr
         o————————————o         

    */
    
    long i_Site, j_Site;
    double E_curr, E_flip;
    double theta_i_a, theta_j_a, theta_i_b, theta_j_b;

    cluster.reset();

    //--- Randomly rotation all sites
    randRotation();

    //--- Percolation-like Process
    for (i_Site = 0; i_Site < L*L; i_Site++)
    {
        //--- check y-direction
        j_Site = Latt.getNNSite(i_Site, 1);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 0)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 0)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = - E_curr;
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

        //--- check x-direction
        j_Site = Latt.getNNSite(i_Site, 2);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 0)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 0)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = - E_curr;
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

    }

    // -1 means not examined yet; 0 means not flip; 1 means flip
    std::fill(cluster_flip_tag.begin(), cluster_flip_tag.end(), -1); 
    //--- Update spins
    for (long i_Site = 0; i_Site < L*L; i_Site++)
    {
        // find the root of the cluster
        int root = cluster.find(i_Site);

        // if cluster root is not examined yet, assign 0 or 1 to the root
        if (cluster_flip_tag[root] == -1)
            cluster_flip_tag[root] = rn.getRandomDouble() < 0.5 ? 0 : 1;

        // flip the site based on the root
        if (cluster_flip_tag[root] == 1)
        {
            pointFlip(i_Site);
        }

    }

}


void Configuration::SwendsenWang_B2()
{
    /*
        Keep layer A unchanged.

        i_b          j_b
         o————————————o               E_curr

        i_b        j_b + pi           E_flip = - E_curr
         o————————————o         

    */
    
    long i_Site, j_Site;
    double E_curr, E_flip;
    double theta_i_a, theta_j_a, theta_i_b, theta_j_b;

    cluster.reset();

    //--- Randomly rotation all sites
    randRotation();

    //--- Percolation-like Process
    for (i_Site = L*L; i_Site < Vol; i_Site++)
    {
        //--- check y-direction
        j_Site = Latt.getNNSite(i_Site, 1);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 5)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 5)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = - E_curr;
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

        //--- check x-direction
        j_Site = Latt.getNNSite(i_Site, 2);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 5)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 5)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = - E_curr;
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

    }

    // -1 means not examined yet; 0 means not flip; 1 means flip
    std::fill(cluster_flip_tag.begin(), cluster_flip_tag.end(), -1); 
    //--- Update spins
    for (long i_Site = L*L; i_Site < Vol; i_Site++)
    {
        // find the root of the cluster
        int root = cluster.find(i_Site);

        // if cluster root is not examined yet, assign 0 or 1 to the root
        if (cluster_flip_tag[root] == -1)
            cluster_flip_tag[root] = rn.getRandomDouble() < 0.5 ? 0 : 1;

        // flip the site based on the root
        if (cluster_flip_tag[root] == 1)
        {
            pointFlip(i_Site);
        }

    }

}



void Configuration::SwendsenWang_C()
{
    /*
        Keep theta_i_a + theta_i_b = Const. 

         i_b         j_b
          o           o
          |           |
          |           |         E_curr
          |           |
          o           o
         i_a         j_a


         i_b      j_b - pi
          o           o
          |           |
          |           |         E_flip = - E_curr
          |           |
          o           o
         i_a      j_a + pi         

    */

    long i_Site, j_Site;
    double E_curr, E_flip;
    double theta_i_a, theta_j_a, theta_i_b, theta_j_b;

    cluster.reset();

    //--- Randomly rotation all sites
    randRotation();

    //--- Percolation-like Process
    for (i_Site = 0; i_Site < L*L; i_Site++)
    {
        //--- check y-direction
        j_Site = Latt.getNNSite(i_Site, 1);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 0)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 0)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = - E_curr;
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

        //--- check x-direction
        j_Site = Latt.getNNSite(i_Site, 2);
        theta_i_a = Site[i_Site];
        theta_j_a = Site[j_Site];
        theta_i_b = Site[Latt.getNNSite(i_Site, 0)];
        theta_j_b = Site[Latt.getNNSite(j_Site, 0)];
        E_curr = getEnergyUnit(theta_i_a, theta_j_a, theta_i_b, theta_j_b);
        E_flip = - E_curr;
        P_sw = 1.0 - exp(E_curr - E_flip);
        if(rn.getRandomDouble() < P_sw)
        {
            // unite clusters
            cluster.unite(i_Site, j_Site);
        }

    }

    // -1 means not examined yet; 0 means not flip; 1 means flip
    std::fill(cluster_flip_tag.begin(), cluster_flip_tag.end(), -1); 
    //--- Update spins
    for (long i_Site = 0; i_Site < L*L; i_Site++)
    {
        // find the root of the cluster
        int root = cluster.find(i_Site);

        // if cluster root is not examined yet, assign 0 or 1 to the root
        if (cluster_flip_tag[root] == -1)
            cluster_flip_tag[root] = rn.getRandomDouble() < 0.5 ? 0 : 1;

        // flip the site based on the root
        if (cluster_flip_tag[root] == 1)
        {
            pointFlip(i_Site);  // + pi
            pointFlip_(Latt.getNNSite(i_Site, 0));  // - pi
        }

    }

}