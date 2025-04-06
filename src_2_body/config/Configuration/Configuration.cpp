#include "Configuration.hpp"

Configuration::Configuration(Clock& _ck, IOControl& _io, RandomNumGen& _rn, Parameter& _para, Observable& _obs, Histogram& _his) 
: ck(_ck), io(_io), rn(_rn), para(_para), obs(_obs), his(_his)
{
    initialConf();  // for site spin 
    initialAlgo();  // for algorithms
    initialMeas();  // for k-space and cluster measurement
    initialObsr();  // for basic observables
}

void Configuration::initialConf()
{
    //--- Initialize Basic Parameters
    Beta = 1.0;
    J = para.J;
    K = para.K;
    Dim = 3;
    L = para.L;
    Nspin = 2;

    //--- Initialize Lattice
    //             z, y, x
    Latt.set(Dim, {2, L, L});
    Vol = Latt.getVol();
    NNb = Latt.getNNb();
    Site.resize(Vol, 0);

    //--- Initialize Spin Configuration
    for (unsigned int i = 0; i < Vol; i++)
    {
        Site[i] = randAngle();
    }

}

void Configuration::initialAlgo()
{
    //--- Initialize Queue and Memory
    Que.resize(Vol);
    Mem.resize(Vol);
    for (int i = 0; i < Vol; i++)
    {
        Que[i] = 0;
        Mem[i] = 0;
    }

    //--- Initialize ClusterFind
    cluster.ini(Vol);
    cluster_flip_tag.resize(Vol, -1);

    //--- Initialize Probabilities
    P_metro = 0.0;
    P_sw = 0.0;

}

void Configuration::initialMeas()
{
    //--- k-space Measurement
    k_cos.resize(L);
    k_sin.resize(L);

    for (int i = 0; i < L; i++)
    {
        k_cos[i] = cos(2 * M_PI / (double)L * i);
        k_sin[i] = sin(2 * M_PI / (double)L * i);
    }

    //--- Geometric Measurement
    x_max.resize(Dim);
    x_min.resize(Dim);
    x_now.resize(Dim);

    for (int i = 0; i < Dim; i++)
    {
        x_max[i] = 0;
        x_min[i] = 0;
        x_now[i] = 0;
    }

}

void Configuration::initialObsr()
{
    //--- Initialize Cluster Observables
    NCluster = 0;
    C1 = 0;
    C2 = 0;
    S2 = 0;
    S4 = 0;

    para.Corr_Fun.resize(int(L / 2.0), 0);
    para.Corr_Pair.resize(int(L / 2.0), 0);
    para.Corr_Ave.resize(int(L / 2.0), 0);
    para.corr_num = 0;

}

#include "../Measurement_config.hpp"

bool Configuration::measureOrNot()
{
    return true;
}

void Configuration::writeCnf()
{
    
}

void Configuration::checkCnf()
{

}
