HOMEWORK 9: MINIBLAST


NAME:  < Lin Wu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< YiZhou，w3cschool >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 hours >


HASH FUNCTION DESCRIPTION
The hash function implemented in this program is a simple polynomial rolling hash function. 
It works by assigning a numeric value to each character in the k-mer, and then it calculates the sum of each character's value multiplied 
by a prime number raised to the power of its position in the k-mer. The result is then taken modulo the hash table size to obtain the index 
where the k-mer should be stored in the hash table. 
This method provides a decent distribution of k-mers across the hash table while maintaining a relatively low collision rate.






HASH TABLE IMPLEMENTATION
The hash table is implemented using open addressing with linear probing.
 Open addressing stores all elements directly within the hash table array, as opposed to separate chaining, 
which uses linked lists to store elements. In case of a collision, linear probing searches for the next available slot in the array
 by incrementing the index by 1 until an empty slot is found. This method is simple to implement and generally provides good performance,
 especially when the load factor of the hash table is kept below a certain threshold.






ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found	
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
The hash table data structure requires O(L) memory since it needs to store all the k-mers in the genome sequence.


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

    Hash table insert operation:

    Average-case: O(1)
    Worst-case: O(L)

    Hash table find operation:

    Average-case: O(1)
    Worst-case: O(L)

    Hash table resize operation:

    O(L)


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


