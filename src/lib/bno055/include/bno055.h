#ifndef BNO055_H__
#define BNO055_H_

#include <stdint.h>
#include <stdio.h>

#include "i2c.h"

#include "pico/stdlib.h"

/* ------------------------------------------------------------ *
 * PARAMERER DEFINES                                            *
 * ------------------------------------------------------------ */
#define ENABLE  1
#define DISABLE 0

/* ------------------------------------------------------------ *
 * Bosch BNO0555 I2C ADDRESS                                    *
 * ------------------------------------------------------------ */

#define BNO055_ADDR             0x28

/* ------------------------------------------------------------ *
 * Bosch BNO0555 Chip ID                                        *
 * ------------------------------------------------------------ */

#define BNO055_CHIP_ID          0xA0

/* ------------------------------------------------------------ *
 * Bosch BNO0555 Registers                                      *
 * ------------------------------------------------------------ */

#define BNO055_CHIP_ID_ADDR     0x00
#define BNO055_MODE_IMU         0x08

/* Page ID register, for page switching */
#define BNO055_PAGE_ID_ADDR     0x07

#define BNO055_OPR_MODE_ADDR    0x3D
#define BNO055_PWR_MODE_ADDR    0x3E

#define BNO055_SYS_STAT_ADDR    0x39
#define BNO055_CALIB_STAT_ADDR  0x35
#define BNO055_STEST_RSLT_ADDR  0x34

#define BNO055_SYS_TRIGGER_ADDR 0x3F
#define BNO055_SYS_ERROR_ADDR   0x3A

#define BNO055_TEMP_SOURCE_ADDR 0x40

/* Euler data registers */
#define BNO055_EULER_H_LSB_ADDR      0x1A
#define BNO055_EULER_H_MSB_ADDR      0x1B
#define BNO055_EULER_R_LSB_ADDR      0x1C
#define BNO055_EULER_R_MSB_ADDR      0x1D
#define BNO055_EULER_P_LSB_ADDR      0x1E
#define BNO055_EULER_P_MSB_ADDR      0x1F

/* Acc data registers */
#define BNO055_ACC_DATA_X_LSB_ADDR     0x08
#define BNO055_ACC_DATA_X_MSB_ADDR     0x09
#define BNO055_ACC_DATA_Y_LSB_ADDR     0x0A
#define BNO055_ACC_DATA_Y_MSB_ADDR     0x0B
#define BNO055_ACC_DATA_Z_LSB_ADDR     0x0C
#define BNO055_ACC_DATA_Z_MSB_ADDR     0x0D

/* Mag data registers */
#define BNO055_MAG_DATA_X_LSB_ADDR     0x0E
#define BNO055_MAG_DATA_X_MSB_ADDR     0x0F
#define BNO055_MAG_DATA_Y_LSB_ADDR     0x10
#define BNO055_MAG_DATA_Y_MSB_ADDR     0x11
#define BNO055_MAG_DATA_Z_LSB_ADDR     0x12
#define BNO055_MAG_DATA_Z_MSB_ADDR     0x13

/* Gyro data registers */
#define BNO055_GYRO_DATA_X_LSB_ADDR     0x14
#define BNO055_GYRO_DATA_X_MSB_ADDR     0x15
#define BNO055_GYRO_DATA_Y_LSB_ADDR     0x16
#define BNO055_GYRO_DATA_Y_MSB_ADDR     0x17
#define BNO055_GYRO_DATA_Z_LSB_ADDR     0x18
#define BNO055_GYRO_DATA_Z_MSB_ADDR     0x19

/* Registers to set Gyrosscope Any Motion Interrupt */
/* Interrupt registers*/
#define BNO055_INT_MASK_ADDR                0X0F
#define BNO055_INT_ADDR                     0X10
#define BNO055_GYRO_INTR_SETING_ADDR        0X17
#define BNO055_GYRO_ANY_MOTION_THRES_ADDR   0X1E
#define BNO055_GYRO_ANY_MOTION_SET_ADDR     0X1F

/*Interrupt status registers*/
#define BNO055_INTR_STAT_ADDR               0x37

#define BNO055_INTR_STAT_GYRO_ANY_MOTION_POS      2
#define BNO055_INTR_STAT_GYRO_ANY_MOTION_MSK      0X04
#define BNO055_INTR_STAT_GYRO_ANY_MOTION_LEN      1

