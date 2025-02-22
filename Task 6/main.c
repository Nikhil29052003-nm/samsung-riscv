#include <debug.h>
#include <ch32v00x.h>
#include <ch32v00x_gpio.h>

#define SDA_PIN GPIO_Pin_1
#define SCL_PIN GPIO_Pin_2
#define LCD_Address 0x27

#define ULTRASONIC_TRIGGER_PIN GPIO_Pin_4
#define ULTRASONIC_ECHO_PIN GPIO_Pin_3
#define IR_SENSOR_PIN GPIO_Pin_5

#define BUZZER_PIN GPIO_Pin_2

void lcd_send_cmd(unsigned char cmd);
void lcd_send_data(unsigned char data);
void lcd_send_str(const char *str);
void lcd_init(void);
void delay_ms(unsigned int ms);

void GPIO_Config(void) {
    
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;
    
        // Configure PC1 and PC2 for I2C SDA and SCL
        GPIO_InitStructure.GPIO_Pin = SDA_PIN | SCL_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    
        
            // Configure ultrasonic sensor pins
        GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIGGER_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = ULTRASONIC_ECHO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        
            // Configure IR sensor pin
        GPIO_InitStructure.GPIO_Pin = IR_SENSOR_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        
#define BUZZER_PIN GPIO_Pin_2
        GPIO_InitStructure.GPIO_Pin = BUZZER_PIN ;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);


        }
        
        uint32_t Ultrasonic_Read(void) {
            uint32_t echoTime = 0;
            GPIO_WriteBit(GPIOD, ULTRASONIC_TRIGGER_PIN, SET);
            delay_ms(10);
            GPIO_WriteBit(GPIOD, ULTRASONIC_TRIGGER_PIN, RESET);
            while (GPIO_ReadInputDataBit(GPIOD, ULTRASONIC_ECHO_PIN) == Bit_RESET);
            while (GPIO_ReadInputDataBit(GPIOD, ULTRASONIC_ECHO_PIN) == Bit_SET) echoTime++;
            return echoTime;
        }
        
        float Calculate_Distance(uint32_t echoTime) {
            return (echoTime / 2.0) * 0.034;
        }
        
        void check_sensors(void) {
            uint32_t echoTime = Ultrasonic_Read();
            float distance = Calculate_Distance(echoTime);
            uint8_t ir_status = GPIO_ReadInputDataBit(GPIOD, IR_SENSOR_PIN);
          
            if (distance < 10) {
                
                lcd_send_str("Collision Warning!");
                GPIO_WriteBit(GPIOD, BUZZER_PIN, Bit_SET);
                delay_ms(1000);
            } else {
             
                GPIO_WriteBit(GPIOD, BUZZER_PIN, Bit_RESET);
                
            }
        
            if (ir_status == 0) {
                lcd_send_str("Lane Departure!");
                GPIO_WriteBit(GPIOD, BUZZER_PIN, Bit_SET);
             
            } else {
               
           
                GPIO_WriteBit(GPIOD, BUZZER_PIN, Bit_RESET);
               
            }
        }
        void delay_ms(unsigned int ms) {
            for (unsigned int i = 0; i < ms; i++) {
                for (unsigned int j = 0; j < 8000; j++) {
                    __NOP();
                }
            }
        }
          
        int main(void) {
            NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
            SystemCoreClockUpdate();
            Delay_Init();
            GPIO_Config();
            lcd_init();
        
            while (1) {
                lcd_send_str("Safe Driving");
                delay_ms(500);
                lcd_send_cmd(0x01);
                check_sensors();
                delay_ms(1000);
                

                
            }
        }
       
void i2c_write(unsigned char dat) {
    for (unsigned char i = 0; i < 8; i++) {
        GPIO_WriteBit(GPIOC, SCL_PIN, Bit_RESET);
        if (dat & (0x80 >> i)) {
            GPIO_WriteBit(GPIOC, SDA_PIN, Bit_SET);
        } else {
            GPIO_WriteBit(GPIOC, SDA_PIN, Bit_RESET);
        }
        GPIO_WriteBit(GPIOC, SCL_PIN, Bit_SET);
    }
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_RESET);
}

void i2c_start(void) {
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_SET);
    GPIO_WriteBit(GPIOC, SDA_PIN, Bit_SET);
    delay_ms(1);
    GPIO_WriteBit(GPIOC, SDA_PIN, Bit_RESET);
    delay_ms(1);
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_RESET);
}

void i2c_stop(void) {
    GPIO_WriteBit(GPIOC, SDA_PIN, Bit_RESET);
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_RESET);
    delay_ms(1);
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_SET);
    delay_ms(1);
    GPIO_WriteBit(GPIOC, SDA_PIN, Bit_SET);
}

void i2c_ACK(void) {
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_RESET);
    GPIO_WriteBit(GPIOC, SDA_PIN, Bit_SET);
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_SET);
    while (GPIO_ReadInputDataBit(GPIOC, SDA_PIN));
    GPIO_WriteBit(GPIOC, SCL_PIN, Bit_RESET);
}

void lcd_send_cmd(unsigned char cmd) {
    unsigned char cmd_l = (cmd << 4) & 0xf0;
    unsigned char cmd_u = cmd & 0xf0;

    i2c_start();
    i2c_write(LCD_Address << 1);
    i2c_ACK();
    i2c_write(cmd_u | 0x0C);
    i2c_ACK();
    i2c_write(cmd_u | 0x08);
    i2c_ACK();
    delay_ms(1);
    i2c_write(cmd_l | 0x0C);
    i2c_ACK();
    i2c_write(cmd_l | 0x08);
    i2c_ACK();
    delay_ms(1);
    i2c_stop();
}

void lcd_send_data(unsigned char data) {
    unsigned char data_l = (data << 4) & 0xf0;
    unsigned char data_u = data & 0xf0;

    i2c_start();
    i2c_write(LCD_Address << 1);
    i2c_ACK();
    i2c_write(data_u | 0x0D);
    i2c_ACK();
    i2c_write(data_u | 0x09);
    i2c_ACK();
    delay_ms(1);
    i2c_write(data_l | 0x0D);
    i2c_ACK();
    i2c_write(data_l | 0x09);
    i2c_ACK();
    delay_ms(1);
    i2c_stop();
}

void lcd_send_str(const char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_init(void) {
    lcd_send_cmd(0x02);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x01);
    delay_ms(20);
}
