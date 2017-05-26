#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>
#include "../headers/catch.hpp"
#include "../headers/Image.h"

using namespace RSSELI007;
using namespace std;

Image image1("Lenna_standard.pgm");


TEST_CASE("Constructors"){

    SECTION("CONSTRUCT and LOAD"){
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
    // normalise the mask
    SECTION("EQUALITY and THRESHOLD"){
        image2 *= 0; // normalise
        Image test("Lenna_hat_mask.pgm");
        test *= 0; // normalise
        REQUIRE(image2 == test);
        REQUIRE(image2 != image1);
    }
    SECTION("ADDITION, SUBTRACTION & INVERSION"){
        image2 *= 0; // normalise
        Image imgAdd = !(image1 + image2)*0;
        Image imgSub = !((!image1 - !image2)*0);
        REQUIRE(imgAdd == imgSub);
    }
    SECTION("MASKING"){
        image2 *= 0; //normalise
        Image imgMask = image1/image2;
        imgMask *= 0; //normalise
        REQUIRE(imgMask == image2);
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
