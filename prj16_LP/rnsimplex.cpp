//simplex
//rn at 2018.3.4
#include"rnsimplex.h"

rnlp_data rnsimplex::rnpivot(const rnlp_data& rnlp, const size_type rnl, const size_type rne, data_type& rnvalue) const
{
	rnlp_data rnlp_ret(rnlp.n, rnlp.m);  // new lp data

	//compute the coefficients of the equation for new basic variable Xe
	auto rnAle = rnlp.mat_A[rnl][rne];
	rnlp_ret.vec_b[rne] = rnlp.vec_b[rnl]/rnAle;
	for(auto rnindex: rnlp.vec_N)
	{
		if(rnindex == rne)
			continue;
		rnlp_ret.mat_A[rne][rnindex] = rnlp.mat_A[rnl][rnindex]/rnAle;
	}
	rnlp_ret.mat_A[rne][rnl] = 1/rnAle;
	//compute the coefficients of the remaining constraints
	for(auto rnrow: rnlp.vec_B)
	{
		if(rnrow == rnl)
			continue;
		rnlp_ret.vec_b[rnrow] = rnlp.vec_b[rnrow] - rnlp.mat_A[rnrow][rne]*rnlp_ret.vec_b[rne];
		for(auto rncol: rnlp.vec_N)
		{
			if(rncol == rne)
				continue;
			rnlp_ret.mat_A[rnrow][rncol] = rnlp.mat_A[rnrow][rncol] - rnlp.mat_A[rnrow][rne]*rnlp_ret.mat_A[rne][rncol];
		}
		rnlp_ret.mat_A[rnrow][rnl] = -rnlp.mat_A[rnrow][rne]*rnlp_ret.mat_A[rne][rnl];
	}
	//compute the objective function
	rnvalue += rnlp.vec_c[rne]*rnlp_ret.vec_b[rne];
	for(auto rnindex: rnlp.vec_N)
	{
		if(rnindex == rne)
			continue;
		rnlp_ret.vec_c[rnindex] = rnlp.vec_c[rnindex] - rnlp.vec_c[rne]*rnlp_ret.mat_A[rne][rnindex];
	}
	rnlp_ret.vec_c[rnl] = -rnlp.vec_c[rne]*rnlp_ret.mat_A[rne][rnl];
	//compute new sets
	for(size_type rncnt = 0; rncnt < rnlp.n; ++rncnt)
	{
		if(rnlp.vec_N[rncnt] == rne)
			rnlp_ret.vec_N[rncnt] = rnl;
		else
			rnlp_ret.vec_N[rncnt] = rnlp.vec_N[rncnt];
	}
	for(size_type rncnt = 0; rncnt < rnlp.m; ++rncnt)
	{
		if(rnlp.vec_B[rncnt] == rnl)
			rnlp_ret.vec_B[rncnt] = rne;
		else
			rnlp_ret.vec_B[rncnt] = rnlp.vec_B[rncnt];
	}
	return rnlp_ret;
}
