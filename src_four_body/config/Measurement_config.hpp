# pragma once

// ------------------------------------------------------------------------
// This function passes the config data into the observable for collection.
// ------------------------------------------------------------------------
void Configuration::measure()
{

    //--- Spin Observables
	std::vector<double> subSpin_1, subSpin_2, pairSpin, aveSpin, tempSpin;
	subSpin_1.resize(Nspin, 0);
	subSpin_2.resize(Nspin, 0);
	pairSpin.resize(Nspin, 0);
    aveSpin.resize(Nspin, 0);
	tempSpin.resize(Nspin, 0);

    std::vector<double> mk_c, mk_s;
	double Mk2_temp_1 ,Mk2_temp_2;
	mk_c.resize(Nspin, 0);
	mk_s.resize(Nspin, 0);

	//--- Layer One	
	for (unsigned int i = 0; i < L*L; i++)
	{
		tempSpin[0] = cos(Site[i]); // x
		tempSpin[1] = sin(Site[i]); // y

		subSpin_1 = subSpin_1 + tempSpin;

		mk_c = mk_c + k_cos[Latt.getComponent(i,2)] * tempSpin;
		mk_s = mk_s + k_sin[Latt.getComponent(i,2)] * tempSpin;

	}
 
	obs.Ob[para.i_M_l1] = abs(subSpin_1) * abs(subSpin_1);

	Mk2_temp_1 = 0;
	for (int i = 0; i < Nspin; i++)
		Mk2_temp_1 += mk_c[i] * mk_c[i] + mk_s[i] * mk_s[i];

	obs.Ob[para.i_Mk_l1] = Mk2_temp_1;

	//--- Layer Two	
	std::fill(mk_c.begin(), mk_c.end(), 0);
	std::fill(mk_s.begin(), mk_s.end(), 0);
	for (unsigned int i = L*L; i < Vol; i++)
	{
		tempSpin[0] = cos(Site[i]); // x
		tempSpin[1] = sin(Site[i]); // y

		subSpin_2 = subSpin_2 + tempSpin;
	
		mk_c = mk_c + k_cos[Latt.getComponent(i,2)] * tempSpin;
		mk_s = mk_s + k_sin[Latt.getComponent(i,2)] * tempSpin;    
    
    }
	
	obs.Ob[para.i_M_l2] = abs(subSpin_2) * abs(subSpin_2);

    Mk2_temp_2 = 0;
	for (int i = 0; i < Nspin; i++)
		Mk2_temp_2 += mk_c[i] * mk_c[i] + mk_s[i] * mk_s[i];

	obs.Ob[para.i_Mk_l2] = Mk2_temp_2;

	//--- Total Layer
	obs.Ob[para.i_M_t] = abs(subSpin_1 + subSpin_2) * abs(subSpin_1 + subSpin_2);

    obs.Ob[para.i_Mk_t] = Mk2_temp_1 + Mk2_temp_2;
	
    //--- Pairing 	
	std::fill(mk_c.begin(), mk_c.end(), 0);
	std::fill(mk_s.begin(), mk_s.end(), 0);    
	for (unsigned int i = 0; i < L*L; i++)
	{
		tempSpin[0] = cos(Site[i] + Site[Latt.getNNSite(i,0)]); // x
		tempSpin[1] = sin(Site[i] + Site[Latt.getNNSite(i,0)]); // y

		pairSpin = pairSpin + tempSpin;

        mk_c = mk_c + k_cos[Latt.getComponent(i,2)] * tempSpin;
		mk_s = mk_s + k_sin[Latt.getComponent(i,2)] * tempSpin;

	}
	
    obs.Ob[para.i_M_p] = abs(pairSpin) * abs(pairSpin);

	Mk2_temp_2 = 0;
	for (int i = 0; i < Nspin; i++)
		Mk2_temp_2 += mk_c[i] * mk_c[i] + mk_s[i] * mk_s[i];

	obs.Ob[para.i_Mk_p] = Mk2_temp_2;

    //--- Averaging
    std::fill(mk_c.begin(), mk_c.end(), 0);
	std::fill(mk_s.begin(), mk_s.end(), 0);
    for (unsigned int i = 0; i < L*L; i++)
	{
		tempSpin[0] = cos(Site[i]) + cos(Site[Latt.getNNSite(i,0)]); // x
		tempSpin[1] = sin(Site[i]) + sin(Site[Latt.getNNSite(i,0)]); // y
		
        aveSpin = aveSpin + 0.5 * tempSpin;
	
		mk_c = mk_c + 0.5 * k_cos[Latt.getComponent(i,2)] * tempSpin;
		mk_s = mk_s + 0.5 * k_sin[Latt.getComponent(i,2)] * tempSpin;    
    
    }

	obs.Ob[para.i_M_ave] = abs(aveSpin) * abs(aveSpin);

	Mk2_temp_2 = 0;
	for (int i = 0; i < Nspin; i++)
		Mk2_temp_2 += mk_c[i] * mk_c[i] + mk_s[i] * mk_s[i];

	obs.Ob[para.i_Mk_ave] = Mk2_temp_2;

}
