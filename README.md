# Word-Count-with-MapReduce
Contain 4 functions:
1. Input Reader: 
   Read in a text file and divide the file into one-word-segments.
2. Map:
   Transfer each word into a key-pair. Key is the word and value = 1. return the key-pair.
3. Reduce:
   Get the key-pair from Map function. Produce a single key-pair, where the key are still the words and the value are the sums of each word.
4. Output:
   Get the key-pair from Reduce function and print the word counts.
