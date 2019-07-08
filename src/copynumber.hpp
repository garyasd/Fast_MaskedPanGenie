#ifndef COPYNUMBER_H
#define COPYNUMBER_H

#include <vector>

/** Represents probabilities of a kmer to have copy numbers 0,1 and 2. **/

class CopyNumber {
public:
	CopyNumber();
	/**
	@param cn_0 probability of copy number 0
	@param cn_1 probability of copy number 1
	@param cn_2 probability of copy number 2
	 **/
	CopyNumber(double cn_0, double cn_1, double cn_2);
	/** get probability of copy number cn **/
	double get_probability_of(int cn);
	bool operator==(const CopyNumber &other) const;
	bool operator!=(const CopyNumber &other) const;
private:
	std::vector<double> probabilities;
};
#endif // COPYNUMBER_H