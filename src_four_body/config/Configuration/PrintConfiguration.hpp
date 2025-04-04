# pragma once

void Configuration::printConfig(int _index)
{
    // squarePrint();
    // corrFunPrint();
    // corrPairPrint();
}

void Configuration::squarePrint()
{
    // if(Dim!=2) return;           // only for two dimensions
    // if(Nspin!=1) return;       // only for Ising model

    // std::string str;
    // double theta;

    // str += "//---Layer One\n";
    // for (int i = 0; i < para.L; i++)
    // {   
    //     for (int j = 0; j < para.L; j++)
    //     {
    //         std::vector<int> coor = {0, j ,i};
    //         theta = atan2(Site[Latt.getSite(coor)][1], Site[Latt.getSite(coor)][0]) * 180.0 / M_PI;;
    //         str += r_jf(theta, 3)  + "    ";
    //     }
    //     str += "\n";
    // }

    // str += "//---Layer Two\n";
    // for (int i = 0; i < para.L; i++)
    // {   
    //     for (int j = 0; j < para.L; j++)
    //     {
    //         std::vector<int> coor = {1, j ,i};
    //         theta = atan2(Site[Latt.getSite(coor)][1], Site[Latt.getSite(coor)][0]) * 180.0 / M_PI;;
    //         str += r_jf(theta, 3)  + "    ";
    //     }
    //     str += "\n";
    // }

    
    // io.exportInfo(io.TestiInfo, str);
}

// void Configuration::corrFunPrint()
// {
//     std::ofstream file;
//     file.open("CorrFun_L_" + toStr(L) + "_K_" + toStr(K) + "_J_" + toStr(J) + ".dat");
//     for (unsigned i = 0; i < int(L / 2.0); i++)
//     {
//         file << i << '\t' << para.Corr_Fun[i] / para.corr_num << '\n';
//     }
//     file.close();
// }

// void Configuration::corrPairPrint()
// {
//     std::ofstream file;
//     file.open("CorrPair_L_" + toStr(L) + "_K_" + toStr(K) + "_J_" + toStr(J) + ".dat");
//     for (unsigned i = 0; i < int(L / 2.0); i++)
//     {
//         file << i << '\t' << para.Corr_Pair[i] / para.corr_num << '\n';
//     }
//     file.close();
// }