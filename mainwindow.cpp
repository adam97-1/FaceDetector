#include "mainwindow.h"
#include "asmOpenCv.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);


//     Load classifiers from "opencv/data/haarcascades" directory
//    nestedCascade.load("./haarcascades/haarcascade_eye.xml") ;

    // Change path before execution
    cascade.load("./cascade/cascade.xml") ;


    timer->start(1);
    video.open(0);
    videoDispaly = new QLabel("Test", this);
    videoDispaly->resize(600,600);
    resize(600,600);
}

void MainWindow::onTimerTimeout()
{

    video >> img3;
    detectAndDraw( img3, cascade, nestedCascade, scale );
    pixMap = ASM::cvMatToQPixmap(img3);
    videoDispaly->setPixmap(pixMap);
}

void MainWindow::detectAndDraw(cv::Mat &img, cv::CascadeClassifier &cascade, cv::CascadeClassifier &nestedCascade, double scale)
{
    std::vector<cv::Rect> faces, faces2;
    cv::Mat gray, smallImg;

    cvtColor( img, gray, cv::COLOR_BGR2GRAY ); // Convert to Gray Scale
    double fx = 1 / scale;

    // Resize the Grayscale Image
    cv::resize( gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    // Detect faces of different sizes using cascade classifier
    cascade.detectMultiScale( smallImg, faces, 1.1,
                             2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

    // Draw circles around the faces
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Rect r = faces[i];
        cv::Mat smallImgROI;
        std::vector<cv::Rect> nestedObjects;
        cv::Point center;
        cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing tool

        rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                      cvPoint(cvRound((r.x + r.width-1)*scale),
                              cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
//        if( nestedCascade.empty() )
//            continue;
//        smallImgROI = smallImg( r );

//        // Detection of eyes in the input image
//        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2,
//                                       0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

//        // Draw circles around eyes
//        for ( size_t j = 0; j < nestedObjects.size(); j++ )
//        {
//            cv::Rect nr = nestedObjects[j];
//            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
//            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
//            radius = cvRound((nr.width + nr.height)*0.25*scale);
//            circle( img, center, radius, color, 3, 8, 0 );
//        }
    }
}
