#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <memory>

typedef unsigned char uchar;

namespace RSSELI007{
    class Image{

        private:

        int width, height;

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
            Image & operator+(const Image & img);

            // Subtraction
            Image & operator-(const Image & img);

            // Invert
            Image & operator!();

            // Mask
            Image & operator/(const Image & img);

            // Int Threshold
            Image & operator*(int f);

            // In Stream
            friend std::istream & operator>>(std::istream is, const Image img);

            // Out Stream
            friend std::ostream & operator<<(std::ostream, const Image img);


            /*
            Methods
            */

            bool load(std::string filename);

            bool save(std::string filename);

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

            };

             //Iterator Methods

             iterator begin(void){
                 return iterator(data.get());
             }
             iterator end(void){
                 return iterator(data.get(), width*height);
             }

    };
}

#endif