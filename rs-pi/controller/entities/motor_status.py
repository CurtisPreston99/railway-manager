from entities.motor import Motor


class MotorStatus:
    motor1: Motor = Motor()
    motor2: Motor = Motor()
    motor3: Motor = Motor()
    motor4: Motor = Motor()

    # {"motor_1":{"spd":100,"forward":true},"motor_2":{"spd":50,"forward":false},"motor_3":{"spd":50,"forward":false},"motor_4":{"spd":50,"forward":false}}
    def toDict(self):
        return {
            "motor_1": self.motor1.ToDict(),
            "motor_2": self.motor2.ToDict(),
            "motor_3": self.motor3.ToDict(),
            "motor_4": self.motor4.ToDict(),
        }
    
    def fromDict(self,status):
        return self