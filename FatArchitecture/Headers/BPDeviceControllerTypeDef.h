//
//  BPDeviceControllerTypeDef.h
//  BPToolBox
//
//  Created by GrayLand on 2017/10/20.
//  Copyright © 2017年 BodyPlus. All rights reserved.
//

#ifndef BPDeviceControllerTypeDef_h
#define BPDeviceControllerTypeDef_h

// Command length
#define    BLECMD_DATA_INIT_LENGTH        1
#define    BLECMD_CMD_VN_LENGTH           1
#define    BLECMD_NORMAL_0_LENGTH         2
#define    BLECMD_TIME_LENGTH             8
#define    BLECMD_UPLOAD_DATA_LENGTH      1
#define    BLECMD_EMG_RUN_LENGTH          1
#define    BLECMD_ECG_RUN_LENGTH          1
#define    BLECMD_A3D_RUN_LENGTH          1
#define    BLECMD_A3D_CLR_LENGTH          1
#define    BLECMD_GPS_RUN_LENGTH          1
#define    BLECMD_PRES_RUN_LENGTH         1
#define    BLECMD_UPLOAD_OLDDATA_LENGTH   1
#define    BLECMD_USER_NAME_LENGTH        12
#define    BLECMD_UNAME_LENGTH_LENGTH     1
#define    BLECMD_DFU_JUMP_LENGTH         1
#define    BLECMD_LED_STOP_LENGTH         1
#define    BLECMD_LOG_LEVEL_LENGTH        1
#define    BLECMD_LOG_MODULE_LENGTH       2
#define    BLECMD_PRES_SEA_LENGTH         2
#define    BLECMD_USER_ID_LENGTH          4
#define    BLECMD_NORMAL_3_LENGTH         4
#define    BLECMD_CORE_TYPE_LENGTH        1
#define    BLECMD_PASSWORD_CHECK_LENGTH   8
#define    BLECMD_POW_STATE_LENGTH        1
#define    BLECMD_POW_LEV_LENGTH          1
#define    BLECMD_GPS_STATE_LENGTH        1
#define    BLECMD_GPS_LEV_LENGTH          1
#define    BLECMD_CORE_MODE_LENGTH        1
#define    BLECMD_NORMAL_4_LENGTH         3
#define    BLECMD_HW_VN_LENGTH            2
#define    BLECMD_SW_VN_LENGTH            2
#define    BLECMD_CORE_SN_LENGTH          10
#define    COREDATA_FLAG_SHIRT_LENGTH     1
#define    COREDATA_FLAG_PANTS_LENGTH     1
#define    BLECMD_FILT_STORE_CNT_LENGTH   1
#define    BLECMD_FILT_FISRT_JUMP_LENGTH  1
#define    BLECMD_FILT_WAVAMP_ALL_LENGTH  1
#define    BLECMD_FILT_WAVAMP_LAST_LENGTH 1
#define    ALL_BUFFER_LENGTH              82
#define    BUFFER_END_LENGTH              4


