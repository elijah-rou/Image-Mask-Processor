#define IMAGE RSSELI007::Image

#include "../headers/Image.h"

/*
Constructors
*/

// Default
IMAGE::Image() = default;

IMAGE::Image(std::string filename){

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
std::ostream &operator<<(std::ostream, const IMAGE img){

}


/*
Methods
*/

// read file
bool IMAGE::read(std::string filename){

}

// load file
bool IMAGE::load(std::string filename){

}
