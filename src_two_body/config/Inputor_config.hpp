#pragma once

void Inputor::initInputor()
{
    setGroup("Model_Parameters");
    addInputor(para.Nspin         ,   "N"               , 		    2                 );
    addInputor(para.beta          ,   "beta"            , 		    1                 );
    addInputor(para.J             ,   "J"               , 		    1                 );
    addInputor(para.K             ,   "K"               , 		    1                 );
    addInputor(para.L             ,   "L"               , 		    4                 );

}
