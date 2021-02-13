#include <iostream>
#include <fstream>
using namespace std;

void foo(int argc, char *argv[]) {
    int size = 0;
    if (argc > 1) {
        const char *fname = argv[1];
        ofstream of;
        of.open(fname, ios::binary);
        //open file for writing, write bytes 27, 28, ..., 126
        for (int i = 0; i < 100; ++i)
            of.put(char(i+27));
        of.close();

        ifstream file;
        //open the file for reading
        file.open(fname, ios::in | ios::binary);
        //we might have permission to write, but not to read???
        if (file) {
            //set the pointer at the end of the file
            file.seekg(0, ios::end);
            size = file.tellg();
            if (size < 0) {
                //why not found? we did successfuly open the file
                //it was reading the position that failed
                cerr << fname << " not found";
                //from a void function? with no error code? w/out throwing an exception?
                //weird af
                return;
            }
            //nearly impossible that the size != 100
            cout << fname << " size = " << size;
        }
        //then why even bother checking, if not handling failure...

    } else {
        cout << "file name not specified";
    }
}

int main(int argc, char *argv[]) {
    foo(argc, argv);
}