#define BNO055_INTR_STAT_ACC_ANY_MOTION_POS      6
#define BNO055_INTR_STAT_ACC_ANY_MOTION_MSK      0X40
#define BNO055_INTR_STAT_ACC_ANY_MOTION_LEN      1

/* Registers to set Gyrosscope Any Motion Interrupt */
/* Interrupt registers*/
#define BNO055_INT_MASK_ADDR                0X0F
#define BNO055_INT_ADDR                     0X10
#define BNO055_GYRO_INTR_SETING_ADDR        0X17
#define BNO055_GYRO_ANY_MOTION_THRES_ADDR   0X1E
#define BNO055_GYRO_ANY_MOTION_SET_ADDR     0X1F

/* Axis mapping registers and value for remap P0*/
#define BNO055_AXIS_REMAP_CONFIG_ADDR     0x41
#define BNO055_AXIS_REMAP_SIGN_ADDR       0x42
#define BNO055_AXIS_CONFIG                0x21
#define BNO055_AXIS_SIGN                  0x04

/* PAGE1 REGISTER DEFINITION START*/
        /* Interrupt mask register */
#define BNO055_INT_MSK_ADDR                 0X0F
#define BNO055_INT_MSK_ACC_NM_MSK           0X80
#define BNO055_INT_MSK_ACC_NM_POS           7
#define BNO055_INT_MSK_ACC_AM_MSK           0X40
#define BNO055_INT_MSK_ACC_AM_POS           6
        
        /* Interrupt enabled register */
#define BNO055_INT_EN_ADDR                  0X10
#define BNO055_INT_EN_ACC_NM_MSK            0X80
#define BNO055_INT_EN_ACC_NM_POS            7
#define BNO055_INT_EN_ACC_AM_MSK            0X40
#define BNO055_INT_EN_ACC_AM_POS            6
        
        /* Any Motion interrupt threshold register */
#define BNO055_ACC_AM_THRES_ADDR            0X11
#define BNO055_ACC_AM_THRES_MSK             0XFF
#define BNO055_ACC_AM_THRES_POS             0
        
        /* Acceleration interrupt settings register */
#define BNO055_ACC_INT_Settings_ADDR        0X12
#define BNO055_ACC_INT_Settings_ACC_X_MSK   0X04
#define BNO055_ACC_INT_Settings_ACC_X_POS   2
#define BNO055_ACC_INT_Settings_ACC_Y_MSK   0X08
#define BNO055_ACC_INT_Settings_ACC_Y_POS   3
#define BNO055_ACC_INT_Settings_ACC_Z_MSK   0X10
#define BNO055_ACC_INT_Settings_ACC_Z_POS   4
#define BNO055_ACC_INT_Settings_AM_DUR_MSK  0x03
#define BNO055_ACC_INT_Settings_AM_DUR_POS  0

        /* Accelerometer Offset registers */
#define BNO055_ACCEL_OFFSET_X_LSB_ADDR      0X55
#define BNO055_ACCEL_OFFSET_X_MSB_ADDR      0X56
#define BNO055_ACCEL_OFFSET_Y_LSB_ADDR      0X57
#define BNO055_ACCEL_OFFSET_Y_MSB_ADDR      0X58
#define BNO055_ACCEL_OFFSET_Z_LSB_ADDR      0X59
#define BNO055_ACCEL_OFFSET_Z_MSB_ADDR      0X5A

        /* Magnetometer Offset registers */
#define BNO055_MAG_OFFSET_X_LSB_ADDR        0X5B
#define BNO055_MAG_OFFSET_X_MSB_ADDR        0X5C
#define BNO055_MAG_OFFSET_Y_LSB_ADDR        0X5D
#define BNO055_MAG_OFFSET_Y_MSB_ADDR        0X5E
#define BNO055_MAG_OFFSET_Z_LSB_ADDR        0X5F
#define BNO055_MAG_OFFSET_Z_MSB_ADDR        0X60

        /* Gyroscope Offset register s*/
#define BNO055_GYRO_OFFSET_X_LSB_ADDR       0X61
#define BNO055_GYRO_OFFSET_X_MSB_ADDR       0X62
#define BNO055_GYRO_OFFSET_Y_LSB_ADDR       0X63
#define BNO055_GYRO_OFFSET_Y_MSB_ADDR       0X64
#define BNO055_GYRO_OFFSET_Z_LSB_ADDR       0X65
#define BNO055_GYRO_OFFSET_Z_MSB_ADDR       0X66

