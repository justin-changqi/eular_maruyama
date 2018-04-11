#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

// private slots:
//   void realtimeDataSlot();
//   void bracketDataSlot();
//   void screenShot();
//   void allScreenShots();
//
private:
  MainWindow *ui;
//   QString demoName;
//   QTimer dataTimer;
//   QCPItemTracer *itemDemoPhaseTracer;
//   int currentDemoIndex;
};

#endif // MAINWINDOW_H
