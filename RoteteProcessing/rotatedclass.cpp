#include "rotatedclass.h"

RotatedClass::RotatedClass()
{

}

void RotatedClass::rotatedImgProcessing()
{
    Mat before_rotation = imread("/home/karali/image/TestOCR/enes5.jpg");//loading image to a matrix
    namedWindow("BeforeRotation");//Declaring window to show the original image//
    imshow("BeforeRotation", before_rotation);//showing the image before rotation//
    namedWindow("AfterRotation");//declaring window to show rotated image//
//    int Rotation = 180;//initialization rotation angle//
//    createTrackbar("Rotation", "AfterRotation", &Rotation, 360);//creating trackbar//
    int Height = before_rotation.rows / 2;//getting middle point of rows//
    int Width = before_rotation.cols / 2;//getting middle point of height//
    int Rotation = 0;
    while (true) {

       Mat for_Rotation = getRotationMatrix2D(Point(Width, Height), (Rotation - 180), 1);//affine transformation matrix for 2D rotation//
       Mat for_Rotated;//declaring a matrix for rotated image
       warpAffine(before_rotation, for_Rotated, for_Rotation, before_rotation.size());//applying affine transformation//
       imshow("AfterRotation", for_Rotated);//show rotated image//
       Rotation +=10;
       if(Rotation ==190){
           break;
       }
       int termination = waitKey(30);//allow system 30 millisecond time to create the rottion effect//
       if (termination == 27){ //terminate if Esc button is pressed//
          break;
       }
    }

}
