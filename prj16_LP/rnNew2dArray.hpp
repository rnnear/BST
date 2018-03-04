//This hpp file has realized 2 demension array with dynamic memery and 
//it's good to use that in passing argument of function
#include<cstddef>
#include<cstring>
#include<stdexcept>
#ifndef RNNEW2DARRAY_HPP
#define RNNEW2DARRAY_HPP
template<typename T>
T** rnNew2dArray(const size_t rnrow, const size_t rncol, char rnc = '\0')
{
	if(!(rnrow&&rncol))
		throw std::runtime_error("Wrong array size.");
	T** rnarr = new T*[rnrow];
	if(!rnarr)
		throw std::runtime_error("Memery allocate wrong.");
	rnarr[0] = new T[rnrow*rncol];
	if(!rnarr[0])
	{
		delete[] rnarr;
		throw std::runtime_error("Memery allocate wrong.");
	}
	std::memset(rnarr[0],rnc,rnrow*rncol*sizeof(T));
	for(std::size_t rncnt = 1; rncnt < rnrow; ++rncnt)
		rnarr[rncnt] = rnarr[rncnt - 1] + rncol;
	return rnarr;
}
template<typename T>
T** rnNew2dArray(const size_t rnrow, char rnc = '\0')
{
	return rnNew2dArray<T>(rnrow, rnrow, rnc);
}
template<typename T>
void rnDelete2dArray(T** rnarr)
{
	if(rnarr == nullptr)
		return;
	else
	{
		delete[] rnarr[0];
		delete[] rnarr;
	}
}
#endif
