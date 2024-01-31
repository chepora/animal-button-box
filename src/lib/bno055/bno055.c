#include "../include/bno055.h"

#define IMU_INTR_PIN 28

#define BNODEBUG 0

const bool ENABLED  = true;
const bool DISABLED = false;

BNO055_offsets_t BNO055_offsets = {

    // measured via Adafruits calibration script
    // https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/bno055-sensor-calibration-circuitpython
    .accel_offset_x =  -14,
    .accel_offset_y =  -12,
    .accel_offset_z =  -13,
    //
    .gyro_offset_x  =  -1,
    .gyro_offset_y  =  2,
    .gyro_offset_z  =  3,
    //
    .mag_offset_x   =  -618,
    .mag_offset_y   =  55,
    .mag_offset_z   =  303,
};


static inline uint8_t value_into_reg(uint8_t value, uint8_t reg, uint8_t mask, uint8_t position);

BNO055_state_e BNO055_init(BNO055_params_t pt_BNO055_var){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    pt_BNO055_var.offsets = BNO055_offsets;

    // default i2c is defined via board file
    default_i2c_init();
    // Power-on-reset time for the BNO055 is 650 ms. Give it time to start.
    sleep_ms(650);

    if(BNODEBUG) printf("BNO055 Done\r\n");

    BNO055_state = BNO055_ALL_GOOD;

    return BNO055_state;
}

void BNO055_test(){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;
    
    // Buffer to store raw reads
    uint8_t data[6];

    axis_placement_t req_axis_placement = {
        .axis_remap = axis_remap_P0,
        .axis_sign = axis_sign_P0,
    };

    euler_angles_t tEulAngles;

    power_mode_t req_power_mode = normal;
    
    // Read device ID to make sure that we can communicate with the device
    BNO055_state =  BNO055_get_device_id();

    printf("Setting power mode to NORMAL = 0x00 now.\n");

    BNO055_state =  BNO055_set_power_mode(req_power_mode);

    BNO055_state =  BNO055_get_calib_status();
    BNO055_state =  BNO055_start_selftest();

    BNO055_state =  BNO055_print_operation_mode();

    printf("Will try to set to IMU mode = 0x08 now.\n");

    operation_mode_t mode_imu = imu;

    BNO055_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    BNO055_state =  BNO055_print_operation_mode();

    printf("Will try to set to axis placement P0 now.\n");

    BNO055_state = BNO055_set_axis_mode(req_axis_placement);

    BNO055_state = BNO055_print_eul(&tEulAngles);

    mode_imu = acconly;

    printf("Will try to set to ACCONLY mode = 0x02 now.\n");

    BNO055_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    BNO055_state =  BNO055_print_operation_mode();

    BNO055_state = BNO055_get_acc_xyz();

    mode_imu = magonly;

    printf("Will try to set to MAGONLY mode = 0x02 now.\n");

    BNO055_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    BNO055_state =  BNO055_print_operation_mode();

    BNO055_state = BNO055_get_mag_xyz();

    mode_imu = gyronly;

    printf("Will try to set to GYRONLY mode = 0x03 now.\n");

    BNO055_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    BNO055_state =  BNO055_print_operation_mode();

    BNO055_state = BNO055_get_gyro_xyz();

    mode_imu = amg;

    printf("Will try to set to AMG mode = 0x07 now.\n");

    BNO055_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    BNO055_state =  BNO055_print_operation_mode();

    BNO055_state = BNO055_get_acc_xyz();
    BNO055_state = BNO055_get_mag_xyz();
    BNO055_state = BNO055_get_gyro_xyz();


}

BNO055_state_e BNO055_get_device_id(){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);
    
    // Buffer to store raw reads
    uint8_t data[6];
    
    // Read device ID to make sure that we can communicate with the device
    BNO055_state =  default_i2c_reg_read(BNO055_ADDR, BNO055_CHIP_ID_ADDR, data, 1);

    if (data[0] != BNO055_CHIP_ID) {
        if(BNODEBUG) printf("ERROR: Could not communicate with BNO055\r\n");
        if(BNODEBUG) printf("Data read: %x\r\n", data[0]);
    }else{
        if(BNODEBUG) printf("Found device with device id %x\n", BNO055_CHIP_ID);

    }

    return BNO055_state;
}

