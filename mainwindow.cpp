#include "mainwindow.h"
#include "asmOpenCv.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);

    cascade.load("./cascade/cascade.xml") ;


    timer->start(1);
    video.open(0);
    videoDispaly = new QLabel("Test", this);
    video >> img3;
    pixMap = ASM::cvMatToQPixmap(img3);
    videoDispaly->resize(pixMap.size());
    resize(pixMap.size());
}

void MainWindow::onTimerTimeout()
{

    video >> img3;
    detectAndDraw( img3, cascade, scale );
    pixMap = ASM::cvMatToQPixmap(img3);
    videoDispaly->resize(size());
    videoDispaly->setPixmap(pixMap.scaled(size()));

}

void MainWindow::detectAndDraw(cv::Mat &img, cv::CascadeClassifier &cascade, double scale)
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
    }
}
