#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>


namespace RSSELI007{
    typedef unsigned char uchar;

    struct Filter{
        std::size_t dimension;
        double ** matrix;

        Filter(std::string filename){
            std::ifstream file("filters/" + filename);
            if (file.good()){
                std::string line;
                std::getline(file, line);

                std::istringstream iss(line);
                std::string str;
                std::getline(iss, str, ' ');
                dimension = std::stoi(str);

                matrix = new double*[dimension];
                for(int i=0; i<dimension; ++i){
                   double * col = new double[dimension];
                    for(int j=0; j<dimension; ++j){
                        std::getline(iss, str, ' ');
                        col[j] = atof(str.c_str());
                    }
                    matrix[i] = col;
                }
            }
        }
        ~Filter(){
            for(unsigned int i=0; i<dimension; i++){
                delete matrix[i];
            }
            delete [] matrix;
        }

        void print(void){
            std::cout << "PRINTING G " << dimension << std::endl;
            for(int i=0; i<dimension; ++i){
                    for(int j=0; j<dimension; ++j){
                        std::cout << matrix[i][j] << " ";
                    }
                    std::cout << std::endl;
                }
        }
    };

    class Image{
        private:

            int width, height;

            std::string filename;

            std::unique_ptr<uchar[]> data;

            // method for convertiing data set into 2D from 1D
            uchar** to_2D();

        public:

            /*
            Constructors
            */

            // Default
            Image();
            Image(std::string fileName);

            // Copy
            Image(const Image & img);
            Image & operator=(const Image & img);

            // Move
            Image(Image && img);
            Image & operator=(Image && img);

            // Destructor
            ~Image();


            /*
            Overloads
            */

            // Addition
            Image & operator+=(const Image & img);
            Image operator+(const Image & img);

            // Subtraction
            Image & operator-=(const Image & img);
            Image operator-(const Image & img);

            // Invert
            Image operator!();

            // Mask
            Image & operator/=(const Image & img);
            Image operator/(const Image & img);

            // Int Threshold
            Image & operator*=(int f);
            Image operator*(int f);

            // Equality
            bool operator==(const Image & img);
            bool operator!=(const Image & img);

            // In Stream
            friend std::istream & operator>>(std::istream & is, Image & img);

            // Out Stream
            friend std::ostream & operator<<(std::ostream & os, const Image & img);

            // Filter
            Image & operator%=(const Filter & g);
            Image operator%(const Filter & g);


            /*
            Methods
            */

            bool load(std::string filename);

            bool save(std::string filename);

            int getWidth(void){ return this->width; }

            int getHeight(void){ return this->height; }

            std::string getFilename(void){ return this->filename; }

            /*
            Iterator
            */
            class iterator{
                private:

                    // pointer
                    uchar * ptr;

                public:

                    // constructor
                    iterator(uchar * p) : ptr(p) {}

                    iterator(uchar * p, int index) : ptr(&p[index]) {}

                    // copy constructor
                    iterator(const iterator & it) : ptr(it.ptr) {}
                    iterator & operator=(const iterator & it){
                        if(this != & it){
                            delete [] ptr;
                            this->ptr = it.ptr;
                            for(int i=0; i<sizeof(it.ptr); i++){
                                ptr[i] = it.ptr[i];
                            }
			            }   
			            return *this;
                    }

                    // overloads

                    // deref
                    uchar & operator*(){
                        return * ptr;
                    }

                    // Increment
                    iterator & operator++(){
                        ++ptr;
                        return *this;
                    }

                    iterator & operator++(int){
                        iterator * temp = new iterator(*this);
                        operator++();
                        return * temp;
                    }

                    // Decrement
                    iterator & operator--(){
                        --ptr;
                        return *this;
                    }

                    iterator & operator--(int){
                        iterator * temp = new iterator(*this);
                        operator--();
                        return * temp;
                    }

                    // equality

                    bool operator==(const iterator & it){
                        return ptr == it.ptr;
                    }

                    bool operator!=(const iterator & it){
                        return ptr != it.ptr;
                    }

            };

             //Iterator Methods

             iterator begin(void) const {
                 return iterator(this->data.get());
             }
             iterator end(void) const {
                 return iterator(this->data.get(), width*height);
             }
             // for testing
             iterator last(void) const {
                return iterator(data.get(), width*height-1);
            }

    };
}

#endif