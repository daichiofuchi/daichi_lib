/**********************************************************************
File    DMS_2Y0A02.h
Ver     1.1.0
Date    1.0.0   2022/5/23
1.0.0   2022/05/23
Auther  Daichi Ofuchi
**********************************************************************/

/**********************************************************************
Include guard
**********************************************************************/
#ifndef __DMS_2Y0A02_H__
#define __DMS_2Y0A02_H__

/**********************************************************************
Includes
**********************************************************************/
#include "mbed.h"

/**********************************************************************
PID class
**********************************************************************/
class DMS_2Y0A02
{
public:
  DMS_2Y0A02(PinName); //コンストラクタ 引き数1:pwmのピン
  float get_distance();

private:
  float get_distance_var;
  AnalogIn dms_input;
};

#endif

/**********************************************************************
Usage example
**********************************************************************/

