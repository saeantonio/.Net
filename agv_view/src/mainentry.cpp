#include "mainentry.h"
#include "agv_viewer.h"
#include <QApplication>

int main(int argc,char* argv[])
{
  QApplication app(argc,argv);
  AGV_Viewer window;

  window.show();
  return  app.exec();

}
