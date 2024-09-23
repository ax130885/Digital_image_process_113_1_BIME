#ifndef GENERALPROCESS_H
#define GENERALPROCESS_H

#include <QObject>
#include <QImage>

class GeneralProcess : public QObject
{
    Q_OBJECT
public:
    explicit GeneralProcess(QObject *parent = nullptr);
    std::unique_ptr<QImage> UploadFile();
    std::unique_ptr<QImage> calculateHistogram(std::unique_ptr<QImage> &image);

signals:

private:
};

#endif // GENERALPROCESS_H
