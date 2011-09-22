#ifndef _DRACO_GPIO_H
#define _DRACO_GPIO_H

#define GPIO_127 	127
#define GPIO_128	128
#define GPIO_15		15
#define GPIO_129	129
#define GPIO_130	130
#define GPIO_131	131
#define GPIO_132	132
#define GPIO_133	133
#define GPIO_134	134
#define GPIO_135	135
#define GPIO_136	136
#define GPIO_137	137
#define GPIO_138	138
#define GPIO_139	139

#define GPIO_56		56
#define GPIO_57		57
#define GPIO_12		12
#define GPIO_13		13
#define GPIO_14		14
#define GPIO_22		22
#define GPIO_7		7
#define GPIO_179	179
#define GPIO_180	180
#define GPIO_181	181
#define GPIO_182	182
#define GPIO_178	178
#define GPIO_177	177

// ahora las definiciones por etiqueta

#define ON_MONITOR		GPIO_127
#define POWER_IN_CONTROL	GPIO_128
#define _LB_DETECT		GPIO_15
#define	_PWR_SERVOS		GPIO_129
#define PWM_S1			GPIO_130
#define PWM_S2			GPIO_131
#define PWM_S3                  GPIO_132
#define PWM_S4                  GPIO_133
#define PWM_S5                  GPIO_134
#define PWM_S6                  GPIO_135
#define S3D_PC			GPIO_136
#define S3D_LC			GPIO_137
#define S3D_SIGN		GPIO_138
#define S3D_SENSOR_EN		GPIO_139
#define _SPK_ENABLE		GPIO_56
#define DNA_TX_RX		GPIO_57
#define MSECURE			GPIO_22
#define SYS_BOOT5		GPIO_7
#define TOUCH_RX1		GPIO_179
#define TOUCH_RX2		GPIO_180
#define TOUCH_RX3		GPIO_181
#define TOUCH_TX		GPIO_182
#define RF_IRQ			GPIO_178
#define RF_CE			GPIO_177


#define DEVNAME "DRACO_GPIO_mod"

#define DRACO_GPIO_NUM  27 // numero total de gpios en la estructura a configurar
#define DRACO_GPIO_OUTPUT 1
#define DRACO_GPIO_INPUT 0
#define DRACO_GPIO_ACTIVE_LOW 0
#define DRACO_GPIO_ACTIVE_HIGH 1

// definicion de los comandos validos para IOCTL

#define DRACO_GPIO_IOC_MAGIC            'k'
#define DRACO_GPIO_RESET                _IO(DRACO_GPIO_IOC_MAGIC, 0)
#define DRACO_GPIO_SET_IOC              _IOW(DRACO_GPIO_IOC_MAGIC, 1, unsigned long *)      
#define DRACO_GPIO_GET_IOC              _IOR(DRACO_GPIO_IOC_MAGIC, 2, unsigned long *)
#define DRACO_GPIO_SET_CONFIG_IOC       _IOW(DRACO_GPIO_IOC_MAGIC, 3, unsigned long *)
#define DRACO_GPIO_GET_CONFIG_IOC       _IOR(DRACO_GPIO_IOC_MAGIC, 4, unsigned long *)

#define DRACO_GPIO_NUM_PINS     27


typedef struct  {
       const char *sLabel;
        unsigned uGpio;
        unsigned uDirection;
        unsigned uActiveFlag;
	unsigned uDefaultValue;
}zGpioPin;

#endif
