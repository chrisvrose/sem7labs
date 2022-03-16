#include <gd.h>
#include <iostream>
#include <string>
#include <omp.h>

int main(int argc, char** argv)
{
    FILE* fp = nullptr;

    gdImagePtr img;

    char *iname = nullptr, *oname = nullptr;

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <ipfile> <opfile>\n";
        return 1;
    } else {
        // set args
        iname = argv[1], oname = argv[2];
    }

    uint red = 0, blue = 0, green = 0,color=0,mid=0;

    uint x, y, z,w,h;

    if (!(fp = fopen(iname, "r"))) {
        std::cout<<"Cannot open input\n";
        return 1;
    }

    img = gdImageCreateFromPng(fp);
    fclose(fp);fp=nullptr;
    w = gdImageSX(img);
    h = gdImageSY(img);
    auto t = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) private(x,y,color,red,green,blue)
    for(x=0;x<w;x++){
        for(y=0;y<h;y++){
            
            color = gdImageGetPixel(img,x,y);
            red = gdImageRed(img,color);
            green = gdImageGreen(img,color);
            blue = gdImageBlue(img,color);

            mid = (red+blue+green)/3;
            red = green = blue = mid;
            
            color = gdImageColorAllocate(img,red,green,blue);
            #pragma omp critical
            gdImageSetPixel(img,x,y,color);

        }
    }
    t = omp_get_wtime()-t;
    if(!(fp=fopen(oname,"w"))){std::cout<<"Could not open output file\n"; return 1;}
    gdImagePng(img,fp);
    fclose(fp);

    gdImageDestroy(img);
    std::cout<<"Time taken:"<<t<<"\n";
    return 0;
}