BNO055_state_e BNO055_set_reg_page(uint8_t page){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_PAGE_ID_ADDR, &page, 1);

    return BNO055_state;

}

BNO055_state_e BNO055_set_to_config_mode(){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    uint8_t  page   = 0;
    BNO055_state       = BNO055_set_reg_page(page);

    // set to configuration mode
    operation_mode_t config_mode = config;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_OPR_MODE_ADDR, &config_mode, 1);
    /* --------------------------------------------------------- *
    * switch time: any->config needs 7ms + small buffer = 10ms  *
    * --------------------------------------------------------- */
    sleep_ms(10);

    return BNO055_state;
}

BNO055_state_e BNO055_print_operation_mode(){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;
    uint8_t operation_mode = 0;
    uint8_t data[6];
    
    // read operation mode
    BNO055_state =  default_i2c_reg_read(BNO055_ADDR, BNO055_OPR_MODE_ADDR, data, 1);

    // operation mode lies in the 4 lower bits
    operation_mode = data[0] & 0x0F;

    if (BNO055_state != I2C_ALL_GOOD) {
        printf("ERROR: Could not communicate with BNO055\r\n");
        printf("BNO055_state returned: %x\r\n", BNO055_state);
    }else{
        printf("BNO055_get_operation_mode returned %x\n", operation_mode);
    }
}

BNO055_state_e BNO055_set_operation_mode(operation_mode_t newmode){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // set requested mode
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_OPR_MODE_ADDR, &newmode, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    return BNO055_state;
}

BNO055_state_e BNO055_set_power_mode(power_mode_t newmode){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // set requested mode
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_PWR_MODE_ADDR, &newmode, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    return BNO055_state;
}


BNO055_state_e BNO055_enable_any_motion_intr(uint8_t threshold, uint8_t duration){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);

    // SET DURATION
    // 4.4.11 ACC_INT_Settings 0x12
    // Any motion interrupt triggers if [AM_DUR<1:0>+1] consecutive data points are above the any
    // motion interrupt threshold define in ACC_AM_THRES register
    // get current register
    uint8_t reg = 0;
    BNO055_state = default_i2c_reg_read(BNO055_ADDR,  BNO055_ACC_INT_Settings_ADDR, &reg , 1);

    // add desired duration into last two bits
    reg = value_into_reg(duration, reg, BNO055_ACC_INT_Settings_AM_DUR_MSK, BNO055_ACC_INT_Settings_AM_DUR_POS);
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACC_INT_Settings_ADDR, &reg, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    // SET THRESHOLD
    // 4.4.10 ACC_AM_THRES 0x11
    // Threshold used for the any-motion interrupt. The threshold value is dependent on the
    // accelerometer range selected in the ACC_Config register.
    // Default value in the the ACC_Config register is 2-g range
    //
    //    1 LSB = 3.91 mg (2-g range)
    //    1 LSB = 7.81 mg (4-g range)
    //    1 LSB = 15.63 mg (8-g range)
    //    1 LSB = 31.25 mg (16-g range)
    //
    //    can write full byte
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACC_AM_THRES_ADDR, &threshold, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    // ENABLE
    // 4.4.9 INT_EN 0x10
    // Holds all enable bits for all possoble interrupts
    // ACC_AM is on bit 6
    // Enable and disable of Accelerometer any motion interrupt
    // Read:    1: Enabled / 0: Disabled
    // Write:   1: Enable / 0: Disable interrupt
    // get current register
    BNO055_state = default_i2c_reg_read(BNO055_ADDR,  BNO055_INT_EN_ADDR, &reg , 1);

    // add desired value into bit 6
    // 1 for ENABLE
    reg = value_into_reg(ENABLE, reg, BNO055_INT_EN_ACC_AM_MSK, BNO055_INT_EN_ACC_AM_POS);
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACC_INT_Settings_ADDR, &reg, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    // SET MASK
    // 4.4.8 INT_MSK 0x0F
    // Masking of Accelerometer any motion interrupt, when enabled the interrupt will update the
    // INT_STA register and trigger a change on the INT pin, when disabled only the INT_STA register
    // will be updated.
    // Read:    1: Enabled / 0: Disabled
    // Write:   1: Enable / 0: Disable
    // get current register
    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_INT_MSK_ADDR, &reg , 1);

    // add desired value into bit 6
    // 1 for ENABLE
    reg = value_into_reg(ENABLE, reg, BNO055_INT_MSK_ACC_AM_MSK, BNO055_INT_MSK_ACC_AM_POS);
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_INT_MSK_ADDR, &reg, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    // go back to fusion mode
    operation_mode_t mode_imu = imu;
    BNO055_state = BNO055_set_operation_mode(mode_imu);

    if(BNODEBUG) printf("BNO055 ACC AM Interrupt set.\n");

    return BNO055_state;
}

