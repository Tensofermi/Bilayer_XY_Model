#pragma once

struct Parameter
{
    // Simulation Parameters
    int Seed;
    unsigned long N_Measure;
    unsigned long N_Each;
    unsigned long N_Therm;
    unsigned long N_Total;
    unsigned long NBlock;
    unsigned long MaxNBin;
    unsigned long NperBin;

    // Model Parameters
    int Nspin, L;
    double beta, K, J;

    // Observable label
    int i_M_l1, i_M_l2, i_M_t, i_M_p, i_M_ave;
    int i_Mk_l1, i_Mk_l2, i_Mk_t, i_Mk_p, i_Mk_ave;    
    int i_xi_l1, i_xi_l2, i_xi_t, i_xi_p, i_xi_ave;

    int i_corr_layer;

    // Distribution label
    // int dis_gr;

    // Function
    std::vector<double> Corr_Fun, Corr_Pair, Corr_Ave;
    double corr_num;

};