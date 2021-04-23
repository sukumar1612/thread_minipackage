# thread_minipackage
minipackage for college project

the project uses a thread to read one line of the text file
so for every line I used one thread
I used mutex lock to prevent race condition when updating the word count

takes in a text file and outputs the distinct words along with their count and shows other file statics.
only runs on linux terminal since it uses posix thread

to compile program type g++ project.cpp -lpthread

To run the program on linux terminal do ./a.out <filename>


