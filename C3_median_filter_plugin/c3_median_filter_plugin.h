#ifndef C3_MEDIAN_FILTER_PLUGIN_H
#define C3_MEDIAN_FILTER_PLUGIN_H

#include "c3_median_filter_plugin_global.h"
#include "../Interface/cvplugininterface.h"

class C3_MEDIAN_FILTER_PLUGINSHARED_EXPORT C3_median_filter_plugin :
        public QObject,
        public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.amin.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    C3_median_filter_plugin();
    ~C3_median_filter_plugin() override;

    // CvPluginInterface interface
public:
    QString description() override;
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage) override;
};

#endif // C3_MEDIAN_FILTER_PLUGIN_H