// Command Value
#define     BLECMD_DATA_INIT        0
#define     BLECMD_CMD_VN           1
#define     BLECMD_NORMAL_0         2
#define     BLECMD_TIME             4
#define     BLECMD_UPLOAD_DATA      12 // length - 1
#define     BLECMD_EMG_RUN          13 // S06 - Breath Rate
#define     BLECMD_RESP_RUN         13
#define     BLECMD_ECG_RUN          14
#define     BLECMD_A3D_RUN          15
#define     BLECMD_A3D_CLR          16
#define     BLECMD_GPS_RUN          17
#define     BLECMD_PRES_RUN         18
#define     BLECMD_UPLOAD_OLDDATA   19
#define     BLECMD_USER_NAME        20
#define     BLECMD_UNAME_LENGTH     32
#define     BLECMD_DFU_JUMP         33
#define     BLECMD_LED_STOP         34
#define     BLECMD_LOG_LEVEL        35
#define     BLECMD_LOG_MODULE       36
#define     BLECMD_PRES_SEA         38
#define     BLECMD_USER_ID          40
#define     BLECMD_NORMAL_3         44
#define     BLECMD_NORMAL_3         44
#define     BLECMD_CORE_TYPE        45
#define     BLECMD_BOOSTLOAD_VERSION 46
#define     BLECMD_PASSWORD_CHECK   48
#define     BLECMD_POW_STATE        56
#define     BLECMD_POW_LEV          57
#define     BLECMD_GPS_STATE        58
#define     BLECMD_GPS_LEV          59
#define     BLECMD_CORE_MODE        60
#define     BLECMD_NORMAL_4         61
#define     BLECMD_HW_VN            64
#define     BLECMD_SW_VN            66
#define     BLECMD_CORE_SN          68
#define     COREDATA_FLAG_SHIRT     78
#define     COREDATA_FLAG_PANTS     79
#define     BLECMD_FILT_STORE_CNT   80
#define     BLECMD_FILT_FISRT_JUMP  81
#define     BLECMD_FILT_WAVAMP_ALL  82
#define     BLECMD_FILT_WAVAMP_LAST 83
#define     ALL_BUFFER              84
#define     BLECMD_FILT_WAVAMP_ALL  82 //1
#define     BLECMD_FILT_WAVAMP_LAST 83 //1
#define     BLECMD_SLEEP_THRESHOLD  88
#define     BLECMD_SLEEP_THRESHOLD_N 92
#define     BUFFER_END              96

//Data length
#define BLE_DATA_ECG_MONITOR_LENGTH             50
#define BLE_DATA_HEART_RATE_LENGTH             1
#define BLE_DATA_RR_INTERVALS_LENGTH            1
#define BLE_DATA_HRV_RATIO_LENGTH               1
#define BLE_DATA_BREATH_RATE_LENGTH          1
#define BLE_DATA_BREATHING_INTENSITY_LENGTH     1
#define BLE_DATA_MUSCLE_MONITOR_UP_LENGTH       15
#define BLE_DATA_MUSCLE_MONITOR_DOWN_LENGTH     12
#define BLE_DATA_MUSCLE_IMBALANCE_UP_LENGTH     15
#define BLE_DATA_MUSCLE_IMBALANCE_DOWN_LENGTH   12
#define BLE_DATA_STEP_COUNTER_LENGTH            4
#define BLE_DATA_CALORIES_LENGTH                4
#define BLE_DATA_STATE_LENGTH                   4
#define BLE_DATA_GPS_LENGTH                     12
#define BLE_DATA_SPEED_LENGTH                   4
#define BLE_DATA_ALTITUDE_LENGTH                4
#define BLE_DATA_MUSCLE_CALIBRATION_UP_LENGTH   15*4
#define BLE_DATA_MUSCLE_CALIBRATION_DOWN_LENGTH 12*4

typedef NS_ENUM(NSUInteger, BPCommandPermission) {
    BPCommandPermissionRead,
    BPCommandPermissionWrite,
};

typedef NS_ENUM(NSUInteger, BPBLEDataType) {
    BPBLEDataTypeECGMonitor           = 1,///<心电监护
    BPBLEDataTypeHeartRate            = 2,///<心率
    BPBLEDataTypeRRIntervals          = 3,///<RR间期
    BPBLEDataTypeHRVRatio             = 4,///<HRV比率
    BPBLEDataTypeBreathingRate        = 5,///<呼吸率
    BPBLEDataTypeBreathingIntensity   = 6,
    BPBLEDataTypeMuscleMonitorUp      = 7,
    BPBLEDataTypeMuscleMonitorDown    = 8,
    BPBLEDataTypeMuscleImbalanceUp    = 9,
    BPBLEDataTypeMuscleImbalanceDown  = 10,
    BPBLEDataTypeStepCounter          = 11,
    BPBLEDataTypeCalories             = 12,
    BPBLEDataTypeState                = 13,
    BPBLEDataTypeGPS                  = 14,
    BPBLEDataTypeSpeed                = 15,
    BPBLEDataTypeAltitude             = 16,
    BPBLEDataTypeMuscleCalibreationUp = 17,
    BPBLEDataTypeMuscleCalibreationDown = 18,
    BPBLEDataTypeSleeStatus           = 19
};


#endif /* BPDeviceControllerTypeDef_h */
