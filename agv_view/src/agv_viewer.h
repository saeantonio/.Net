#ifndef AGV_VIEWER_H
#define AGV_VIEWER_H

#include <QWidget>
#include <QThread>
#include "ros/ros.h"
#include "std_msgs/String.h"

namespace Ui {
class AGV_Viewer;
}

class agv_subscriber:public QObject{
  Q_OBJECT
signals:
  void positionChanged();

public slots:
  void fetchPosition();
public:
  agv_subscriber();
  ~agv_subscriber();



//public:
//  void chatterCallback(const std_msgs::String::ConstPtr& msg);

};

class AGV_Viewer : public QWidget
{
  Q_OBJECT
  QThread workThread;
public:
  explicit AGV_Viewer(QWidget *parent = nullptr);
  ~AGV_Viewer();
public slots:
  void handlePositionChanged();

private:
  Ui::AGV_Viewer *ui;
  agv_subscriber * subscriber;

protected:
  void paintEvent(QPaintEvent *event) override;

};

//void chatterCallback(const std_msgs::String::ConstPtr& msg)
//{
//  ROS_INFO("I heard: [%s]", msg->data.c_str());
//}




#endif // AGV_VIEWER_H
