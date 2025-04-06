#pragma once


void Observable::initObservable()  // add addBasicObser() & addCombiObser()
{
	int L = para.L;
	double Beta = para.beta;

    //  Observables               Name           				Description             		 		A     +     B  *  Obs 
	addBasicObser(para.i_corr_layer    , "corr_layer"   , "correlation of two layers"    				, 0     , 1.0      					);

    addBasicObser(para.i_M_l1    , "M_l1"        		, "Layer one magnetic density"    				, 0     , 1.0/L/L/L/L      					);
	addBasicObser(para.i_M_l2    , "M_l2"        	    , "Layer two magnetic density"    				, 0     , 1.0/L/L/L/L      					);
	addBasicObser(para.i_M_t     , "M_t"        	    , "Total magnetic density"    					, 0     , 1.0/L/L/2.0/L/L/2.0      	    	);
	addBasicObser(para.i_M_p     , "M_p"        	    , "Pairing magnetic density"    				, 0     , 1.0/L/L/L/L	      	    		);
	addBasicObser(para.i_M_ave   , "M_ave"        	    , "Average magnetic density"    				, 0     , 1.0/L/L/L/L	      	    		);


	addBasicObser(para.i_Mk_l1   , "Mk_l1"        		, "Layer one Fourier of magnetic density"       , 0     , 1.0/L/L/L/L    	  				);
	addBasicObser(para.i_Mk_l2   , "Mk_l2"        		, "Layer two Fourier of magnetic density" 		, 0     , 1.0/L/L/L/L   					);
	addBasicObser(para.i_Mk_t    , "Mk_t"        		, "Total Fourier of magnetic density" 			, 0     , 1.0/L/L/2.0/L/L/2.0   			);
	addBasicObser(para.i_Mk_p    , "Mk_p"        		, "Pairing Fourier of magnetic density" 		, 0     , 1.0/L/L/L/L		   				);
	addBasicObser(para.i_Mk_ave  , "Mk_ave"        		, "Average Fourier of magnetic density" 		, 0     , 1.0/L/L/L/L		   				);


	addCombiObser(para.i_xi_l1   , "xi_L_l1"    		, "Layer one correlation ratio"       			, 0     , 1.0		      				);
	addCombiObser(para.i_xi_l2 	 , "xi_L_l2"    		, "Layer two correlation ratio"    	            , 0     , 1.0		      				);
	addCombiObser(para.i_xi_t 	 , "xi_L_t"     		, "Total correlation ratio"    		            , 0     , 1.0		      				);
	addCombiObser(para.i_xi_p 	 , "xi_L_p"    			, "Pairing correlation ratio"    		        , 0     , 1.0		      				);
	addCombiObser(para.i_xi_ave  , "xi_L_ave"  			, "Average correlation ratio"    		        , 0     , 1.0		      				);


}

void Observable::calCombiObser()  // add Result[]
{
	Result[para.i_xi_l1] = 1.0 / (2 * para.L * sin(M_PI / para.L)) * sqrt(Ob[para.i_M_l1] / Ob[para.i_Mk_l1] - 1.0);

	Result[para.i_xi_l2] = 1.0 / (2 * para.L * sin(M_PI / para.L)) * sqrt(Ob[para.i_M_l2] / Ob[para.i_Mk_l2] - 1.0);
	
	Result[para.i_xi_t] = 1.0 / (2 * para.L * sin(M_PI / para.L)) * sqrt(Ob[para.i_M_t] / Ob[para.i_Mk_t] - 1.0);

	Result[para.i_xi_p] = 1.0 / (2 * para.L * sin(M_PI / para.L)) * sqrt(Ob[para.i_M_p] / Ob[para.i_Mk_p] - 1.0);

	Result[para.i_xi_ave] = 1.0 / (2 * para.L * sin(M_PI / para.L)) * sqrt(Ob[para.i_M_ave] / Ob[para.i_Mk_ave] - 1.0);

}


