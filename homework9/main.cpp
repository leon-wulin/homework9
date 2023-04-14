#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "blast_hash.h"

int main() {
    int size = 100; // Set default size to 100
    float occupancy = 0.50; // Set default occupancy to 0.5
    int kmer_length = 10; // Set default kmer length to 10
    std::string command;
    std::string dna_sequence;
    bool hash_table_created = false;    
    HashTable* hash_table = nullptr;
    



    
    while (true) {
        //std::cout << "Enter command:" << std::endl;
        std::cin >> command;

        if (hash_table_created) {
            if (command == "table" || command == "occupancy" || command == "kmer") {
                std::cout << "Hash table already created. Cannot modify parameters." << std::endl;
                continue;
            }
        }

        if (command == "genome") {
            std::string filename;
            std::cin >> filename;
            dna_sequence = read_file(filename);
        }
        else if (command == "table_size") {
            std::cin >> size; 

        }
        else if (command == "occupancy") {
            std::cin >> occupancy; 
        }
        else if (command == "kmer") {
            std::cin >> kmer_length; 
        }
        else if (command == "query") {
            if (!hash_table_created) {       
                //std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

                hash_table = new HashTable(dna_sequence,size,kmer_length,occupancy);  

                //std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now(); 
                //std::chrono::duration<double, std::milli> time_span = end_time - start_time; 
                //double duration = time_span.count(); 
                

                //hash_table->print_hash_table(); 
                hash_table_created = true; 
                //std::cout << "program running time£º " << duration << " ms" << std::endl;
            }
            
            int m;
            std::string query_string;
            std::cin >> m >> query_string;
            hash_table->query_genome(m, query_string);
            
        }
        else if (command == "quit") {
            break;
        }
        else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
    
    delete hash_table;
    
    return 0;
    
}
