#pragma once

void Inputor::initInputor()
{
    setGroup("Model_Parameters");
    // addInputor(para.Nspin         ,   "N"               , 		    2                 );
    // addInputor(para.beta          ,   "beta"            , 		    1                 );
    
    addInputor(para.J             ,   "J"               , 		    1                 );
    addInputor(para.K             ,   "K"               , 		    1                 );
    addInputor(para.L             ,   "L"               , 		    4                 );

}

void Inputor::validateInputor()
{
    std::ostringstream errors;
    if (para.L <= 0) errors << "L must be positive\n";
    if (!std::isfinite(para.J)) errors << "J must be finite\n";
    if (!std::isfinite(para.K)) errors << "K must be finite\n";
    if (para.N_Measure == 0) errors << "N_Measure must be positive\n";
    if (para.N_Each == 0) errors << "N_Each must be positive\n";
    if (para.N_Total == 0) errors << "N_Total must be positive\n";
    if (para.NBlock < 2) errors << "NBlock must be at least 2\n";
    if (para.MaxNBin < para.NBlock) errors << "MaxNBin must be at least NBlock\n";
    if (para.NperBin == 0) errors << "NperBin must be positive\n";
    if (!errors.str().empty()) io.exportInfo(io.ErrorInfo, errors.str());
}
