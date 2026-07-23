# Repository guide for agents

This file applies to the whole repository. It documents the model, safe code paths, parameter planning, and the exact changes needed to reuse the task/data workflow from `Zoo_of_Classical_ON_Spin_Model`.

## Scientific purpose

This repository studies two coupled 2D XY layers at fixed temperature scale. `src_2_body` is the historical two-body model, called the **single** model in the current terminology. `src_4_body` is the historical four-body model, called the **pair** model. Both use `J` and `K` as reduced couplings and `L` as the linear size.

The single model distinguishes a disordered phase from a conventional BKT phase. The pair model supports a disordered phase, an intermediate paired-BKT phase, and a conventional BKT phase. Its importance is that composite order can acquire quasi-long-range coherence while single-spin order remains short-ranged, providing a concrete setting for emergent paired order and for the fate of BKT transitions under interlayer coupling.

Do not mix the two source trees in one dataset: identical `J,K,L` labels describe different Hamiltonians. Record `src_2_body` or `src_4_body` as campaign metadata even though it is not printed in `ouput.txt`.

## Code map and scientific contract

- `src_2_body/` and `src_4_body/` are independent implementations with parallel framework layouts.
- `<variant>/config/Inputor_config.hpp` defines `J`, `K`, and `L` and sampling validation.
- `<variant>/config/Configuration/UpdataScheme.cpp` selects updates. The two-body default is Swendsen-Wang. The four-body default randomly mixes four cluster channels and Metropolis moves.
- `<variant>/config/Measurement_config.hpp` constructs layer, total, and paired estimators.
- `<variant>/config/Observable_config.hpp` defines normalization and outputs `corr_layer`, `M_l1`, `M_l2`, `M_t`, `M_p`, `M_ave`, Fourier counterparts, and `xi_L_*` ratios.

Changes to an interaction term must update both the update acceptance/bond rules and any energy-like or correlation measurement derived from it. Preserve periodic geometry and the distinction among single-layer, total, and paired fields. Do not rename output columns without updating downstream scripts and documenting data compatibility.

## Build and single-run workflow

The Makefile currently selects `src_2_body`. Switch the assignment to `src_4_body` for the pair model, then clean before rebuilding because both variants share `build/` and `bin/a.out`.

```bash
make clean
make -j
make test
./run.sh
```

For automated work, an equivalent safe sequence is to edit the source selection explicitly, clean, build, test, and only then run. Never reuse a binary after changing the source variant without rebuilding.

`input.txt` fields are `J,K,L`, then `Seed,N_Measure,N_Each,N_Therm,N_Total,NBlock,MaxNBin,NperBin`. A smoke run uses small `L` and short counts; verify completion, finite observables, the requested Seed, and plausible bounds for normalized correlations. Production results go to the historical filename `ouput.txt`.

## Parameter planning

Use a staged phase-diagram strategy:

1. Select one Hamiltonian variant and hold it fixed.
2. Pilot on sizes such as 8, 16, and 32 over a coarse `J,K` mesh. Track both single (`M_l1`, `M_l2`, `xi_L_l1`, `xi_L_l2`) and paired (`M_p`, `xi_L_p`) sectors plus `corr_layer`.
3. Refine one-dimensional cuts normal to candidate phase boundaries. Avoid spending a dense rectangular grid far from transitions.
4. Add geometrically spaced sizes, for example 16, 32, 64, 128, after measuring runtime. Use multiple independent Seeds at every point.
5. For BKT boundaries, fit size drift and logarithmic corrections. Ordinary power-law crossing fits can give a precise but biased transition.

A paired phase is not established from a single observable. Require consistent behavior: paired correlations should show quasi-long-range scaling while single-layer correlations remain short-ranged, and the conclusion should persist under larger `L` and varied lower-size cutoffs.

`J` and `K` are validated as finite values. If antiferromagnetic or negative-coupling regimes are requested, first verify that every cluster probability and estimator remains valid; the existing production interpretation is ferromagnetic.

## Adapting the Zoo pipeline

Obtain the reference scripts beside this repository and copy `lsub/`, `qsub/`, `data/`, `fit/`, and `plot/` as needed:

```bash
git clone --depth 1 https://github.com/Tensofermi/Zoo_of_Classical_ON_Spin_Model.git ../Zoo_of_Classical_ON_Spin_Model
cp -R ../Zoo_of_Classical_ON_Spin_Model/lsub .
cp -R ../Zoo_of_Classical_ON_Spin_Model/qsub .
cp -R ../Zoo_of_Classical_ON_Spin_Model/data .
cp -R ../Zoo_of_Classical_ON_Spin_Model/fit .
cp -R ../Zoo_of_Classical_ON_Spin_Model/plot .
```

Then make all of these repository-specific edits before running anything:

- Replace Zoo model arrays `N,D,beta,L,h` with `J,K,L`; build the Cartesian product in exactly that order.
- Generate `input.txt` with `J`, `K`, `L`, followed by the eight sampling fields. Use a job name containing the variant, `J`, `K`, `L`, and Seed.
- Make the generator select `src_2_body` or `src_4_body`, run `make clean` before `make`, and use the resulting `bin/a.out`. Do not put both variants in one generator product unless each job receives a separately built, variant-specific executable.
- Adjust PBS/Slurm queue, account, partition, memory, wall time, and local parallelism to measured resource use.
- Keep the expected directory contract `jobs/<job>/input.txt` and `jobs/<job>/ouput.txt`, or change task generation and data traversal together.

For the copied formatter, the printed model order is `J,K,L`. Set `header=10` and the 1-based `seed_index=6`. The zero-based model columns are `J=0`, `K=1`, `L=2`. Update extraction/grouping indices accordingly and add the unprinted variant name to the output path or archived manifest. Format one job first and inspect both header rows before combining Seeds.

The Zoo fitting functions are not automatically appropriate. Select columns by their names, then fit single and paired sectors separately. Update input paths, x/y/error columns, phase-specific BKT ansatz, correction terms, parameter bounds, and `L_min` scan. Plot both sectors on the same campaign cuts so that the paired phase cannot be mistaken for conventional order.

## Production workflow and provenance

The expected sequence is:

1. Define the physical question, source variant, `J,K,L` pilot grid, Seeds, and stopping/statistics targets.
2. Build/test the selected variant and run one local smoke point.
3. Generate local or scheduler tasks; inspect a generated input and submission script; submit a one-point batch.
4. Submit the full campaign only after measured memory/time agree with requests.
5. Run format, collect, extract, and compress. Verify row counts before and after Seed combination.
6. Fit with BKT-aware models, scan size cutoffs, plot residuals and both order sectors, and archive the raw data.

Archive the repository commit, source variant, generated parameter file, scheduler script, compiler, Seed list, and analysis environment with every production dataset.

## Change and verification policy

- Run `make test` for both source variants after shared or mirrored changes.
- For update/energy changes, compare small seeded runs and physical identities between old and new code; explain intentional changes to simulation results.
- New observables require coordinated parameter labels, measurement, registration/normalization, formatter headers, fit columns, and tests.
- Keep Markdown formulas as `$...$` or `$$...$$`.
- Do not commit generated binaries, jobs, or bulk data unless explicitly requested. Keep commits narrow and describe motivation, implementation, validation, and effect on reproducibility.
