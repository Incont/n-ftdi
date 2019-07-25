'use strict';
const _ftdi = require('bindings')('addon');

/**
 * Status values for FTDI devices
 * @enum {Number}
 */
const FT_STATUS =  {
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

for (let ftstatusKey in FT_STATUS) {
    Object.defineProperty(FT_STATUS, ftstatusKey, {
        writable: false,
        configurable: false,
    });
}

/**
 * Class wrapper for FTD2XX.DLL
 * @constructor
 */
function FTDI() {}

/**
 * Gets the number of FTDI devices available
 * @return {Object} result.ftStatus - value from FT_CreateDeviceInfoList,
 *  result.devCount - the number of FTDI devices available
 */
FTDI.prototype.getNumberOfDevices = () => _ftdi.createDeviceInfoList();

module.exports = {
    FT_STATUS: FT_STATUS,
    FTDI: FTDI,
}