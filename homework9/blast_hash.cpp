#include"blast_hash.h"
#include <cassert>
HashTable::HashTable(std::string& sequence, int init_size, int kmer_length, float occupancy)
    : genome_data(sequence), size(init_size), kmer_length(kmer_length), occupancy(occupancy), entrys(0) {
    table.resize(size);
    
    for (int i = 0; i < sequence.size() - kmer_length + 1; i++) {
        if (static_cast<float>(entrys) / size >= occupancy) {
            size *= 2;
            rehash();
        }
        std::string kmer = sequence.substr(i, kmer_length);
        int index = hash_function(kmer); 
        bool is_c = false;
        while (!table[index].kmer.empty()) {
            if (table[index].kmer == kmer) {
                table[index].coordinates.push_back(i);
                break;
            }
            index = (index + 1) % size;
            is_c = true;
        }

        if (table[index].kmer.empty()) {
            table[index].kmer = kmer;
            table[index].coordinates.push_back(i);
            entrys++;
            if (is_c) {
                collision++;
            }
        }
    }
}

int HashTable::hash_function(const std::string& kmer) {
    const unsigned int seed = 131; 
    unsigned int hash_value = 0;

    for (char nucleotide : kmer) {
        int value;
        switch (nucleotide) {
        case 'A': value = 2; break;
        case 'G': value = 3; break;
        case 'C': value = 5; break;
        case 'T': value = 7; break;
        default:
            std::cout << "Invalid kmer: " << kmer << std::endl;
            std::cout << "Invalid nucleotide: " << nucleotide << std::endl;
            throw std::invalid_argument("Invalid nucleotide in k-mer");
        }

        
        hash_value = (hash_value * seed) ^ value;
    }
    hash_times++; 
    return hash_value % size;
} 

void HashTable::rehash() {
    std::vector<Entry> old_table = table;
    table.clear();
    table.resize(size);
    entrys = 0;

    for (const Entry& entry : old_table) { 
        if (!entry.kmer.empty()) {
            for (int coord : entry.coordinates) {
                std::string kmer = entry.kmer;
                int index = hash_function(kmer);
                
                bool is_c = false;
                while (!table[index].kmer.empty()) {
                    if (table[index].kmer == kmer) {
                        table[index].coordinates.push_back(coord);
                        break;
                    }
                    index = (index + 1) % size;
                    is_c = true;
                }

                if (table[index].kmer.empty()) {
                    table[index].kmer = kmer;
                    table[index].coordinates.push_back(coord);
                    entrys++;
                    if (is_c) {
                        collision++;
                    }
                }
            }
        }
    }
};

void HashTable::print_hash_table() const{
    int data = 0;
    for (int i = 0; i < size; ++i) { 
        if (!table[i].kmer.empty()) {
            std::cout << i << ": " << table[i].kmer << ": ";
            for (int coord : table[i].coordinates) {
                std::cout << coord << " ";
            }
            std::cout << std::endl;
            data++;
        }
    }
    std::cout<<"hash table size:" << data << "/" << size << std::endl;
    std::cout << "collision proportion:" << collision << "/" << hash_times << std::endl;
}

bool find(const std::vector<int>& vec, int value) {
    std::vector<int>::const_iterator it = std::find(vec.begin(), vec.end(), value);
    return it != vec.end();
}

void HashTable::query_genome(const int m, const std::string& query_string) {
    int query_length = query_string.size();
    int num_substrings = query_length - kmer_length + 1;
    std::vector<int> all_positions;

    /*
    for (int i = 0; i < num_substrings; i++) {
        std::string kmer = query_string.substr(i, kmer_length);
        int index = hash_function(kmer);        
            while (!table[index].kmer.empty()) {
                if (table[index].kmer == kmer) {
                    for (int pos = 0; pos < table[index].coordinates.size();pos++) {
                        try {
                            // std:cout<<
                            if (genome_data.substr(table[index].coordinates[pos] - i, kmer_length) == kmer) {

                                all_positions.push_back(table[index].coordinates[pos] - i);
                            }
                        }
                        catch (std::exception& e)
                        {
                            std::cout << "error" << std::endl;
                        }
                    }
                    break;
                }
                index = (index + 1) % size;
            }
            }
            */
    
    int index = hash_function(query_string.substr(0, kmer_length)); 

    bool found = true;

    while (table[index].kmer != query_string.substr(0, kmer_length) ){
        if (table[index].kmer == "") { 
            found = false;
            break;
        }
        index++; 
    }

    if(found){
        for (int i : table[index].coordinates) {
            all_positions.push_back(i); 
        }
    }

    std::vector<std::pair<int, int>> valid_positions;

    for (const int pos : all_positions) {
        bool valid_kmer = false;
        for (int k = 0; k < num_substrings; k++) {
            std::string kmer = query_string.substr(k, kmer_length);
            if (genome_data.substr(pos + k, kmer_length) == kmer) {
                valid_kmer = true;
                break;
            }
        }
        if (!valid_kmer) {
            continue;
        }

        int error_count = 0;
        for (int i = 0; i < query_length; i++) {
            if (genome_data[pos + i] != query_string[i]) {
                error_count++;
                if (error_count > m) {
                    break;
                }
            }
        }
        if (error_count <= m) {
            std::vector<std::pair<int, int>>::iterator it = std::find_if(valid_positions.begin(), valid_positions.end(), 
                [&pos](const std::pair<int, int>& pair) { return pair.first == pos; });

            if (it == valid_positions.end()) {
                valid_positions.push_back(std::make_pair(pos, error_count));
            }
        }
    }

    std::cout << "Query: " << query_string << std::endl;

    if (valid_positions.empty()) {
        std::cout << "No Match" << std::endl;
    }
    else {
        for (const std::pair<int, int>& pos_error : valid_positions) {
            int pos = pos_error.first;
            int errors = pos_error.second;
            std::string matched_sequence = genome_data.substr(pos, query_length);

            std::cout << pos << " " << errors << " " << matched_sequence << std::endl;
        }
    }
}

std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, dna_sequence;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return "";
    }

    while (std::getline(file, line)) {
        for (char c : line) {
            if (std::isalpha(c)) {
                dna_sequence += c;
            }
        }
    }

    file.close();
    return dna_sequence;
}