typedef enum {
    BNO055_ALL_GOOD    = 0x00,
    BNO055_WRITE_ERROR = 0x0F,
    BNO055_READ_ERROR  = 0xF0,
} BNO055_state_e;

typedef enum {
   config   = 0x00,
   /* Non-Fusion Modes */
   acconly  = 0x01,
   magonly  = 0x02,
   gyronly  = 0x03,
   accmag   = 0x04,
   accgyro  = 0x05,
   maggyro  = 0x06,
   amg      = 0x07,
   /* Fusion Modes */
   imu      = 0x08,
   compass  = 0x09,
   m4g      = 0x0A,
   ndof     = 0x0B,
   ndof_fmc = 0x0C
} operation_mode_t;

typedef enum {
   normal  = 0x00,
   low     = 0x01,
   suspend = 0x02
} power_mode_t;

typedef struct {

    uint16_t accel_offset_x;
    uint16_t accel_offset_y;
    uint16_t accel_offset_z;

    uint16_t gyro_offset_x;
    uint16_t gyro_offset_y;
    uint16_t gyro_offset_z;

    uint16_t mag_offset_x;
    uint16_t mag_offset_y;
    uint16_t mag_offset_z;

} BNO055_offsets_t;

typedef struct {

    uint8_t host_intr_pin;
    uint8_t last_page;
    operation_mode_t last_op_mode;
    BNO055_offsets_t offsets;

} BNO055_params_t;

typedef enum {

    axis_remap_P0 = 0x21,
    axis_remap_P1 = 0x24,
    axis_remap_P2 = 0x24,
    axis_remap_P3 = 0x21,
    axis_remap_P4 = 0x24,
    axis_remap_P5 = 0x21,
    axis_remap_P6 = 0x21,
    axis_remap_P7 = 0x24,

} axis_remap_t;

typedef enum {

    axis_sign_P0 = 0x04,
    axis_sign_P1 = 0x00,
    axis_sign_P2 = 0x06,
    axis_sign_P3 = 0x02,
    axis_sign_P4 = 0x03,
    axis_sign_P5 = 0x01,
    axis_sign_P6 = 0x07,
    axis_sign_P7 = 0x05,

} axis_sign_t;

typedef struct axis_placement {

    axis_remap_t    axis_remap;
    axis_sign_t     axis_sign;

} axis_placement_t ;


typedef struct {
   double eul_head;
   double eul_roll;
   double eul_pitch;
} euler_angles_t;

BNO055_state_e BNO055_init();
void BNO055_test();

BNO055_state_e BNO055_reset_system(void);
BNO055_state_e BNO055_read_SYS_TRIG(void);
BNO055_state_e BNO055_read_INT_STA(void);
BNO055_state_e BNO055_read_SYS_STATUS(void);

BNO055_state_e BNO055_enable_any_motion_intr(uint8_t threshold, uint8_t duration);
BNO055_state_e BNO055_enable_intr_on_XYZ(uint8_t x, uint8_t y, uint8_t z);

BNO055_state_e BNO055_set_offsets(BNO055_offsets_t* pt_BNO055_offsets);

BNO055_state_e BNO055_get_device_id();

BNO055_state_e BNO055_set_reg_page(uint8_t page);

BNO055_state_e BNO055_set_to_config_mode();
BNO055_state_e BNO055_print_operation_mode();
BNO055_state_e BNO055_set_operation_mode(operation_mode_t newmode);

BNO055_state_e BNO055_set_power_mode(power_mode_t newmode);

BNO055_state_e BNO055_get_calib_status();
BNO055_state_e BNO055_start_selftest();
BNO055_state_e BNO055_selftest_results();

BNO055_state_e BNO055_get_axis_mode(BNO055_params_t* pt_BNO055_var);
BNO055_state_e BNO055_set_axis_mode(axis_placement_t req_axis_placement);

BNO055_state_e BNO055_print_eul(euler_angles_t* ptEulAngles);

BNO055_state_e BNO055_get_acc_xyz();

BNO055_state_e BNO055_get_mag_xyz();

BNO055_state_e BNO055_get_gyro_xyz();

#endif