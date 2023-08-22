//pass the data to math function(calculate the index) (hash function) -> and get the index(hash value) -> hash table
//may have more than one data that shares same index
//hash value -> index, the whole process is call hashing
//good for search, insertion, deletion
//not all data appear at the same time, expanding hash table, create a hash table smaller than number of keys
//collision could occur -> instead of override, find the new index for data
//hash table has m slots {0,...m-1}
//possible keys {k0,k1, ..... , kn-1} size of |N|
// m < N
//good hash function -> fast to compute and avoid the number of collision(giving same hash value for some data)
//h(k) = k mod m -> gives the hash value of 0 to m-1
//m should not be power of 10
//why? -> ex) if m = 100 = 10^2, always uses the last two digit of input value -> will always get collision
//m should not be power of 2
//ex) if m = 8 = 2^3, always uses the last three bits of the input value 
//always uses the prime number
//good values should not too close to exact powers of 2
//string keys -> key[0] + 27*key[1] + 27^2 * key[2] -> not that good
//instead take all letters, 37^(L-1-i) * key[i] -> more computation will make the program slow
//seperate chaining -> using linked list for data with same index -> always put the new data at the first of the linked list
//-> much faster, just like adjacent list
//-> searching insertion, deletion is very easy, but memory aloocation and deallocation could slow down
//three method for resolving collisions -> open addressing, 1. linear probing, 2. quadratic probing, 3, 
//1. linear probing, if the index already has been occupied, move downward by 1 until you find the empty index
// -> it will create a big cluster which will make more collision -> primary clustering
//2. Quadratic probing -> move down by one location at the first collision, for the second collision, go down by 4 loaction
//for ith collision, go down by i^2 location -> will create many smaller collision
//there is no case when even quadratic probing cannot give you empty slot -> if the table size is prime and at least half empty 
//if the empty slot is less than half of the table, double the size of the table, 
//and move the item into new table(recompute the hash value)
//3. different jump for different data -> double hash
//hash(k) = k mod m,  hash2(k) = R - (k mod R) 
//--> 1. never evaluate to zero, 2. relatively prime(common factor is only 1) to the table size m, R is related to m
//R -> prime number smaller than m
//Searching element in hash table -> stop when find the element or empty cell
//Deletion -> dont delete the element, just remark the element with the label 'DELETED' -> Lazy Deletion
//Insertion to the cell marked as 'DELETED' and change the label back to 'ACTIVE'
//Load factor -> percentage of boxes that are occupied -> if load factor is big, create a new hash table with bigger size(rehashing)
//Load factor is greater than 1/2 => need to rehashing
//