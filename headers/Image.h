#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>


namespace RSSELI007{
    typedef unsigned char uchar;
    class Image{
        private:

            int width, height;

            std::string filename;

            std::unique_ptr<uchar[]> data;

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