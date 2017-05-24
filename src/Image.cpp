#define IMAGE RSSELI007::Image

#include "../headers/Image.h"

/*
Constructors
*/

// Default
IMAGE::Image() = default;

IMAGE::Image(std::string filename){
    if(load(filename)){
        
    }

}

// Copy
IMAGE::Image(const Image & img){

}

IMAGE & IMAGE::operator=(const Image &img){

}

// Move
IMAGE::Image(Image && img){

}

IMAGE & IMAGE::operator=(Image && img){

}

// Destructor
IMAGE::~Image(){
    delete [] & data;
}


/*
Overloads
*/

// Addition
IMAGE & IMAGE::operator+(const Image &img){

}

// Subtraction
IMAGE & IMAGE::operator-(const Image &img){

}

// Invert
IMAGE & IMAGE::operator!(){

}

// Mask
IMAGE & IMAGE::operator/(const Image &img){

}

// Int Threshold
IMAGE & IMAGE::operator*(int f){

}

// In Stream
std::istream &operator>>(std::istream is, const IMAGE img){

}

// Out Stream
std::ostream &operator<<(std::ostream os, IMAGE img){
    //for(const IMAGE::iterator it=img.begin(); it !=img.end()){

    //}
}


/*
Methods
*/

// read file
bool IMAGE::load(std::string filename){

}

// load file
bool IMAGE::save(std::string filename){
    // write file
	std::ofstream file("bin/output/"+filename+".pgm", std::ios::out | std::ios::binary);
	if (file.good()){
        file << "P5" << std::endl << this->width << " " << this->height << std::endl << "255" << std::endl << *this;
		file.close();
	}
}
