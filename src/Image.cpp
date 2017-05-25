#define IMAGE RSSELI007::Image
#define UCHAR RSSELI007::uchar

#include "../headers/Image.h"
#include <iostream>

/*
Constructors
*/

// Default
IMAGE::Image(){
    width = height = 0;
}

IMAGE::Image(std::string filename){
    this->filename = filename;
    if(!load(filename)){
    }

}

// Copy
IMAGE::Image(const Image & img)
:   width(img.width),
    height(img.height),
    filename(img.filename){
        Image::iterator it(img.begin());
        UCHAR * buffer = new UCHAR[img.width*img.height];
        for(int i=0; i<this->width*this->height; ++i){
            buffer[i] = *it;
            ++it;
	    }
        this->data = std::unique_ptr<UCHAR[]>(buffer);
}

IMAGE & IMAGE::operator=(const Image & img){
    if(this != &img){
        this->width = img.width;
        this->height = img.height;
        this->filename = img.filename;
        Image::iterator it(img.begin());
        UCHAR * buffer = new UCHAR[img.width*img.height];
        for(int i=0; i<this->width*this->height; ++i){
            buffer[i] = *it;
            ++it;
	    }
        this->data = std::unique_ptr<UCHAR[]>(buffer);
    }
    return *this;
}

// Move
IMAGE::Image(Image && img)
:   width(img.width),
    height(img.height){
        this->filename = std::move(img.filename);
        this->data = std::move(img.data);
}

IMAGE & IMAGE::operator=(Image && img){
    if(this != &img){
        this->width = img.width;
        this->height = img.height;
        this->filename = std::move(img.filename);
        this->data = std::move(img.data);
    }
    return *this;
}

// Destructor
IMAGE::~Image(){
    data = nullptr;
}


/*
Overloads
*/

// Addition
IMAGE & IMAGE::operator+=(const Image & img){
    
}
IMAGE & IMAGE::operator+(const Image & img){

}

// Subtraction
IMAGE & IMAGE::operator-=(const Image & img){

}
IMAGE & IMAGE::operator-(const Image & img){

}

// Invert
IMAGE & IMAGE::operator!(){

}

// Mask
IMAGE & IMAGE::operator/=(const Image & img){

}
IMAGE & IMAGE::operator/(const Image & img){

}

// Int Threshold
IMAGE & IMAGE::operator*=(int f){

}
IMAGE & IMAGE::operator*(int f){

}

// In Byte Stream
std::istream & RSSELI007::operator>>(std::istream & is, IMAGE & img){
    UCHAR * buffer = new UCHAR[img.width*img.height];
    is.read((char *)buffer, img.width*img.height);
    img.data = std::unique_ptr<UCHAR[]>(buffer);
    return is;
}

// Out Byte Stream
std::ostream & RSSELI007::operator<<(std::ostream & os, const IMAGE & img){
    Image::iterator it = img.begin();
    while(it != img.end()){
        os << *it;
        ++it;
    }
    return os;
}


/*
Methods
*/

// read file
bool IMAGE::load(std::string filename){
    std::ifstream file("img/" + filename);
    if(file.good()){
        std::string line;
        // skip first line
        std::getline(file, line);
        // skip comments
        do{
            std::getline(file, line);
        }while(line[0] == '#');
        // obtain size
        {
            std::istringstream iss(line);
            std::string str;
            std::getline(iss, str, ' ');
            this->width = std::stoi(str);
            std::getline(iss, str, ' ');
            this->height = std::stoi(str);
        }
        std::getline(file, line);
        file >> *this;
        return true;
    }
    return false;
}

// save file
bool IMAGE::save(std::string filename){
    // write file
	std::ofstream file("bin/output/"+filename+".pgm", std::ios::out | std::ios::binary);
	if (file.good()){
        file << "P5" << std::endl << this->width << " " << this->height << std::endl << "255" << std::endl << *this;
		file.close();
        return true;
	}
    return false;
}
