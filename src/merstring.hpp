#ifndef MERSTRING_HPP
#define MERSTRING_HPP

#include <jellyfish/mer_dna.hpp>

/** Represents a kmers.
 *  In contrast to jellyfish::mer_dna "k" can be different for each object of MerString. **/

class MerString {
public:
    MerString(std::string sequence);

    MerString(size_t k);

    /** return size of k-mer**/
    size_t size();

    /** shift k-mer by one base. Base on the furthest left gets returned. 
     * New base will be added on the right side **/
    char shift_left(char c);

    /** return k-mer as string **/
    std::string to_str();

    /** return masked string **/
    std::string apply_mask_string(std::string mask);

    /** return masked dna_mer sequence **/
    jellyfish::mer_dna apply_mask_sequence(std::string mask);

private:
    char* bases;
    unsigned short start_position;
    size_t k;
};



#endif // MERSTRING_HPP