BNO055_state_e BNO055_enable_intr_on_XYZ(uint8_t x, uint8_t y, uint8_t z){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);

    // SET DURATION
    // 4.4.11 ACC_INT_Settings 0x12
    // X axis: bit 2, Y axis: bit 3, Z axis: bit 4
    // Select which axis of the accelerometer is used to trigger a any motion or no motion interrupt
    // for every bit  1: Enabled; 0: Disabled
    // get current register
    uint8_t reg = 0;
    BNO055_state = default_i2c_reg_read(BNO055_ADDR,  BNO055_ACC_INT_Settings_ADDR, &reg , 1);

    // Set the flags as requested--binary choice, so set or unset
    reg = value_into_reg(x, reg, BNO055_ACC_INT_Settings_ACC_X_MSK, BNO055_ACC_INT_Settings_ACC_X_POS);
    reg = value_into_reg(y, reg, BNO055_ACC_INT_Settings_ACC_Y_MSK, BNO055_ACC_INT_Settings_ACC_Y_POS);
    reg = value_into_reg(z, reg, BNO055_ACC_INT_Settings_ACC_Z_MSK, BNO055_ACC_INT_Settings_ACC_Z_POS);
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACC_INT_Settings_ADDR, &reg, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    if(BNODEBUG) printf("BNO055 enabled interrupt on axis X: %d, Y: %d, Z: %d.\n", x, y, z);

    // go back to fprevious mode
    operation_mode_t mode_imu = imu;
    BNO055_state = BNO055_set_operation_mode(mode_imu);

    return BNO055_state;
}

BNO055_state_e BNO055_clear_intr(void){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    //// set to configuration mode
    //BNO055_state = BNO055_set_to_config_mode();
//
    //// set registry page 1
    //BNO055_state =  BNO055_set_reg_page(1);
//
    //// SET DURATION
    //// 4.4.11 ACC_INT_Settings 0x12
    //// X axis: bit 2, Y axis: bit 3, Z axis: bit 4
    //// Select which axis of the accelerometer is used to trigger a any motion or no motion interrupt
    //// for every bit  1: Enabled; 0: Disabled
    //// get current register
    //uint8_t reg = 0;
    //BNO055_state = default_i2c_reg_read(BNO055_ADDR,  BNO055_ACC_INT_Settings_ADDR, &reg , 1);
//
    //// Set the flags as requested--binary choice, so set or unset
    //reg = value_into_reg(x, reg, BNO055_ACC_INT_Settings_ACC_X_MSK, BNO055_ACC_INT_Settings_ACC_X_POS);
    //reg = value_into_reg(y, reg, BNO055_ACC_INT_Settings_ACC_Y_MSK, BNO055_ACC_INT_Settings_ACC_Y_POS);
    //reg = value_into_reg(z, reg, BNO055_ACC_INT_Settings_ACC_Z_MSK, BNO055_ACC_INT_Settings_ACC_Z_POS);
    //BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACC_INT_Settings_ADDR, &reg, 1);
    ///* --------------------------------------------------------- *
    // * switch time: config->any needs 19ms + small buffer = 25ms *
    // * --------------------------------------------------------- */
    //sleep_ms(25);
//
    //printf("BNO055 enabled interrupt on axis X: %d, Y: %d, Z: %d.\n", x, y, z);
//
    //// go back to fusion mode
    //operation_mode_t mode_imu = amg;
    //BNO055_state = BNO055_set_operation_mode(mode_imu);
//
    //return BNO055_state;
}

