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


	//--------------------------------------------------------
	//--- Correlation Function Measurement
	//--------------------------------------------------------
	
	int site_i, site_j, site_pair_1, site_pair_2;
	int n_corr_sample = 250;
	int n_dx = int(L / 2.0);

    site_i = rn.getRandomNum(L*L);

    obs.Ob[para.i_corr_layer] = cos(Site[site_i] - Site[Latt.getNNSite(site_i, 0)]);
    
//--- Correlation Function
    for (unsigned int n = 0; n < n_corr_sample; n++)
    {
        site_i = rn.getRandomNum(L*L); // only for Layer A

        for (unsigned int dx = 0; dx < n_dx; dx++)
        {
            site_j = Latt.getDirSite(site_i, 2, dx);
            para.Corr_Fun[dx] += cos(Site[site_i] - Site[site_j]);

            site_j = Latt.getDirSite(site_i, 3, dx);
            para.Corr_Fun[dx] += cos(Site[site_i] - Site[site_j]);
        }

        for (unsigned int dy = 0; dy < n_dx; dy++)
        {
            site_j = Latt.getDirSite(site_i, 1, dy);
            para.Corr_Fun[dy] += cos(Site[site_i] - Site[site_j]);

            site_j = Latt.getDirSite(site_i, 4, dy);
            para.Corr_Fun[dy] += cos(Site[site_i] - Site[site_j]);
        }
    }

//--- Correlation Function (Paired)
	for (unsigned int n = 0; n < n_corr_sample; n++)
    {
        site_i = rn.getRandomNum(L*L); // only for Layer A
		site_pair_1 = Latt.getNNSite(site_i, 0);

        for (unsigned int dx = 0; dx < n_dx; dx++)
        {
            site_j = Latt.getDirSite(site_i, 2, dx);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Pair[dx] += cos(Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]);

            site_j = Latt.getDirSite(site_i, 3, dx);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Pair[dx] += cos(Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]);
        }

        for (unsigned int dy = 0; dy < n_dx; dy++)
        {
            site_j = Latt.getDirSite(site_i, 1, dy);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Pair[dy] += cos(Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]);

            site_j = Latt.getDirSite(site_i, 4, dy);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Pair[dy] += cos(Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]);
        }
    }

//--- Correlation Function (Ave)
	for (unsigned int n = 0; n < n_corr_sample; n++)
    {
        site_i = rn.getRandomNum(L*L); // only for Layer A
		site_pair_1 = Latt.getNNSite(site_i, 0);

        for (unsigned int dx = 0; dx < n_dx; dx++)
        {
            site_j = Latt.getDirSite(site_i, 2, dx);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Ave[dx] += cos((Site[site_i] - Site[site_pair_1]) / 2.0) * cos((Site[site_j] - Site[site_pair_2]) / 2.0) * cos((Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]) / 2.0);

                                

            site_j = Latt.getDirSite(site_i, 3, dx);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Ave[dx] += cos((Site[site_i] - Site[site_pair_1]) / 2.0) * cos((Site[site_j] - Site[site_pair_2]) / 2.0) * cos((Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]) / 2.0);
        }

        for (unsigned int dy = 0; dy < n_dx; dy++)
        {
            site_j = Latt.getDirSite(site_i, 1, dy);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Ave[dy] += cos((Site[site_i] - Site[site_pair_1]) / 2.0) * cos((Site[site_j] - Site[site_pair_2]) / 2.0) * cos((Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]) / 2.0);

            site_j = Latt.getDirSite(site_i, 4, dy);
			site_pair_2 = Latt.getNNSite(site_j, 0);
            para.Corr_Ave[dy] += cos((Site[site_i] - Site[site_pair_1]) / 2.0) * cos((Site[site_j] - Site[site_pair_2]) / 2.0) * cos((Site[site_i] + Site[site_pair_1] - Site[site_j] - Site[site_pair_2]) / 2.0);
        }
    }

	para.corr_num += 4 * n_corr_sample;

}