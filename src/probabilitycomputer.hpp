#ifndef PROBABILITYCOMPUTER_HPP
#define PROBABILITYCOMPUTER_HPP

#include <vector>

/** 
* Computes probabilities for kmer copy numbers.
**/

class ProbabilityComputer {
public:
	ProbabilityComputer();
	ProbabilityComputer(long double mean_cn0, long double mean_cn1, long double mean_cn2);
	void set_parameters(long double mean_cn0, long double mean_c1, long double mean_c2);
	long double get_probability (size_t cn, unsigned int value) const;
private:
	std::vector<long double> means;
};
#endif // PROBABILITYCOMPUTER_HPP