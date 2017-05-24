#include <iostream>
#include <string>
#include <vector>

#include "../headers/Image.h"

using namespace std;

void clear(void) { system("clear") ;}

int main(int argc, char* argv[]){
	clear();
    // can handle multiple commands for ease of use
    for (int i = 2; i < argc; i++){

        // command
        string arg = argv[i];

        // add images
        if (arg == "-a"){
            string file_i = argv[i + 1];
            string file_j = argv[i + 2];
            string out_file = argv[i + 3];
        }

        // subtract images
        else if (arg == "-s"){
            string file_i = argv[i + 1];
            string file_j = argv[i + 2];
            string out_file = argv[i + 3];
        }

        // invert image
        else if (arg == "-i"){
            string file = argv[i + 1];
            string out_file = argv[i + 2];
        }

        // mask images
        else if (arg == "-l"){
            string file_i = argv[i + 1];
            string file_j = argv[i + 2];
            string out_file = argv[i + 3];
        }

        // int threshold on image
        else if (arg == "-t"){
            string file = argv[i + 1];
            int threshold = atoi(argv[i + 2]);
            string out_file = argv[i + 3];
        }

        // filter image
        else if (arg == "-f"){
            
        }
    }
}