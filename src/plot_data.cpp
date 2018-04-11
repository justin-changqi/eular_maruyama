#include "plot_data.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new MainWindow)
{

}

MainWindow::~MainWindow()
{
  delete ui;
}
