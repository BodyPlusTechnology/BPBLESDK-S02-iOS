# 1.0.3 

1. Update SN-Code filter for support iOS13.
2. Update DFUConfig method.


# 1.0.2 

1. Add `BPBLEManagerS02+Config.h` to help check defice if need to firmware upgrade.

# 1.0.1 

1. Start monintoring HeartRate and BreathRate may be failed when Core is Isolating.

# 1.0.0 

1. DFU Devices Detect.
2. Connect a DFU Device can continue Upgrading.
3. Add Manufacturer Filter within scanning method.

# 0.0.8

1. Add Erase current offline data API
2. After sync offline data, if HR array's length not equal BR array's length, then the short array will filling data with last value;


# 0.0.7

1. Remove check DFU version in the unzipped package.

# 0.0.6

1. Fixed DFU permission check error.
2. Support ZF's BLE Devices.
3. Support S03 BLE Devices.
4. Add a manufacturer filter func within scanning.

# 0.0.5

1. Get core's version auto set the display version property.
2. Core's position change will reset the monitor state.


# 0.0.4

Build in Xcode10.2 (Swift4.2)