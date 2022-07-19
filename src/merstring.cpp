#include <iostream>
#include "merstring.hpp"

using namespace std;

static const char valid_bases[5] ={'A','C','G','T','N'};

static bool is_valid(char c){
    for(char b : valid_bases){
        if(b==c) return true;
    }
    return false;
}

MerString::MerString(size_t k)
    :   k(k),
        start_position(0) {

    bases = (char *) malloc(k);
    for(int i = 0; i<k; i++){
        bases[i] = 'N';
    }
}

MerString::MerString(string sequence)
    :   k(sequence.size()),
        start_position(0) {
    
    bases = (char *) malloc(k);
    for(int i = 0; i<k; i++){
        char c = sequence[i];
        if(is_valid(c)) bases[i] = c;
        else throw runtime_error("Character" + to_string(c) + "not accepted as base.");
    }
}

size_t MerString::size(){
    return k;
}

string MerString::to_str(){
    string output;
    for(int i = start_position; i<k; i++){
        output.push_back(bases[i]);
    }
    for(int i = 0; i<start_position; i++){
        output.push_back(bases[i]);
    }
    return output;
}

char MerString::shift_left(char c){
    if(!is_valid(c)) throw runtime_error("Character" + to_string(c) + "not accepted as base.");

    char leftmost_char = bases[start_position];
    bases[start_position] = c;
    
    if(start_position<k-1) start_position++;
    else start_position=0;

    return leftmost_char;
}

string MerString::apply_mask_string(string mask){
    string output;
    int position = 0;

    for(int i = start_position; i<k; i++){
        if(mask[position]=='1'){
            output.push_back(bases[i]);
        }
        position++;
    }
    for(int i = 0; i<start_position; i++){
        if(mask[position]=='1'){
            output.push_back(bases[i]);
        }
        position++;
    }
    return output;
}
jellyfish::mer_dna MerString::apply_mask_sequence(string mask){

    jellyfish::mer_dna output("");
    int position = 0;
    int nr_shifts = 0;

    for(int i = start_position; i<k; i++){
        if(mask[position]=='1'){
            output.shift_left(bases[i]);
            nr_shifts++;
        }
        position++;
    }
    for(int i = 0; i<start_position; i++){
        if(mask[position]=='1'){
            output.shift_left(bases[i]);
            nr_shifts++;
        }
        position++;
    }

    //check if jellyfish uses same k-mer size
    if(jellyfish::mer_dna::k() != nr_shifts){
        throw runtime_error("Jellyfish k-mer size ("+to_string(jellyfish::mer_dna::k())+
        ") different to number of bases in given mask ("+to_string(nr_shifts)+")");
    }

    return output;
}

