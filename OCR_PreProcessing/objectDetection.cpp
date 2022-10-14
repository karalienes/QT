//#include <iostream>
//#include "opencv2/text.hpp"
//#include <opencv2/opencv.hpp>
//#include <tesseract/baseapi.h>
////#include <tesseract/strngs.h>

//using namespace std;
//using namespace cv;
//using namespace cv::text;

//bool isRepetitive(const string& s){
//    int count = 0;

//    for (int i=0; i<(int)s.size(); i++){
//        if ((s[i] == 'i') ||
//                (s[i] == 'l') ||
//                (s[i] == 'I'))
//            count++;
//    }
//    if (count > ((int)s.size()+1)/2){
//        return true;
//    }
//    return false;
//}

//void er_draw(vector<Mat> &channels, vector<vector<ERStat> > &regions, vector<Vec2i> group, Mat& segmentation){

//    for (int r=0; r<(int)group.size(); r++){
//        ERStat er = regions[group[r][0]][group[r][1]];
//        if (er.parent != NULL) { // deprecate the root region
//            int newMaskVal = 255;
//            int flags = 4 + (newMaskVal << 8) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;
//            floodFill(channels[group[r][0]],segmentation,Point(er.pixel%channels[group[r][0]].cols,er.pixel/channels[group[r][0]].cols),
//                      Scalar(255),0,Scalar(er.level),Scalar(0),flags);
//        }
//    }
//}

//std::vector<Mat> extractTableFromImage(Mat src){

//    // resizing for practical reasons
//    Mat rsz;
//    Size size(800, 900);
//    resize(src, rsz, size);

//    // Transform source image to gray if it is not and show grayscale image
//    Mat gray;
//    if (rsz.channels() == 3){
//        cvtColor(rsz, gray, COLOR_BGR2GRAY);
//    } else {
//        gray = rsz;
//    }

//    // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
//    Mat bw;
//    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);

//    // Create the images that will use to extract the horizontal and vertical lines
//    Mat horizontal = bw.clone();
//    Mat vertical = bw.clone();

//    int scale = 20; // change this variable in order to increase/decrease the amount of lines to be detected

//    // Specify size on horizontal axis
//    int horizontalsize = horizontal.cols / scale;
//    // Create structure element for extracting horizontal lines through morphology operations
//    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
//    // Apply morphology operations, erosion removes white noises, but it also shrinks our object
//    //So we dilate it, since noise is gone, they won't come back, but our object area increases
//    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
//    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));

//    // Specify size on vertical axis
//    int verticalsize = vertical.rows / scale;
//    // Create structure element for extracting vertical lines through morphology operations
//    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size( 1,verticalsize));
//    // Apply morphology operations
//    erode(vertical, vertical, verticalStructure, Point(-1, -1));
//    dilate(vertical, vertical, verticalStructure, Point(-1, -1));

//    // create a mask which includes the tables
//    Mat mask = horizontal + vertical;

//    // find the joints between the lines of the tables, we will use this information in order
//    // to descriminate tables from pictures
//    Mat joints;
//    bitwise_and(horizontal, vertical, joints);

//    // Find external contours from the mask, which most probably will belong to tables or to images
//    vector<Vec4i> hierarchy;
//    std::vector<std::vector<cv::Point> > contours;
//    cv::findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

//    vector<vector<Point> > contours_poly( contours.size() );
//    vector<Rect> boundRect( contours.size() );
//    vector<Mat> rois;

//    for (size_t i = 0; i < contours.size(); i++){

//        // find the area of each contour
//        double area = contourArea(contours[i]);

//        // filter individual lines of blobs that might exist and they do not represent a table
//        if(area < 100) // value is randomly chosen, you will need to find that by yourself with trial and error procedure
//            continue;

//        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
//        boundRect[i] = boundingRect( Mat(contours_poly[i]) );

//        // find the number of joints that each table has
//        Mat roi = joints(boundRect[i]);

//        vector<vector<Point> > joints_contours;
//        findContours(roi, joints_contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

//        // if the number is not more than 5 then most likely it not a table
//        if(joints_contours.size() <= 4)
//            continue;

//        rois.push_back(rsz(boundRect[i]).clone());

//        //drawContours( rsz, contours, i, Scalar(0, 0, 255), CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
//        rectangle( rsz, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 1, 8, 0 );
//    }

//    return rois;
//}

////Label pre processing
//Mat labelPreprocessing(Mat image){
//    Mat grey;

//    cvtColor(image, grey, COLOR_BGR2GRAY);
//    cv::threshold(grey, grey, 128, 255, THRESH_BINARY | THRESH_OTSU);
//    // Apply Histogram Equalization
//    equalizeHist( grey, grey );

