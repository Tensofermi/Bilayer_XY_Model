#include "../Configuration.hpp"

/* ------------------------------------------------------------------------------------*/
/* ------------------------------ Short-Range Interaction -----------------------------*/
/* ------------------------------------------------------------------------------------*/

void Configuration::SwendsenWang()
{
    long j_Site, k_Site, zj_coor, zk_coor;
    double project, strength;

    cluster.reset();

    //--- Randomly rotation the spin for all sites
    randRotation();

    //--- Percolation-like Process
    for (long j_Site = 0; j_Site < Vol; j_Site++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            // check whether to skip or not
            zj_coor = Latt.getComponent(j_Site, 0);  // get z coordinate for j_Site
            if(zj_coor == 1 && j == 0) continue;     // skip top     (z=1, j=0)
            if(zj_coor == 0 && j == 5) continue;     // skip bottom  (z=0, j=5)

            // obtain the interacting k_Site
            k_Site = Latt.getNNSite(j_Site, j);
            zk_coor = Latt.getComponent(k_Site, 0);  // get z coordinate for k_Site

            // interaction strength for j_Site and k_Site
            strength = J;   // in the same layer
            if(zj_coor != zk_coor) strength = K;   // for different layers

            project = sin(Site[j_Site]) * sin(Site[k_Site]);
            P_sw = 1.0 - exp(-2 * Beta * strength * project);
            if(rn.getRandomDouble() < P_sw)
            {
                // unite clusters
                cluster.unite(j_Site, k_Site);
            }
        }
    }

    // -1 means not examined yet; 0 means not flip; 1 means flip
    std::fill(cluster_flip_tag.begin(), cluster_flip_tag.end(), -1); 
    //--- Update spins
    for (long i_Site = 0; i_Site < Vol; i_Site++)
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