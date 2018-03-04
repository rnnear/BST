//simplex
//rn at 2018.3.3
#include<vector>
#include<cstddef>
#include<stdexcept>
#include<utility>
#include"rnNew2dArray.hpp"

class rnsimplex;
class rnlp_data
{
public:
	friend class rnsimplex;
	typedef std::size_t size_type;
	typedef long int data_type;                                          //index start from 1, except vec_N and vec_B
	rnlp_data(const size_type rnn, const size_type rnm, data_type** rnA,
			const std::vector<size_type>& rnN, const std::vector<size_type>& rnB,
			const std::vector<data_type>& rnb, const std::vector<data_type>& rnc): n(rnn), m(rnm),
	mat_A(nullptr), vec_N(rnN.cbegin(), rnN.cend()), vec_B(rnB.cbegin(), rnB.cend()), vec_b(rnb.cbegin(), rnb.cend()),
	vec_c(rnc.cbegin(), rnc.cend())
	{
		if(vec_N.size() != n||vec_B.size() != m||vec_b.size() != n+m+1||vec_c.size() != n+m+1)
			throw std::runtime_error("rnlp_data construction error: wrong parameter!\n");
		else
		{
			auto rnptr = rnNew2dArray<data_type>(n+m+1, n+m+1, 0);
			for(std::size_t rnrow = 1; rnrow < n+m+1; ++rnrow)
				for(std::size_t rncol = 1; rncol < n+m+1; ++rncol)
					rnptr[rnrow][rncol] = rnA[rnrow][rncol];//rnA[rnrow - 1][rncol - 1];
			mat_A = rnptr;
		}
	}
	rnlp_data(const size_type rnn, const size_type rnm): n(rnn), m(rnm),
	mat_A(nullptr), vec_N(rnn, 0), vec_B(rnm, 0), vec_b(rnn+rnm+1, 0),
	vec_c(rnn+rnm+1, 0)
	{
		mat_A = rnNew2dArray<data_type>(n+m+1, n+m+1, 0);
	}
	void swap(rnlp_data& rnright)
	{
		std::swap(this->n, rnright.n);
		std::swap(this->m, rnright.m);
		std::swap(this->mat_A, rnright.mat_A);
		std::swap(this->vec_N, rnright.vec_N);
		std::swap(this->vec_B, rnright.vec_B);
		std::swap(this->vec_b, rnright.vec_b);
		std::swap(this->vec_c, rnright.vec_c);
	}
	rnlp_data(const rnlp_data& rncopy)
	{
		rnlp_data rntemp(rncopy.n, rncopy.m, rncopy.mat_A, rncopy.vec_N, rncopy.vec_B, rncopy.vec_b, rncopy.vec_c);
		this->swap(rntemp);
	}
	rnlp_data& operator=(const rnlp_data& rncopy)
	{
		rnlp_data rntemp(rncopy);
		this->swap(rntemp);
		return *this;
	}

	~rnlp_data()
	{rnDelete2dArray(mat_A);}

//	size_type nonbasicNumber()const{return n;}
//	size_type basicNumber()const{return m;}

private:
	size_type n;               //nonbasic variable number
	size_type m;               //basic variable number
	data_type** mat_A;         //
	std::vector<size_type> vec_N;
	std::vector<size_type> vec_B;
	std::vector<data_type> vec_b;
	std::vector<data_type> vec_c;
};

class rnsimplex 
{
public:
	typedef rnlp_data::size_type size_type;
	typedef rnlp_data::data_type data_type;
	rnsimplex(const rnlp_data& rnlp, const data_type rnvalue = 0): lp_data(rnlp),
	vec_x(rnlp.n+rnlp.m+1, 0), value(rnvalue){}
	~rnsimplex(){}

	rnlp_data rnpivot(const rnlp_data& rnlp, const size_type rnl, const size_type rne, data_type& rnvalue) const;

private:
	rnlp_data lp_data;
	std::vector<data_type> vec_x;
	data_type value;
};