BNO055_state_e BNO055_reset_system(void){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);

    // SYSTEM RESET
    // 4.3.63 SYS_TRIGGER 0x3F
    // bit 5: RST_SYS Set to reset system
    uint8_t reg = 0x00;
    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_SYS_TRIGGER_ADDR, &reg, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    if(BNODEBUG) printf("BNO055 triggered system reset.\n");

    return BNO055_state;
}

BNO055_state_e BNO055_set_offsets(BNO055_offsets_t* pt_BNO055_offsets){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(1);

    // maybe doing this in the worst possible way
    uint8_t reg = 0;
    // ACC
    //4.3.86 ACC_OFFSET_X_MSB 0x56 ff
    reg = (pt_BNO055_offsets->accel_offset_x) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACCEL_OFFSET_X_LSB_ADDR, &reg, 1);
    // 4.3.87 ACC_OFFSET_Y_LSB 0x57 ff
    reg = (pt_BNO055_offsets->accel_offset_x >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACCEL_OFFSET_X_MSB_ADDR, &reg, 1);

    reg = pt_BNO055_offsets->accel_offset_y & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACCEL_OFFSET_Y_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->accel_offset_y >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACCEL_OFFSET_Y_MSB_ADDR, &reg, 1);

    reg = pt_BNO055_offsets->accel_offset_z & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACCEL_OFFSET_Z_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->accel_offset_z >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_ACCEL_OFFSET_Z_MSB_ADDR, &reg, 1);

    // GYRO
    reg = pt_BNO055_offsets->gyro_offset_x & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_GYRO_OFFSET_X_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->gyro_offset_x >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_GYRO_OFFSET_X_MSB_ADDR, &reg, 1);

    reg = pt_BNO055_offsets->gyro_offset_y & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_GYRO_OFFSET_Y_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->gyro_offset_y >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_GYRO_OFFSET_Y_MSB_ADDR, &reg, 1);

    reg = pt_BNO055_offsets->gyro_offset_z & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_GYRO_OFFSET_Z_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->gyro_offset_z >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_GYRO_OFFSET_Z_MSB_ADDR, &reg, 1);

    // MAG
    reg = pt_BNO055_offsets->mag_offset_x & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_MAG_OFFSET_X_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->mag_offset_x >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_MAG_OFFSET_X_MSB_ADDR, &reg, 1);

    reg = pt_BNO055_offsets->mag_offset_y & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_MAG_OFFSET_Y_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->mag_offset_y >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_MAG_OFFSET_Y_MSB_ADDR, &reg, 1);

    reg = pt_BNO055_offsets->mag_offset_z & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_MAG_OFFSET_Z_LSB_ADDR, &reg, 1);
    reg = (pt_BNO055_offsets->mag_offset_z >> 8) & 0x0FF;
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_MAG_OFFSET_Z_MSB_ADDR, &reg, 1);

    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    // go back to fprevious mode
    operation_mode_t mode_imu = acconly;
    BNO055_state = BNO055_set_operation_mode(mode_imu);

    if(BNODEBUG) printf("BNO055 set offsets.\n");

    return BNO055_state;
}

BNO055_state_e BNO055_read_SYS_STATUS(void){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);

    // SYSTEM RESET
    // 4.3.58 SYS_STATUS 0x39
    uint8_t reg = 0x00;
    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_SYS_TRIGGER_ADDR, &reg, 1);

    if(BNODEBUG) printf("BNO055 SYS_STATUS read: 0.%02x.\n", reg);

    return BNO055_state;
}

BNO055_state_e BNO055_read_SYS_TRIG(void){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);

    // SYSTEM RESET
    // 4.3.63 SYS_TRIGGER 0x3F
    // bit 5: RST_SYS Set to reset system
    uint8_t reg = 0;
    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_SYS_TRIGGER_ADDR, &reg, 1);


    if(BNODEBUG) printf("BNO055 SYS_TRIGGER read: 0.%02x.\n", reg);

    return BNO055_state;
}

