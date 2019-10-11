/*
Seriaal Communication Module  for xBee
latest update : 18/08/01


*/

#define DATA_MAX 128  //2^
#define SERIAL_RATE 38400

// state names configration
#define NO_SIGNAL 0
#define SENT_KIND 1
#define SENT_DATA 2
#define SEND_DATA_ERROR 3
#define RECEIVED_KIND 4
#define SEND_RECEIVED_RESPONCE 5
#define RECEIVE_DATA_ERROR 6

#define MAX_RECEIPABLE_DATA_NUM 5

#define DATA_NUM 19
#define DATA_FOR_SEND_NUM 11

// send / receive data names address
#define GYRO_X 1
#define GYRO_Y 2
#define GYRO_Z 3
#define ACCEL_X 4
#define ACCEL_Y 5
#define ACCEL_Z 6
#define MAG_X 7
#define MAG_Y 8
#define MAG_Z 9
#define PITCH 10
#define ROLL 11
#define YAW 12
#define JOYSTICK_1 13
#define JOYSTICK_2 14
#define JOYSTICK_3 15
#define JOYSTICK_4 16
#define P_TERM 17
#define I_TERM 18
#define D_TERM 19
#define VOLTAGE 20
#define STATE 21
#define COMMAND 22
#define MODE 23

/*All states here*/
#define ALL_CORRECT 1  //working fine!! (setup was finished completely)
#define SETTING 2  //setting now...
#define MOTOR_EMERGENCY 3 //motor not turning
#define PMOD_EMERGENCY 4 //Pmod NAV not working
#define NON_ASSOCIATE 5  //disconnected with the controller or have something wrong with xBee
#define VOLTAGE_LOW 6

/*All activate mode here*/
#define GENERAL 0  //usual mode
#define ACROBAD 1  //acrobad mode
#define MOTOR_ROTATE_TEST 2 //motor turning test (OBSOLETED) 
#define PMODNAV_TEST 3  //Pmod NAV working test (OBSOLETED) 
#define PWM_TEST_1 4 
#define PWM_TEST_2 5
#define PWM_TEST_3 6
#define SAFE_MODE 7

#define DATA_RECEIVED 1
#define NO_DATA_RECEIVED 2


/*Configration of Serial / SoftwareSerial Communication*/
#define SOFT_SERIAL_RX_PIN 2
#define SOFT_SERIAL_TX_PIN 3

#define STOP_SIGNAL 255

#define DATA_NUM 16

#define MAX_CONNECTED_TIME 100



class Communication{
  public:
    Communication();
    
    bool CheckReceivedData(); 
    void Com_setup();
    void SendOneData(byte);
    void SendMultiData(byte, byte);
    bool CheckConnected();
    byte getCommand();
    byte data[DATA_NUM];

    byte RecieveManyData();
    void ClearBuffer();

    int last_com;

  public:
    byte SendCounter = 0;
};