//    cv::imshow("enhanced label image", grey);

//    return grey;
//}


//void endToEndSceneTextDetectionAndRecognition(Mat image){

//    /*Text Detection*/

//    Mat grey;

//    grey = labelPreprocessing(image);

//    // Extract channels to be processed individually
//    vector<Mat> channels,channels2;

//    if (grey.channels() == 3){
//        cvtColor(grey, grey, COLOR_BGR2GRAY);
//    }

//    // Notice here we are only using grey channel
//    channels.push_back(grey);
//    channels.push_back(255-grey);

//    double t_d = (double)getTickCount();
//    // Create ERFilter objects with the 1st and 2nd stage default classifiers
//    Ptr<ERFilter> er_filter1 = createERFilterNM1(loadClassifierNM1("trained_classifierNM1.xml"),8,0.00005f,0.23f,0.2f,true,0.1f);
//    Ptr<ERFilter> er_filter2 = createERFilterNM2(loadClassifierNM2("trained_classifierNM2.xml"),0.5);

//    vector<vector<ERStat> > regions(channels.size());
//    // Apply the default cascade classifier to each independent channel (could be done in parallel)
//    for (int c=0; c<(int)channels.size(); c++)
//    {
//        er_filter1->run(channels[c], regions[c]);
//        er_filter2->run(channels[c], regions[c]);
//    }
//    cout << "TIME_REGION_DETECTION = " << ((double)getTickCount() - t_d)*1000/getTickFrequency() << endl;

//    Mat out_img_decomposition= Mat::zeros(image.rows+2, image.cols+2, CV_8UC1);
//    vector<Vec2i> tmp_group;
//    for (int i=0; i<(int)regions.size(); i++)
//    {
//        for (int j=0; j<(int)regions[i].size();j++)
//        {
//            tmp_group.push_back(Vec2i(i,j));
//        }
//        Mat tmp= Mat::zeros(image.rows+2, image.cols+2, CV_8UC1);
//        er_draw(channels, regions, tmp_group, tmp);
//        if (i > 0)
//            tmp = tmp / 2;
//        out_img_decomposition = out_img_decomposition | tmp;
//        tmp_group.clear();
//    }
//    imshow( "out_img_decomposition", out_img_decomposition);

//    double t_g = (double)getTickCount();
//    // Detect character groups
//    vector< vector<Vec2i> > nm_region_groups;
//    vector<Rect> nm_boxes;
//    erGrouping(image, channels, regions, nm_region_groups, nm_boxes,ERGROUPING_ORIENTATION_HORIZ);
//    cout << "TIME_GROUPING = " << ((double)getTickCount() - t_g)*1000/getTickFrequency() << endl;

//    /*Text Recognition (OCR)*/

//    double t_r = (double)getTickCount();
//    Ptr<OCRTesseract> ocr = OCRTesseract::create(NULL,NULL,"0123456789",OEM_CUBE_ONLY,tesseract::PSM_AUTO);
//    cout << "TIME_OCR_INITIALIZATION = " << ((double)getTickCount() - t_r)*1000/getTickFrequency() << endl;
//    string output;

//    Mat out_img;
//    Mat out_img_detection;
//    Mat out_img_segmentation = Mat::zeros(image.rows+2, image.cols+2, CV_8UC1);
//    image.copyTo(out_img);
//    image.copyTo(out_img_detection);
//    float scale_img  = 600.f/image.rows;
//    float scale_font = (float)(2-scale_img)/1.4f;
//    vector<string> words_detection;

//    t_r = (double)getTickCount();

//    for (int i=0; i<(int)nm_boxes.size(); i++){

//        rectangle(out_img_detection, nm_boxes[i].tl(), nm_boxes[i].br(), Scalar(0,255,255), 3);
//        imshow( "out_img_detection", out_img_detection);

//        Mat group_img = Mat::zeros(image.rows+2, image.cols+2, CV_8UC1);
//        er_draw(channels, regions, nm_region_groups[i], group_img);
//        Mat group_segmentation;
//        group_img.copyTo(group_segmentation);
//        //image(nm_boxes[i]).copyTo(group_img);
//        group_img(nm_boxes[i]).copyTo(group_img);
//        copyMakeBorder(group_img,group_img,15,15,15,15,BORDER_CONSTANT,Scalar(0));

//        vector<Rect>   boxes;
//        vector<string> words;
//        vector<float>  confidences;
//        ocr->run(group_img, output, &boxes, &words, &confidences, OCR_LEVEL_TEXTLINE);

//        output.erase(remove(output.begin(), output.end(), '\n'), output.end());
//        cout << "OCR output = \"" << output << endl;

//    }
//}

//int main(int argc, const char * argv[]){


//    return 0;
//}
