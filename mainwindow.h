#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    cv::VideoCapture video;
    cv::Mat img3;
    QTimer *timer;
    QPixmap pixMap;
    QLabel *videoDispaly;
    cv::CascadeClassifier cascade;
    cv::CascadeClassifier nestedCascade;
    double scale=1;

    void onTimerTimeout();

    void detectAndDraw( cv::Mat& img,
                       cv::CascadeClassifier& cascade,
                       cv::CascadeClassifier& nestedCascade,
                       double scale);




};

#endif // MAINWINDOW_H
