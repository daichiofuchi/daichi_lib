#include "mbed.h"
 
#include "BNO055.h"
 
//PCへのシリアル通信
Serial pc(USBTX, USBRX, 115200);
 
//センサーに使用するI2C
I2C ifaceI2C(PB_7, PB_6);
 
BOARDC_BNO055 sensor1(&ifaceI2C);
 
int main(){
 

    pc.printf("mbed READY\r\n");
 
 
    pc.printf("Start Comm - -- ---- --------\r\n");
    //I2Cインターフェースで２つのセンサーを使用する(200KHz)
    ifaceI2C.frequency(100000);
    sensor1.initialize(false);

    pc.printf("Start Comm - -- ---- --------\r\n");
   
    wait_ms(1000);
 
    //各センサーの値を格納するための変数宣言
    short dataBox[12];
    float scAcc, scMag, scGyro, scEUL, scTemp;
    float ax, ay, az, mx, my, mz, gx, gy, gz, yaw, roll, pitch, temp;
 
    //センサーのRAW値を実際の数値に変換するための倍率を取得する
    scAcc = sensor1.getAccScale();
    scMag = sensor1.getMagScale();
    scGyro = sensor1.getGyroScale();
    scEUL = sensor1.getEulerScale();
    scTemp = sensor1.getTempScale();
 
    while(1){
        //配列dataBoxに、9軸の値とオイラー角(yaw roll pitch)を格納(計12個の値)
        sensor1.get9AxisAndEUL(dataBox);
 
        //倍率をかけてRaw値を実際の値に変換
        ax = (float)dataBox[0] * scAcc;
        ay = (float)dataBox[1] * scAcc;
        az = (float)dataBox[2] * scAcc;
        mx = (float)dataBox[3] * scMag;
        my = (float)dataBox[4] * scMag;
        mz = (float)dataBox[5] * scMag;
        gx = (float)dataBox[6] * scGyro;
        gy = (float)dataBox[7] * scGyro;
        gz = (float)dataBox[8] * scGyro;
        yaw = (float)dataBox[9] * scEUL;
        roll = (float)dataBox[10] * scEUL;
        pitch = (float)dataBox[11] * scEUL;
 
        //BNO055内のセンサーの参考温度を取得して実際の値に変換
        temp = (float)sensor1.getTemperature() * scTemp;
 
        pc.printf(
            "Acc = X[%06.5f], Y[%06.5f], Z[%06.5f]\r\nMag = X[%06.5f], Y[%06.5f], Z[%06.5f]\r\nGyr = X[%06.5f], Y[%06.5f], Z[%06.5f]\r\n",
            ax, ay, az, mx, my, mz, gx, gy, gz
        );
 
        pc.printf(
            "yaw\t\t = %05.4f[deg], data = %0d\r\nroll\t\t = %05.4f[deg], data = %0d\r\npitch\t\t = %05.4f[deg], data = %0d\r\n",
            yaw, dataBox[9], roll, dataBox[10], pitch, dataBox[11]
        );

        pc.printf(
            "Temperature\t = BNO055 -> %03.3f[degC])\r\n",
            temp
        );
 
        wait_ms(1000);
    }
}
 
