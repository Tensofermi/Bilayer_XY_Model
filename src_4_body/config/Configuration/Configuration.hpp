#pragma once
#include <bits/stdc++.h>
#include "../../system/Header.hpp"
#include "../Lattice/Lattice.hpp"

class Configuration
{
    Clock& ck;
    IOControl& io;
    RandomNumGen& rn;
    Parameter& para;
    Observable& obs;
    Histogram& his;

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
    Configuration(Clock& _ck, IOControl& _io, RandomNumGen& rn, Parameter& _para, Observable& _obs, Histogram& _dis);
    void initialConf();
    void initialAlgo();
    void initialMeas();
    void initialObsr();

    void updateCnf();
    bool measureOrNot();
    void measure();
    void writeCnf();

    void printConfig(int _index);
    void corrFunPrint();
    void corrPairPrint();
    void corrAvePrint();

    void checkCnf();

    // Basic Operation
    double getEnergyUnit(long _site_i_a, long _site_j_a, long _site_i_b, long _site_j_b);
    double getEnergyUnit(double _theta_i_a, double _theta_j_a, double _theta_i_b, double _theta_j_b);
    double randAngle();
    void exchangeLayer();
    void randRotation();
    void yaxisFlip(long _site);
    void pointFlip(long _site);
    void pointFlip_(long _site);

    // Update Algorithm
    void Metropolis();
    void SwendsenWang_A();
    void SwendsenWang_B1();
    void SwendsenWang_B2();
    void SwendsenWang_C();


};
