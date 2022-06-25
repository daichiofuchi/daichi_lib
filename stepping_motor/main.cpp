#include <mbed.h>
#include <stepping_motor.h>

stepping_motor motor(D3,D8, 4800, 40);
/*
stepping_motor インスタンス名(MD_pwm_pin(内部ではデジタルアウト), MD_DIR, 1回転当たり何パルス与えればよいか, 1パルスごとの周期[μs])
*/

int main(){
    motor.rot(90, 1);
    /*
    インスタンス名.rot(角度<>, 方向<0 or 1>);
    */
}