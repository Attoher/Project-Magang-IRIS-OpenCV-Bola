#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int min_h = 131;
int max_h = 255;
int noise = 23;
int mindist = 60, param1 = 214, param2 = 60, minrad = 60, maxrad = 66;

int main() {
    // namedWindow("Trackbars", WINDOW_AUTOSIZE);

    // createTrackbar("mindist", "Trackbars", &mindist, 510);
    // createTrackbar("param1", "Trackbars", &param1, 510);
    // createTrackbar("param2", "Trackbars", &param2, 510);
    // createTrackbar("minrad", "Trackbars", &minrad, 510);
    // createTrackbar("maxrad", "Trackbars", &maxrad, 510);

    Mat image = imread("/home/ubuntu/Downloads/Bola2.jpg", IMREAD_COLOR), tres;
    Mat gray;
    resize(image, image, Size(), 2, 2);
    cvtColor(image, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray, noise);

    // while (1) {
        inRange(gray, min_h, max_h, tres);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(tres, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

        // for (size_t i = 0; i < contours.size(); i++) {
        //     Scalar color = Scalar(0, 255, 0);
        //     drawContours(image, contours, static_cast<int>(i), color, 1, LINE_8, hierarchy, 0);
        // }

        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 2, mindist, param1, param2, minrad, maxrad);

        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(image, center, radius, Scalar(0, 255, 0), 2);

            circle(image, center, 5, Scalar(0, 0, 255), -1);
        }

        cout << circles.size() << endl;

        // imshow("tres", tres);
        putText(image, "Jumlah Bola: " + to_string(circles.size()), Point(25, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
        imshow("Circle Detection", image);
        waitKey(0);
    // }

    return 0;
}