BNO055_state_e BNO055_read_INT_STA(void){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set registry page 1
    BNO055_state =  BNO055_set_reg_page(0);

    // INTERRUPT STATUS
    // 4.3.56 INT_STA 0x37
    uint8_t reg = 0;
    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_INTR_STAT_ADDR, &reg, 1);

    if(BNODEBUG) printf("BNO055 INT_STA read: 0.%02x.\n", reg);

    reg = ((reg & BNO055_INTR_STAT_ACC_ANY_MOTION_MSK) >> BNO055_INTR_STAT_ACC_ANY_MOTION_POS);
    if(BNODEBUG) printf("BNO055 INTR_STAT_ACC_ANY read: 0.%02x.\n", reg);

    return BNO055_state;
}

BNO055_state_e BNO055_set_axis_mode(axis_placement_t req_axis_placement){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;

    // set to configuration mode
    BNO055_state = BNO055_set_to_config_mode();

    // write axis remap for requested placement
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_AXIS_REMAP_CONFIG_ADDR, &(req_axis_placement.axis_remap), 1);

    // write axis sign for requested placement
    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_AXIS_REMAP_SIGN_ADDR, &(req_axis_placement.axis_remap), 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    return BNO055_state;
}

BNO055_state_e BNO055_print_eul(euler_angles_t* ptEulAngles){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;
    uint8_t euler_angles_data[6];
    int16_t buffer = 0;

    // to get euler angles sensor needs to be in fusion mode( operation mode > 0x07) !
    // might do mode check here

    // might set unit here

    // defines the angle unit (datasheet p.35)
    // set 16.0 for degrees, 900.0 for rad/s
    float angle_unit = 900.0;                

    // read euler angle data
    BNO055_state = default_i2c_reg_read(BNO055_ADDR,  BNO055_EULER_H_LSB_ADDR, euler_angles_data, 6);

    buffer = ((uint16_t)euler_angles_data[1] << 8) | euler_angles_data[0];
    printf("Euler Orientation Heading: LSB [0x%02X] MSB [0x%02X] INT16 [%d]\n", euler_angles_data[0], euler_angles_data[1], buffer);
    ptEulAngles->eul_head = (double) buffer / angle_unit;
    printf("Euler Orientation Heading: %f\n", ptEulAngles->eul_head);

    buffer = ((int16_t)euler_angles_data[3] << 8) | euler_angles_data[2];
    printf("Euler Orientation Roll: LSB [0x%02X] MSB [0x%02X] INT16 [%d]\n", euler_angles_data[2], euler_angles_data[3], buffer);
    ptEulAngles->eul_roll = (double) buffer / angle_unit;
    printf("Euler Orientation Roll: %f\n", ptEulAngles->eul_roll);

    buffer = ((int16_t)euler_angles_data[5] << 8) | euler_angles_data[4];
    printf("Euler Orientation Pitch: LSB [0x%02X] MSB [0x%02X] INT16 [%d]\n", euler_angles_data[4], euler_angles_data[5], buffer);
    ptEulAngles->eul_pitch = (double) buffer / angle_unit;
    printf("Euler Orientation Pitch: %f\n", ptEulAngles->eul_pitch);

    return BNO055_state;

}

