#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "converter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_convert_clicked();

    void on_browse_clicked();

signals:
    void Convert(QString input);

private:
    Ui::MainWindow *ui;
    Converter converter_;
};
#endif // MAINWINDOW_H
