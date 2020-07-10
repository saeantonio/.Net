#include "agv_viewer.h"
#include "ui_agv_viewer.h"
#include <QPainter>
#include <QtDebug>
agv_subscriber::agv_subscriber()
{

}

agv_subscriber::~agv_subscriber()
{

}
void static chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  qDebug()<<"chatterCallback"<<endl;
}
void agv_subscriber::fetchPosition()
{

  int argc=0;
  char* argv[5];
  ros::init(argc,argv,"agv_subscriber");
  qDebug()<<"fetchPosition:in"<<endl;
  ros::NodeHandle nodeHandle;
  ros::Subscriber sub=nodeHandle.subscribe("agv_coordinator",1000, chatterCallback);
  ros::Rate loop_rate(10);
  while (ros::ok()) {
    qDebug()<<"fetchPosition:working"<<endl;
    loop_rate.sleep();
    ros::spinOnce();
    emit positionChanged();

  }



}


AGV_Viewer::AGV_Viewer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AGV_Viewer)
{
  qDebug()<<"AGV_Viewer"<<endl;
  ui->setupUi(this);
  subscriber=new agv_subscriber;
  connect(&workThread,&QThread::finished,subscriber,&QObject::deleteLater);
  connect(subscriber,&agv_subscriber::positionChanged,this,&AGV_Viewer::handlePositionChanged);
  connect(&workThread,&QThread::started,subscriber,&agv_subscriber::fetchPosition);
  workThread.start();
  qDebug()<<"AGV_Viewer:constructed"<<endl;
}

AGV_Viewer::~AGV_Viewer()
{
  workThread.quit();
  workThread.wait();
  delete ui;
}

void AGV_Viewer::handlePositionChanged()
{
  qDebug()<<"handlePositionChanged"<<endl;
  update();
}


void AGV_Viewer::paintEvent(QPaintEvent *event)
{
  qDebug()<<"paintEvent"<<endl;
  QPainter paineter(this);

  paineter.setPen(Qt::red);
  paineter.drawLine(50,50,300,300);
}



