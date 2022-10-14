#include "ocrprocessing.h"

OCRProcessing::OCRProcessing()
{
    rotatedImgProcessing();
}

void OCRProcessing::rotatedImgProcessing()
{
    Mat before_rotation = imread("/home/karali/image/SEECAM/2022-09-30 11:20:11.png");//loading image to a matrix
//    int Rotation = 180;//initialization rotation angle//
//    createTrackbar("Rotation", "AfterRotation", &Rotation, 360);//creating trackbar//
    int Height = (before_rotation.rows-1) / 2;//getting middle point of rows//
    int Width = (before_rotation.cols-1) / 2;//getting middle point of height//
    double Rotation = 0;
    int holder =0;
    while (holder<4) {
       Mat for_Rotated;
        if(holder==0){
           for_Rotated=before_rotation;
       }
       else{
            Rotation +=90;
            Mat for_Rotation = getRotationMatrix2D(Point(Width, Height), (Rotation), 1);//affine transformation matrix for 2D rotation//
            warpAffine(before_rotation, for_Rotated, for_Rotation, before_rotation.size());//applying affine transformation//
        }

       dataImgProcessing(holder,for_Rotated);

       holder++;
       int termination = waitKey(1);//allow system 30 millisecond time to create the rottion effect//
//       if (termination == 27){ //terminate if Esc button is pressed//
//          break;
//       }

    }
}
void OCRProcessing::dataImgProcessing(int i, Mat img)
{
    if(i==0){
        rotateddata[i].angle = 0;
    }
    else{
        rotateddata[i].angle = rotateddata[i-1].angle +90;
    }
    qDebug()<<img.cols <<"Width";
    qDebug()<<img.rows <<"Height";

    decodeobj = new Decode();
    float confThreshold = 0.6;
    float nmsThreshold = 0.4;
    int inpWidth = 800;
    int inpHeight = 800;
    String model = "/home/karali/image/Text_Detection/frozen_east_text_detection.pb";
    String detect = "line";

    CV_Assert(!model.empty());

    // Load network.
    Net net = readNetFromTensorflow(model);

    // get network output
    vector<Mat> outs;
    vector<String> outNames(2);
    outNames[0] = "feature_fusion/Conv_7/Sigmoid";
    outNames[1] = "feature_fusion/concat_3";

    static const std::string kWinName = "EAST: An Efficient and Accurate Scene Text Detector";
    Mat frame, blob;
    frame = img;

    blobFromImage(frame, blob, 1.0, Size(inpWidth, inpHeight), Scalar(123.68, 116.78, 103.94), true, false);
    net.setInput(blob);
    net.forward(outs, outNames);
    Mat scores = outs[0];
    Mat geometry = outs[1];

    vector<RotatedRect> boxes;
    vector<float> confidences;
    vector<vector<RotatedRect>> line_boxes;
    vector<vector<float>> line_confidences;
    decodeobj->decode(scores, geometry, confThreshold, boxes, line_boxes, confidences, line_confidences);

    int prev_size = 0;
    vector<int> indices;
    vector<Triplets> lines;
    //applying non maximum suppression
    for (int k = 0; k < line_boxes.size(); ++k)
    {
        int curr_size = line_boxes[k].size();
        if (curr_size == prev_size)
            continue;
        NMSBoxes(line_boxes[k], line_confidences[k], confThreshold, nmsThreshold, indices);
        lines.push_back({line_boxes[k].size(), line_boxes[k], indices});
        prev_size = curr_size;
    }

    //remove lines with zero bounding boxes
    int curr_max = 0;
    long unsigned int curr_idx;
    vector<RotatedRect> curr_box;
    vector<int> curr_ind;
    vector<Triplets> box_indices;
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].idx == 0)
        {
            box_indices.push_back({curr_idx, curr_box, curr_ind});
            curr_max = 0;
        }
        else
        {
            if (lines[i].idx > curr_max)
            {
                curr_idx = lines[i].idx;
                curr_box = lines[i].box;
                curr_ind = lines[i].ind;

                curr_max = lines[i].idx;
            }
        }
    }

    vector<json::value> imageText;
    // Render detections and extract text.
    qDebug()<<box_indices.size()<<":Detection Counter";
    for (int i = 0; i < box_indices.size(); i++)
    {
        vector<int> indices = box_indices[i].ind;
        vector<RotatedRect> line_boxes = box_indices[i].box;
        if (indices.size() != 0)
        {
            sort(indices.begin(), indices.end());

            Point2f ratio((float)frame.cols / inpWidth, (float)frame.rows / inpHeight);
            Point2f vertices[4];
            if (detect == "word")
            {
                for (size_t n = 0; n < indices.size(); ++n)
                {
                    RotatedRect &box = line_boxes[indices[n]];
                    box.points(vertices);

                    for (int j = 0; j < 4; ++j)
                    {
                        vertices[j].x *= ratio.x;
                        vertices[j].y *= ratio.y;
                    }

                    for (int j = 0; j < 4; ++j)
                        line(frame, vertices[j], vertices[(j + 1) % 4], Scalar(0, 255, 0), 1);
                }
            }
            else
            {
                RotatedRect &start_box = line_boxes[indices[0]];
                Point2f start_vertices[4];
                start_box.points(start_vertices);
                vertices[0] = start_vertices[0];
                vertices[1] = start_vertices[1];

                int last = indices.size() - 1;
                RotatedRect &end_box = line_boxes[indices[last]];
                Point2f end_vertices[4];
                end_box.points(end_vertices);
                vertices[2] = end_vertices[2];
                vertices[3] = end_vertices[3];

                for (int j = 0; j < 4; ++j)
                {
                    vertices[j].x *= ratio.x;
                    vertices[j].y *= ratio.y;
                }
                for (int j = 0; j < 4; ++j)
                    line(frame, vertices[j], vertices[(j + 1) % 4], Scalar(255, 255, 0), 1);
            }

            vector<Point2f> vert{{vertices[0].x, vertices[0].y},
                                 {vertices[1].x, vertices[1].y},
                                 {vertices[2].x, vertices[2].y},
                                 {vertices[3].x, vertices[3].y}};

            // Text recognition
            RotatedRect new_box = minAreaRect(vert);
            Rect rect3 = new_box.boundingRect();

//            qDebug()<<rect3.x<<"rect3.x";
//            qDebug()<<rect3.height<<"rect3.height";
//            qDebug()<<"***";
//            qDebug()<<rect3.y<<"rect3.y";
//            qDebug()<<rect3.width<<"rect3.width";

            if(rect3.y <0){
                rect3.y = 0;
            }
            if(rect3.x <0){
                rect3.x = 0;
            }
            if(rect3.y+rect3.height>img.rows){
                break;
            }
            if(rect3.x+rect3.width>img.cols){
                break;
            }
            Mat box_img = frame(rect3);
            string output;

            tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
            // Initialize tesseract-ocr with English, without specifying tessdata path
            if (api->Init(TESSDATA_PATH, "tur+eng")) {
                fprintf(stderr, "Could not initialize tesseract.\n");
                exit(1);
            }

            api->SetImage(box_img.data, box_img.cols, box_img.rows, PSM_AUTO, box_img.step);
            cvtColor(box_img, box_img, COLOR_BGR2GRAY);
            std::string outText = api->GetUTF8Text();
            outText = api->GetUTF8Text();
            printf("OCR output:\n%s", outText.c_str());
            qDebug()<<outText.c_str();

            api->End();
            delete api;

            output.erase(remove(output.begin(), output.end(), '\n'), output.end());


        }
    }
    rotateddata[i].detectionboxcounter = (int)box_indices.size();

    qDebug()<<rotateddata[i].angle<<":  Rotated-Angle";
    qDebug()<<rotateddata[i].detectionboxcounter<<":  DetectionboxCounter";


    // Put efficiency information.
    vector<double> layersTimes;
    double freq = getTickFrequency() / 1000;
    double t = net.getPerfProfile(layersTimes) / freq;
    string label = format("Inference time: %.2f ms", t);
    putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
//    imwrite("/home/karali/output.jpg", frame);
//    imshow("Output", frame);
//        waitKey(0);
    //        return ;
}

