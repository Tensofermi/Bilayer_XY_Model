#pragma once
#include <bits/stdc++.h>
#include "../Parameter_config.hpp"
#include "../../system/Clock.hpp"
#include "../../system/IOControl.hpp"
#include "../../system/RandomNumGen.hpp"
#include "../../system/Observable.hpp"
#include "../../system/Distribution.hpp"

#include "../Lattice/LatticeList.hpp"

class Configuration
{
    Clock& ck;
    IOControl& io;
    RandomNumGen& rn;
    Parameter& para;
    Observable& obs;
    Distribution& dis;

public:
    //--- Configuration
    std::vector<double> Site;
    Hyperrectangle Latt;            
    int Dim, Nspin, L, NNb;
    long Vol;
    double Beta, J, K;

    //--- Basic parameter for algorithms
    std::vector<int> Mem, Que;
    double P_metro, P_sw;
    ClusterFind cluster;
    std::vector<int> cluster_flip_tag;

    //--- For spin flip and k-space
    std::vector<double> k_vec, k_cos, k_sin;

    //--- Basic Observables
    std::vector<int> x_max, x_min, x_now;
    long NCluster;                  // Number of clusters
    double C1, C2, S2, S4;          // Cluster size defined by particle number

public:
    Configuration(Clock& _ck, IOControl& _io, RandomNumGen& rn, Parameter& _para, Observable& _obs, Distribution& _dis);
    void initialConf();
    void initialAlgo();
    void initialMeas();
    void initialObsr();

    void updateCnf();
    bool measureOrNot();
    void measure();
    void writeCnf();

    void printConfig(int _index);
    void squarePrint();
    void corrFunPrint();
    void corrPairPrint();

    void checkCnf();

    // Basic Operation
    double randAngle();
    void randRotation();
    void yaxisFlip(long _site);
    void pointFlip(long _site);

    // Update Algorithm
    void Metropolis();
    void SwendsenWang();


};

Configuration::Configuration(Clock& _ck, IOControl& _io, RandomNumGen& _rn, Parameter& _para, Observable& _obs, Distribution& _dis) 
: ck(_ck), io(_io), rn(_rn), para(_para), obs(_obs), dis(_dis)
{
    initialConf();  // for site spin 
    initialAlgo();  // for algorithms
    initialMeas();  // for k-space and cluster measurement
    initialObsr();  // for basic observables
}

void Configuration::initialConf()
{
    //--- Initialize Basic Parameters
    Beta = para.beta;
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

    // para.Corr_Fun.resize(int(L / 2.0));
    // para.Corr_Pair.resize(int(L / 2.0));
    // para.corr_num = 0;

}


#include "UpdataScheme.hpp"
#include "PrintConfiguration.hpp"
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
