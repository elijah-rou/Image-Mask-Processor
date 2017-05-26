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
        exit(1);
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
    if(this->width == img.width && this->height == img.height){
        Image::iterator lhs = this->begin();
        for(uchar c : img){
            if((*lhs + c) > 255){
                *lhs = 255;
            }
            else{
                *lhs += c;
            }
            ++lhs;
        }
    }
    return *this;

}
IMAGE IMAGE::operator+(const Image & img){
    Image result(*this);
    result +=img;
    return result;

}

// Subtraction
IMAGE & IMAGE::operator-=(const Image & img){
    if(this->width == img.width && this->height == img.height){
        Image::iterator lhs = this->begin();
        for(uchar c : img){
            if((*lhs - c) < 0){
                *lhs = 0;
            }
            else{
                *lhs -= c;
            }
            ++lhs;
        }
    }
    return *this;

}
IMAGE IMAGE::operator-(const Image & img){
    Image result(*this);
    result -=img;
    return result;

}

// Invert
IMAGE IMAGE::operator!(){
    Image result(*this);
    /*
    for(uchar c : result){
        c = (255 - c);
    }
    */
    Image::iterator it = result.begin();
    while(it != result.end()){
        *it = (255 - *it);
        ++it;
    }
    return result;
}

// Mask
IMAGE & IMAGE::operator/=(const Image & img){
    if(this->width == img.width && this->height == img.height){
        Image::iterator lhs = this->begin();
        for(uchar c : img){
            if(c == 0){
                *lhs = 0;
            }
            ++lhs;
        }
    }
    return *this;

}
IMAGE IMAGE::operator/(const Image & img){
    Image result(*this);
    result /= img;
    return result;

}

// Int Threshold
IMAGE & IMAGE::operator*=(int f){
    Image::iterator it = this->begin();
    while(it != this->end()){
        *it = *it > f ? 255 : 0;
        ++it;
    }
    return *this;
}
IMAGE IMAGE::operator*(int f){
    Image result(*this);
    result *= f;
    return result;
}

// Equality
bool IMAGE::operator==(const IMAGE & img){
    if(this->width == img.width && this->height == img.height){
        Image::iterator lhs = this->begin();
        for(uchar c : img){
            if(*lhs != c){
                return false;
            }
            ++lhs;
        }
        return true;
    }
    return false;
}
bool IMAGE::operator!=(const IMAGE & img){
    if(this->width == img.width && this->height == img.height){
        Image::iterator lhs = this->begin();
        for(uchar c : img){
            if(*lhs != c){
                return true;
            }
            ++lhs;
        }
        return false;
    }
    return true;
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

// Filter
IMAGE & IMAGE::operator%=(const RSSELI007::Filter & g){
    UCHAR ** buffer = to_2D();
    for (int i = 0; i < this->width; ++i){
        for (int j = 0; j < this->height; ++j){
            UCHAR * array = new UCHAR[g.dimension];
        }
    }
    delete [] buffer;
    return *this;
}
IMAGE IMAGE::operator%(const RSSELI007::Filter & g){
    Image result(*this);
    result %= g;
    return result;
}

/*
Methods
*/

// method for convertiing data set into 2D from 1D
UCHAR** IMAGE::to_2D(void){
    UCHAR ** buffer = new UCHAR*[this->width];
    iterator it = this->begin();
    for (int i = 0; i < this->width; ++i){
        UCHAR *col = new UCHAR[this->height];
        for (int j = 0; j < this->height; ++j){
            col[j] = *it;
            ++it;
        }
        buffer[i] = col;
    }
    return buffer;
}


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
