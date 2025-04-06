#include "Configuration.hpp"

void Configuration::printConfig(int _index)
{
    corrFunPrint();
    corrPairPrint();
    corrAvePrint();
}

void Configuration::corrFunPrint()
{
    std::ofstream file;
    file.open("CorrFun_L_" + toStr(L) + "_K_" + toStr(K) + "_J_" + toStr(J) + ".dat");
    file << "# num = " << para.corr_num << '\n';
    file << "# L = " << L << '\n';
    file << "# K = " << K << '\n';
    file << "# J = " << J << '\n';    
    for (unsigned i = 0; i < int(L / 2.0); i++)
    {
        file << i << '\t' << para.Corr_Fun[i] / para.corr_num << '\n';
    }
    file.close();
}

void Configuration::corrPairPrint()
{
    std::ofstream file;
    file.open("CorrPair_L_" + toStr(L) + "_K_" + toStr(K) + "_J_" + toStr(J) + ".dat");
    file << "# num = " << para.corr_num << '\n';
    file << "# L = " << L << '\n';
    file << "# K = " << K << '\n';
    file << "# J = " << J << '\n';
    for (unsigned i = 0; i < int(L / 2.0); i++)
    {
        file << i << '\t' << para.Corr_Pair[i] / para.corr_num << '\n';
    }
    file.close();
}

void Configuration::corrAvePrint()
{
    std::ofstream file;
    file.open("CorrAve_L_" + toStr(L) + "_K_" + toStr(K) + "_J_" + toStr(J) + ".dat");
    file << "# num = " << para.corr_num << '\n';
    file << "# L = " << L << '\n';
    file << "# K = " << K << '\n';
    file << "# J = " << J << '\n';
    for (unsigned i = 0; i < int(L / 2.0); i++)
    {
        file << i << '\t' << para.Corr_Ave[i] / para.corr_num << '\n';
    }
    file.close();
}