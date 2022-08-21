#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QProgressBar>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QThread *convert_thread = new QThread();
  converter_.moveToThread(convert_thread);

  connect(&converter_, &Converter::Started, this, [this]() {
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(1);
  });

  ui->progressBar->setRange(1, 100);
  ui->progressBar->setValue(1);
  ui->progressBar->setVisible(false);
  connect(&converter_, &Converter::Progress, this, [this](int p) {
    ui->progressBar->setValue(p);
    if (p >= 100) {
      // ui->progressBar->setVisible(false);
      ui->convert->setEnabled(true);
    }
  });

  connect(&converter_, &Converter::Failed, this, [this](QString msg) {
    ui->msg->setText(msg);
    // ui->progressBar->setVisible(false);
    ui->convert->setEnabled(true);
  });

  connect(this, &MainWindow::Convert, &converter_, &Converter::Convert);

  convert_thread->start();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_convert_clicked() {
  if (ui->input->text().isEmpty()) {
    return;
  }
  ui->convert->setEnabled(false);
  emit Convert(ui->input->text());
}

void MainWindow::on_browse_clicked() {
  QString path = QFileDialog::getOpenFileName(this, "选择源文件", "", "*.urc");
  if (path.isEmpty()) {
    return;
  }
  ui->input->setText(path);
}