BNO055_state_e BNO055_get_acc_xyz(){

    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;
    uint8_t acc_data[2] = {0, 0};
    int16_t acc_buff = 0;

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_ACC_DATA_X_LSB_ADDR, acc_data, 2);

    acc_data[0] = ((acc_data[0] & 0xFF) >> 0);
    acc_data[1] = ((acc_data[1] & 0xFF) >> 0);

    //printf("ACC X LSB: 0x%02X\n", acc_data[0]);
    //printf("ACC X MSB: 0x%02X\n", acc_data[1]);

    acc_buff = ((int16_t) ((acc_data[0] << 8)| acc_data[1]));
    
    printf("acc_buff_x: %d\n", acc_buff);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_ACC_DATA_Y_LSB_ADDR, acc_data, 2);

    acc_data[0] = ((acc_data[0] & 0xFF) >> 0);
    acc_data[1] = ((acc_data[1] & 0xFF) >> 0);

    //printf("ACC Y LSB: 0x%02X\n", acc_data[0]);
    //printf("ACC Y MSB: 0x%02X\n", acc_data[1]);

    acc_buff = ((int16_t) ((acc_data[0] << 8)| acc_data[1]));
    
    //printf("acc_buff_y: %d\n", acc_buff);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_ACC_DATA_Z_LSB_ADDR, acc_data, 2);

    acc_data[0] = ((acc_data[0] & 0xFF) >> 0);
    acc_data[1] = ((acc_data[1] & 0xFF) >> 0);

    //printf("ACC Z LSB: 0x%02X\n", acc_data[0]);
    //printf("ACC Z MSB: 0x%02X\n", acc_data[1]);

    acc_buff = ((int16_t) ((acc_data[0] << 8)| acc_data[1]));
    
    //printf("acc_buff_z: %d\n", acc_buff);

    return BNO055_state;
}

BNO055_state_e BNO055_get_mag_xyz(){
    
    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;
    uint8_t mag_data[2] = {0, 0};
    int16_t mag_buff = 0;

    // defines the angle unit (datasheet p.35)
    // set 16.0 for degrees, 900.0 for rad/s
    float angle_unit = 900.0;

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_X_LSB_ADDR, mag_data, 2);

    mag_data[0] = ((mag_data[0] & 0xFF) >> 0);
    mag_data[1] = ((mag_data[1] & 0xFF) >> 0);

    printf("MAG X LSB: 0x%02X\n", mag_data[0]);
    printf("MAG X MSB: 0x%02X\n", mag_data[1]);

    mag_buff = ((int16_t) ((mag_data[0] << 8)| mag_data[1]));
    
    printf("mag_buff_x: %d\n", mag_buff);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_MAG_DATA_Y_LSB_ADDR, mag_data, 2);

    mag_data[0] = ((mag_data[0] & 0xFF) >> 0);
    mag_data[1] = ((mag_data[1] & 0xFF) >> 0);

    printf("MAG Y LSB: 0x%02X\n", mag_data[0]);
    printf("MAG Y MSB: 0x%02X\n", mag_data[1]);

    mag_buff = ((int16_t) ((mag_data[0] << 8)| mag_data[1]));
    
    printf("mag_buff_y: %d\n", mag_buff);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_MAG_DATA_Z_LSB_ADDR, mag_data, 2);

    mag_data[0] = ((mag_data[0] & 0xFF) >> 0);
    mag_data[1] = ((mag_data[1] & 0xFF) >> 0);

    printf("MAG Z LSB: 0x%02X\n", mag_data[0]);
    printf("MAG Z MSB: 0x%02X\n", mag_data[1]);

    mag_buff = ((int16_t) ((mag_data[0] << 8)| mag_data[1]));
    
    printf("mag_buff_z: %d\n", mag_buff);

    return BNO055_state;
}

BNO055_state_e BNO055_get_gyro_xyz(){
    
    BNO055_state_e BNO055_state = BNO055_WRITE_ERROR;
    uint8_t gyro_data[2] = {0, 0};
    int16_t gyro_buff = 0;

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_X_LSB_ADDR, gyro_data, 2);

    gyro_data[0] = ((gyro_data[0] & 0xFF) >> 0);
    gyro_data[1] = ((gyro_data[1] & 0xFF) >> 0);

    printf("GYRO X LSB: 0x%02X\n", gyro_data[0]);
    printf("GYRO X MSB: 0x%02X\n", gyro_data[1]);

    gyro_buff = ((int16_t) ((gyro_data[0] << 8)| gyro_data[1]));
    
    printf("gyro_buff_x: %d\n", gyro_buff);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_Y_LSB_ADDR, gyro_data, 2);

    gyro_data[0] = ((gyro_data[0] & 0xFF) >> 0);
    gyro_data[1] = ((gyro_data[1] & 0xFF) >> 0);

    printf("GYRO Y LSB: 0x%02X\n", gyro_data[0]);
    printf("GYRO Y MSB: 0x%02X\n", gyro_data[1]);

    gyro_buff = ((int16_t) ((gyro_data[0] << 8)| gyro_data[1]));
    
    printf("gyro_buff_y: %d\n", gyro_buff);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_Z_LSB_ADDR, gyro_data, 2);

    gyro_data[0] = ((gyro_data[0] & 0xFF) >> 0);
    gyro_data[1] = ((gyro_data[1] & 0xFF) >> 0);

    printf("GYRO Z LSB: 0x%02X\n", gyro_data[0]);
    printf("GYRO Z MSB: 0x%02X\n", gyro_data[1]);

    gyro_buff = ((int16_t) ((gyro_data[0] << 8)| gyro_data[1]));
    
    printf("gyro_buff_z: %d\n", gyro_buff);

    return BNO055_state;
}

