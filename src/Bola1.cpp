#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int min_h=63;
int max_h=229;
int s1=0;
int s2=0;
int s3=0;

int main() {
    // createTrackbar("H min", "Trackbars", &min_h, 255);
    // createTrackbar("H max", "Trackbars", &max_h, 255);
    Mat image = imread("/home/ubuntu/Downloads/Bola1.jpg");
    Mat gray,tres;
    
    cvtColor(image, gray, COLOR_BGR2GRAY);
    // while(1){
    inRange(gray,min_h,max_h,tres);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(tres, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (size_t i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(0, 255, 0);
        drawContours(image, contours, static_cast<int>(i), color, 2, LINE_8, hierarchy, 0);
    }
    putText(image, "Jumlah Bola: " + to_string(contours.size()), Point(25, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    // putText(tres, "Jumlah Bola: " + to_string(contours.size()), Point(25, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
    imshow("Deteksi Bola Kuning", image);
    // imshow("tres",tres);
    // imshow("contor",contoursImage);
    waitKey(0);
    // }
    return 0;
}