// ---------------------------------------------
// This function prints the Monte Carlo results.
// ---------------------------------------------
std::string Observable::printOutput(bool Flag)
{
	std::string str = "";
	ZZ0 = NBin * NperBin + IBin;

	str += "==============================================================================\n";
	str += l_jf("J = " + toStr(para.J), 22) + l_jf("K = " + toStr(para.K), 22) + l_jf("L = " + toStr(para.L), 22) + "\n";
	str += l_jf("N_Therm = " + toStr(para.N_Therm), 22) + l_jf("N_Total = " + toStr(para.N_Total), 22) + l_jf("Seed = " + toStr(para.Seed), 22) + "\n";
	str += l_jf("N_Measure = " + toStr(para.N_Measure), 22) + l_jf("N_Each = " + toStr(para.N_Each), 22) + l_jf("NBlock = " + toStr(para.NBlock), 22) + "\n";
	str += "==============================================================================\n";

	if(Flag)
	{
		double time_ratio = MCStep / (double)para.N_Each / (double)para.N_Total;

		if(NBin >= NBlock)
		{
			ZZ = (NBin / NBlock) * NBlock * NperBin;
			//--------------------------------------------------//
			//------------ obtain average and error ------------//
			//--------------------------------------------------//
			calAveErr();	
			//--------------------------------------------------//
			//------------ obtain average and error ------------//
			//--------------------------------------------------//
			str += "Average: ZZ = " + toStr(ZZ0) + " , MCStep = " + toStr(MCStep0) + " , Status = " + dou2str(100.0 * time_ratio, 2) + "%" + "\n";
			str += printAverage();
		}
		else
		{
			str += "    The samples are too few!!!\n";
		}
		str += "Simulation Time: " + ck.tick() + " , Total: " + ck.exportTime() + " , " + ck.exportNow() + "\n";

		//---------------------------------------------------------------
		//------------------ Estimate Time ------------------------------
		//---------------------------------------------------------------
		str += "==============================================================================\n";
		double total_time_estimate = fromStr<double>(ck.exportTime_sec()) / time_ratio;
		double remaining_time_estimate = total_time_estimate - fromStr<double>(ck.exportTime_sec());
		
		str += "Estimated Total Time     = " + ck.formTime(total_time_estimate) + " \t= " + dou2str(total_time_estimate, 2) + " s\n";
		str += "Estimated Remaining Time = " + ck.formTime(remaining_time_estimate) + " \t= " + dou2str(remaining_time_estimate, 2) + " s\n";
		//---------------------------------------------------------------
		//------------------ Estimate Time ------------------------------
		//---------------------------------------------------------------
	}
	else
	{	
		double time_ratio = MCStep / (double)para.N_Each / (double)para.N_Therm;
		str += "Current: ZZ0 = " + toStr(ZZ0) + " , MCStep0 = " + toStr(MCStep0) + " , Status = " + dou2str(100.0 * time_ratio, 2) + "%" + "\n";
		str += printCurrent();
		str += "Therm Time: " + ck.tick() + " , Total: " + ck.exportTime() + " , " + ck.exportNow() + "\n";
		
		//---------------------------------------------------------------
		//------------------ Estimate Time ------------------------------
		//---------------------------------------------------------------
		str += "==============================================================================\n";
		double total_time_estimate = fromStr<double>(ck.exportTime_sec()) / time_ratio;
		double remaining_time_estimate = total_time_estimate - fromStr<double>(ck.exportTime_sec());
		
		str += "Estimated Thermalizing Time  = " + ck.formTime(total_time_estimate) + "\t= " + dou2str(total_time_estimate, 2) + " s\n";
		str += "Estimated Remaining Time     = " + ck.formTime(remaining_time_estimate) + "\t= " + dou2str(remaining_time_estimate, 2) + " s\n";
		//---------------------------------------------------------------
		//------------------ Estimate Time ------------------------------
		//---------------------------------------------------------------
	}
	
	str += "==============================================================================\n";

	return str;
}