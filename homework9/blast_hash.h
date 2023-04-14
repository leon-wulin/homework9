#ifndef BLAST_HASH
#undef BLAST_HASH
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>

class HashTable {
public:
    HashTable(std::string& sequence, int size, int kmer_length, float occupancy);

    void print_hash_table()const;

    void query_genome(const int m, const std::string& query_string);

    struct Entry {
        std::string kmer;
        std::vector<int> coordinates;        

        Entry():kmer("") {};
        Entry(const std::string& kmer, int coordinate)
            : kmer(kmer) {
            coordinates.push_back(coordinate);
        }
    };

private:
    std::vector<Entry> table;
    int size;
    int kmer_length;
    float occupancy;
    int entrys;
    int hash_times=0;
    int collision = 0;
    std::string genome_data;

    int hash_function(const std::string& kmer);
    void rehash();
};


//read DNA alphabe file to a string
std::string read_file(const std::string& filename);

#endif