BNO055_state_e BNO055_get_calib_status(){

    BNO055_state_e BNO055_state   = BNO055_WRITE_ERROR;
    uint8_t calib_data      = 0;
    
    int8_t sys_calib_status = 0;
    int8_t gyr_calib_status = 0;
    int8_t acc_calib_status = 0;
    int8_t mag_calib_status = 0;

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_CALIB_STAT_ADDR, &calib_data, 1);

    // bits 7,6,
    sys_calib_status = (calib_data & 0xC0);
    // bits 5,4
    gyr_calib_status = (calib_data & 0x30);
    // bits 3,2
    acc_calib_status = (calib_data & 0x0C);
    // bits 1,0
    mag_calib_status = (calib_data & 0x03);

    printf("sys_calib_status =  0x%02X\n", sys_calib_status);
    printf("gyr_calib_status =  0x%02X\n", gyr_calib_status);
    printf("acc_calib_status =  0x%02X\n", acc_calib_status);
    printf("mag_calib_status =  0x%02X\n", mag_calib_status);

    return BNO055_state;
}

BNO055_state_e BNO055_start_selftest(){

    // device supports Built-In Self-Test (BIST)
    // see datasheet 3.9.2 Built-In Self-Test (BIST)
    
    BNO055_state_e BNO055_state   = BNO055_WRITE_ERROR;
    uint8_t selftest        = 0x01;
    uint8_t sysError        = 0xFF;


    BNO055_state = default_i2c_reg_write(BNO055_ADDR, BNO055_SYS_TRIGGER_ADDR, &selftest, 1);
    printf("Triggered selftest...\n");

    sleep_ms(400);

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_SYS_ERROR_ADDR, &sysError, 1);

    if (sysError == 0)
    {
        printf("Selftest was successfull!\n");
    }else{
        BNO055_state = BNO055_selftest_results();
    }

    return BNO055_state;
}

BNO055_state_e BNO055_selftest_results(){
    
    BNO055_state_e BNO055_state   = BNO055_WRITE_ERROR;
    uint8_t st_results      = 0;
    
    uint8_t mcu_st_results = 0;
    uint8_t gyr_st_results = 0;
    uint8_t acc_st_results = 0;
    uint8_t mag_st_results = 0;

    BNO055_state = default_i2c_reg_read(BNO055_ADDR, BNO055_CALIB_STAT_ADDR, &st_results, 1);

    // bit 3
    mcu_st_results = (st_results  & 0x07);
    // bit 2
    gyr_st_results = (st_results  & 0x03);
    // bit 1
    acc_st_results = (st_results  & 0x02);
    // bit 0
    mag_st_results = (st_results  & 0x01);

    printf("mcu_st_results =  0x%02X\n", mcu_st_results);
    printf("gyr_st_results =  0x%02X\n", gyr_st_results);
    printf("acc_st_results =  0x%02X\n", acc_st_results);
    printf("mag_st_results =  0x%02X\n", mag_st_results);

    return BNO055_state;
}


static inline uint8_t value_into_reg(uint8_t value, uint8_t reg, uint8_t mask, uint8_t position) {
    return (reg & ~mask) | ((value << position) & mask);
}
