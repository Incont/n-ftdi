'use strict';
const _ftdi = require('bindings')('addon');

/**
 * Status values for FTDI devices
 * @enum {Number}
 */
const FT_STATUS = {
    /**
     * Status OK
     * @type {Number}
     */
    FT_OK: 0,
    /**
     * The device handle is invalid
     * @type {Number}
     */
    FT_INVALID_HANDLE: 1,
    /**
     * Device not found
     * @type {Number}
     */
    FT_DEVICE_NOT_FOUND: 2,
    /**
     * Device is not open
     * @type {Number}
     */
    FT_DEVICE_NOT_OPENED: 3,
    /**
     * IO error
     * @type {Number}
     */
    FT_IO_ERROR: 4,
    /**
     * Insufficient resources
     * @type {Number}
     */
    FT_INSUFFICIENT_RESOURCES: 5,
    /**
     * A parameter was invalid
     * @type {Number}
     */
    FT_INVALID_PARAMETER: 6,
    /**
     * The requested baud rate is invalid
     * @type {Number}
     */
    FT_INVALID_BAUD_RATE: 7,
    /**
     * Device not opened for erase
     * @type {Number}
     */
    FT_DEVICE_NOT_OPENED_FOR_ERASE: 8,
    /**
     * Device not poened for write
     * @type {Number}
     */
    FT_DEVICE_NOT_OPENED_FOR_WRITE: 9,
    /**
     * Failed to write to device
     * @type {Number}
     */
    FT_FAILED_TO_WRITE_DEVICE: 10,
    /**
     * Failed to read the device EEPROM
     * @type {Number}
     */
    FT_EEPROM_READ_FAILED: 11,
    /**
     * Failed to write the device EEPROM
     * @type {Number}
     */
    FT_EEPROM_WRITE_FAILED: 12,
    /**
     * Failed to erase the device EEPROM
     * @type {Number}
     */
    FT_EEPROM_ERASE_FAILED: 13,
    /**
     * An EEPROM is not fitted to the device
     * @type {Number}
     */
    FT_EEPROM_NOT_PRESENT: 14,
    /**
     * Device EEPROM is blank
     * @type {Number}
     */
    FT_EEPROM_NOT_PROGRAMMED: 15,
    /**
     * Invalid arguments
     * @type {Number}
     */
    FT_INVALID_ARGS: 16,
    /**
     * An other error has occurred
     * @type {Number}
     */
    FT_OTHER_ERROR: 17
};
Object.freeze(FT_STATUS);

/**
 * Device type identifiers for FT_GetDeviceInfoDetail and FT_GetDeviceInfo
 * @enum {Number}
 */
const FT_DEVICE = {
    /**
     * FT232B or FT245B device
     * @type {Number}
     */
    FT_DEVICE_BM: 0,
    /**
     * FT8U232AM or FT8U245AM device
     * @type {Number}
     */
    FT_DEVICE_AM: 1,
    /**
     * FT8U100AX device
     * @type {Number}
     */
    FT_DEVICE_100AX: 2,
    /**
     * Unknown device
     * @type {Number}
     */
    FT_DEVICE_UNKNOWN: 3,
    /**
     * FT2232 device
     * @type {Number}
     */
    FT_DEVICE_2232: 4,
    /**
     * FT232R or FT245R device
     * @type {Number}
     */
    FT_DEVICE_232R: 5,
    /**
     * FT2232H device
     * @type {Number}
     */
    FT_DEVICE_2232H: 6,
    /**
     * FT4232H device
     * @type {Number}
     */
    FT_DEVICE_4232H: 7,
    /**
     * FT232H device
     * @type {Number}
     */
    FT_DEVICE_232H: 8,
    /**
     * FT X-Series device
     * @type {Number}
     */
    FT_DEVICE_X_SERIES: 9,
    /**
     * FT4222 hi-speed device Mode 0 - 2 interfaces
     * @type {Number}
     */
    FT_DEVICE_4222H_0: 10,
    /**
     * FT4222 hi-speed device Mode 1 or 2 - 4 interfaces
     * @type {Number}
     */
    FT_DEVICE_4222H_1_2: 11,
    /**
     * FT4222 hi-speed device Mode 3 - 1 interface
     * @type {Number}
     */
    FT_DEVICE_4222H_3: 12,
    /**
     * OTP programmer board for the FT4222
     * @type {Number}
     */
    FT_DEVICE_4222_PROG: 13
};
Object.freeze(FT_STATUS);

/**
 * Flags that provide information on the FTDI device state
 * @enum {Number}
 */
const FT_FLAGS = {
    /**
     * Indicates that the device is open
     * @type {Number}
     */
    FT_FLAGS_OPENED: 1,
    /**
     * Indicates that the device is enumerated as a hi-speed USB device
     * @type {Number}
     */
    FT_FLAGS_HISPEED: 2
}
Object.freeze(FT_FLAGS);

class FTDI {
    /**
     * Class wrapper for FTD2XX.DLL
     * @constructor
     */
    constructor() { }

    /**
     * @typedef GetNumberOfDevicesResult
     * @type {Object}
     * @property {Number} ftStatus - value from FT_CreateDeviceInfoList
     * @property {Number} devCount - the number of FTDI devices available
     */
    /**
     * Gets the number of FTDI devices available
     * @return {GetNumberOfDevicesResult}
     */
    static getNumberOfDevices() {
        return _ftdi.createDeviceInfoList();
    }

    /**
     * The device handle
     * @typedef FtHandle
     * @type {Object}
     * @property {Number} value
     */
    /**
     * Type that holds device information for GetDeviceInformation method
     * @typedef DeviceInfo
     * @type {Object}
     * @property {Number} flags - Indicates device state. Can be any combination of the following: FT_FLAGS.FT_FLAGS_OPENED, FT_FLAGS.FT_FLAGS_HISPEED
     * @property {Number} type - Indicates the device type. Can be one of the following: FT_DEVICE_232R, FT_DEVICE_2232C, FT_DEVICE_BM, FT_DEVICE_AM, FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
     * @property {Number} id - The Vendor ID and Product ID of the device
     * @property {Number} locId - The physical location identifier of the device
     * @property {Number} serialNumber - The device serial number
     * @property {Number} description - The device description
     * @property {FtHandle} ftHandle - This value is not used externally and is provided for information only. If the device is not open, ftHandle.value is 0.
     */
    /**
     * @typedef GetDeviceListResult
     * @type {Object}
     * @property {Number} ftStatus - value from FT_GetDeviceInfoDetail
     * @property {Array.<DeviceInfo>} deviceInfoList
     */
    /**
     * Gets information on all of the FTDI devices available
     * @return { GetDeviceListResult} result.ftStatus - value from FT_CreateDeviceInfoList,
     */
    static getDeviceList() {
        let deviceInfoList = new Array();
        let { ftStatus, devCount } = this.getNumberOfDevices();
        for (let i = 0; i < devCount; ++i) {
            deviceInfoList[i] = _ftdi.getDeviceInfoDetail(i).deviceInfo;
        }
        return { ftStatus, deviceInfoList }
    }
}



module.exports = {
    FT_STATUS: FT_STATUS,
    FT_DEVICE: FT_DEVICE,
    FT_FLAGS: FT_FLAGS,
    FTDI: FTDI
}