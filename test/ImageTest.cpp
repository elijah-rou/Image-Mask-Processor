#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>
#include "../headers/catch.hpp"
#include "../headers/Image.h"

using namespace RSSELI007;
using namespace std;

Image image1("Lenna_standard.pgm");


TEST_CASE("Constructors"){

    SECTION("CONSTRUCT"){
        REQUIRE(image1.getWidth() == 512);
        REQUIRE(image1.getHeight() == 512);
        REQUIRE(image1.getFilename() == "Lenna_standard.pgm");
    }

    SECTION("COPY"){
        Image image2(image1);
        REQUIRE(image1.getWidth() == image2.getWidth());
        REQUIRE(image1.getHeight() == image2.getHeight());
        REQUIRE(image1.getFilename() == image2.getFilename());
        REQUIRE(*image1.begin() == *image2.begin());
        REQUIRE(*image1.last() == *image2.last());
        REQUIRE(&image1 != &image2); 
    }

    SECTION("COPY Assignment"){
        Image image2 = image1;
        REQUIRE(image1.getWidth() == image2.getWidth());
        REQUIRE(image1.getHeight() == image2.getHeight());
        REQUIRE(image1.getFilename() == image2.getFilename());
        REQUIRE(*image1.begin() == *image2.begin());
        REQUIRE(*image1.last() == *image2.last());
        REQUIRE(&image1 != &image2);
    }

    SECTION("COPY Iterator"){
        Image image2(image1);
        Image::iterator i1 = image1.begin();
        Image::iterator i2(i1);
        REQUIRE(*i1 == *i2);
        REQUIRE(&i1 != &i2);
    }

    SECTION("COPY Iterator Assignment"){
        Image image2(image1);
        Image::iterator i1 = image1.begin();
        Image::iterator i2 = i1;
        REQUIRE(*i1 == *i2);
        REQUIRE(&i1 != &i2);
    }

    SECTION("MOVE"){
        Image image1copy(image1);
        uchar c = *image1.begin();
        Image image2(std::move(image1copy));
        REQUIRE(image1copy.getFilename() == "");
        REQUIRE(image2.getFilename() == "Lenna_standard.pgm");
        REQUIRE(*image2.begin() == c);
        REQUIRE(&image1 != &image2); 
    }

     SECTION("MOVE Assignment"){
        Image image1copy(image1);
        uchar c = *image1.begin();
        Image image2 = std::move(image1copy);
        REQUIRE(image1copy.getFilename() == "");
        REQUIRE(image2.getFilename() == "Lenna_standard.pgm");
        REQUIRE(*image2.begin() == c);
        REQUIRE(&image1 != &image2); 
    }


}

TEST_CASE("Operators"){
    Image image2("Lenna_hat_mask.pgm");
    SECTION("ADDITION"){
        //Image result = image1 + image2;
    }

}

TEST_CASE("METHODS"){
    SECTION("Save"){
        image1.save("test");
        Image testImage("../bin/output/test.pgm");
        REQUIRE(image1.getWidth() == testImage.getWidth());
        REQUIRE(image1.getHeight() == testImage.getHeight());
        REQUIRE(*image1.begin() == *testImage.begin());
        REQUIRE(*image1.last() == *testImage.last());

    }
}
