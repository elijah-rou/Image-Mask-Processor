#define IMAGE RSSELI007::Image
#define FILTER RSSELI007::Filter

#include <iostream>
#include <string>
#include <vector>

#include "../headers/Image.h"

using namespace std;

void clear(void) { system("clear") ;}

int main(int argc, char* argv[]){
	clear();
    // can handle multiple commands for ease of use
    for (int i = 1; i < argc; i++){

        // command
        string arg = argv[i];

        // add images
        if (arg == "-a"){
            IMAGE file_i = IMAGE::Image(argv[i + 1]);
            IMAGE file_j = IMAGE::Image(argv[i + 2]);
            IMAGE result = file_i+file_j;
            result.save(argv[i + 3]);
        }

        // subtract images
        else if (arg == "-s"){
            IMAGE file_i = IMAGE::Image(argv[i + 1]);
            IMAGE file_j = IMAGE::Image(argv[i + 2]);
            IMAGE result = file_i-file_j;
            result.save(argv[i + 3]);
        }

        // invert image
        else if (arg == "-i"){
            IMAGE file_i = IMAGE::Image(argv[i + 1]);
            IMAGE result = !file_i;
            result.save(argv[i + 2]);
        }

        // mask images
        else if (arg == "-l"){
            IMAGE file_i = IMAGE::Image(argv[i + 1]);
            IMAGE file_j = IMAGE::Image(argv[i + 2]);
            IMAGE result = file_i/file_j;
            result.save(argv[i + 3]);
        }

        // int threshold on image
        else if (arg == "-t"){
            IMAGE file_i = IMAGE::Image(argv[i + 1]);
            int f = stoi(argv[i + 2]);
            IMAGE result = file_i*f;
            result.save(argv[i + 3]);
        }

        // filter image
        else if (arg == "-f"){
            IMAGE file_i = IMAGE::Image(argv[i + 1]);
            FILTER g(argv[i + 2]);
            g.print();
            //IMAGE result = file_i%g;
            //result.save(argv[i + 3])
        }
    }
}