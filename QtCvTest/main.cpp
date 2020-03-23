#include <QCoreApplication>
#include <opencv2/opencv.hpp>

const std::string imagePath("/home/jamehd/Desktop/Image/minion.jpg");

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  cv::Mat image = cv::imread(imagePath);
  cv::imshow("Ouput", image);
  return a.exec();
}
