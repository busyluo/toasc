#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>

class Converter : public QObject
{
    Q_OBJECT
public:
    explicit Converter(QObject *parent = nullptr);

public slots:
    void Convert(QString input);

signals:
    void Progress(int p);
    void Started();
    void Failed(QString msg);
};

#endif // CONVERTER_H
