/**
 * Status values for FTDI devices
 */
export const enum FT_STATUS {
    /**
     * Status OK
     */
    FT_OK= 0,
    /**
     * The device handle is invalid
     */
    FT_INVALID_HANDLE= 1,
    /**
     * Device not found
     */
    FT_DEVICE_NOT_FOUND= 2,
    /**
     * Device is not open
     */
    FT_DEVICE_NOT_OPENED= 3,
    /**
     * IO error
     */
    FT_IO_ERROR= 4,
    /**
     * Insufficient resources
     */
    FT_INSUFFICIENT_RESOURCES= 5,
    /**
     * A parameter was invalid
     */
    FT_INVALID_PARAMETER= 6,
    /**
     * The requested baud rate is invalid
     */
    FT_INVALID_BAUD_RATE= 7,
    /**
     * Device not opened for erase
     */
    FT_DEVICE_NOT_OPENED_FOR_ERASE= 8,
    /**
     * Device not poened for write
     */
    FT_DEVICE_NOT_OPENED_FOR_WRITE= 9,
    /**
     * Failed to write to device
     */
    FT_FAILED_TO_WRITE_DEVICE= 10,
    /**
     * Failed to read the device EEPROM
     */
    FT_EEPROM_READ_FAILED= 11,
    /**
     * Failed to write the device EEPROM
     */
    FT_EEPROM_WRITE_FAILED= 12,
    /**
     * Failed to erase the device EEPROM
     */
    FT_EEPROM_ERASE_FAILED= 13,
    /**
     * An EEPROM is not fitted to the device
     */
    FT_EEPROM_NOT_PRESENT= 14,
    /**
     * Device EEPROM is blank
     */
    FT_EEPROM_NOT_PROGRAMMED= 15,
    /**
     * Invalid arguments
     */
    FT_INVALID_ARGS= 16,
    /**
     * An other error has occurred
     */
    FT_OTHER_ERROR= 17,
  }

/**
 * Flags that provide information on the FTDI device state
 */
export const enum FT_FLAGS {
    /**
     * Indicates that the device is open
     */
    FT_FLAGS_OPENED = 0x00000001,
    /**
     * Indicates that the device is enumerated as a hi-speed USB device
     */
    FT_FLAGS_HISPEED = 0x00000002,
  }

/**
 * Device type identifiers for FT_GetDeviceInfoDetail and FT_GetDeviceInfo
 */
export const enum FT_DEVICE {
    /**
     * FT232B or FT245B device
     */
    FT_DEVICE_BM = 0,
    /**
     * FT8U232AM or FT8U245AM device
     */
    FT_DEVICE_AM = 1,
    /**
     * FT8U100AX device
     */
    FT_DEVICE_100AX= 2,
    /**
     * Unknown device
     */
    FT_DEVICE_UNKNOWN= 3,
    /**
     * FT2232 device
     */
    FT_DEVICE_2232= 4,
    /**
     * FT232R or FT245R device
     */
    FT_DEVICE_232R= 5,
    /**
     * FT2232H device
     */
    FT_DEVICE_2232H= 6,
    /**
     * FT4232H device
     */
    FT_DEVICE_4232H= 7,
    /**
     * FT232H device
     */
    FT_DEVICE_232H= 8,
    /**
     * FT X-Series device
     */
    FT_DEVICE_X_SERIES= 9,
    /**
     * FT4222 hi-speed device Mode 0 - 2 interfaces
     */
    FT_DEVICE_4222H_0= 10,
    /**
     * FT4222 hi-speed device Mode 1 or 2 - 4 interfacesef
     */
    FT_DEVICE_4222H_1_2= 11,
    /**
     * FT4222 hi-speed device Mode 3 - 1 interface
     */
    FT_DEVICE_4222H_3= 12,
    /**
     * OTP programmer board for the FT4222
     */
    FT_DEVICE_4222_PROG= 13,
  }

/**
 * Type that holds device information for GetDeviceInfoDetail method
 */
export type DeviceInfoNode = {
    /**
     * Indicates device state.
     * Can be any combination of the following: FT_FLAGS.FT_FLAGS_OPENED, FT_FLAGS.FT_FLAGS_HISPEED
     */
    readonly flags: FT_FLAGS;
    /**
     * Indicates the device type.
     * Can be one of the following: FT_DEVICE_232R, FT_DEVICE_2232C, FT_DEVICE_BM, FT_DEVICE_AM,
     * FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
     */
    readonly type: FT_DEVICE;
    /**
     * The Vendor ID and Product ID of the device
     */
    readonly id: number;
    /**
     * The Vendor ID and Product ID of the device
     */
    readonly locId: number;
    /**
     * The device serial number
     */
    readonly serialNumber: string;
    /**
     * The device description
     */
    readonly description: string;
    /**
     * This value is not used externally and is provided for information only.
     * If the device is not open, ftHandle is undefined
     */
    readonly ftHandle?: object;

 };

export interface IFtResult {
    /**
     * Value from FTDI native call
     */
    readonly ftStatus: FT_STATUS;
}

export interface IGetNumberOfDevicesResult extends IFtResult {
    /**
     * The number of FTDI devices available
     */
    readonly devCount: number;
}

export interface IGetDeviceListResult extends IFtResult {
    deviceInfoNodeList: DeviceInfoNode[];
}

export class FTDI {
    /**
     * Synchronously gets the number of FTDI devices available
     */
    public static getNumberOfDevicesSync(): IGetNumberOfDevicesResult;
    /**
     * Asynchronously gets the number of FTDI devices available
     */
    public static getNumberOfDevices(): Promise<IGetNumberOfDevicesResult>;
    /**
     * Synchronously gets information on all of the FTDI devices available
     */
    public static getDeviceListSync(): IGetDeviceListResult;
    /**
     * Asynchronously gets information on all of the FTDI devices available
     */
    public static getDeviceList(): Promise<IGetDeviceListResult>;
    /**
     * Synchronously opens the FTDI device with the specified index.
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param index
     * @returns Status values for FTDI device
     */
    public openByIndexSync(index: number): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified index.
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param index
     * @returns Status values for FTDI device
     */
    public openByIndex(index: number): Promise<FT_STATUS>;

    public close(...args: any[]): void;

    public closeSync(...args: any[]): void;

    public getDeviceInfo(...args: any[]): void;

    public getDeviceInfoSync(...args: any[]): void;

    public getQueueStatus(...args: any[]): void;

    public getQueueStatusSync(...args: any[]): void;

    public getStatus(...args: any[]): void;

    public getStatusSync(...args: any[]): void;

    public openByDescription(...args: any[]): void;

    public openByDescriptionSync(...args: any[]): void;

    public openByLocation(...args: any[]): void;

    public openByLocationSync(...args: any[]): void;

    public openBySerialNumber(...args: any[]): void;

    public openBySerialNumberSync(...args: any[]): void;

    public read(...args: any[]): void;

    public readFT232HEEPROM(...args: any[]): void;

    public readFT232HEEPROMSync(...args: any[]): void;

    public readSync(...args: any[]): void;

    public setBaudRate(...args: any[]): void;

    public setBaudRateSync(...args: any[]): void;

    public setDataCharacteristics(...args: any[]): void;

    public setDataCharacteristicsSync(...args: any[]): void;

    public setFlowControl(...args: any[]): void;

    public setFlowControlSync(...args: any[]): void;

    public write(...args: any[]): void;

    public writeSync(...args: any[]): void;

}

export const FT_232H_CBUS_OPTIONS: {
    FT_CBUS_CLK15: number;
    FT_CBUS_CLK30: number;
    FT_CBUS_CLK7_5: number;
    FT_CBUS_DRIVE_0: number;
    FT_CBUS_DRIVE_1: number;
    FT_CBUS_IOMODE: number;
    FT_CBUS_PWREN: number;
    FT_CBUS_RXLED: number;
    FT_CBUS_SLEEP: number;
    FT_CBUS_TRISTATE: number;
    FT_CBUS_TXDEN: number;
    FT_CBUS_TXLED: number;
    FT_CBUS_TXRXLED: number;
};

export const FT_DATA_BITS: {
    FT_BITS_7: number;
    FT_BITS_8: number;
};

export const FT_DRIVE_CURRENT: {
    FT_DRIVE_CURRENT_12MA: number;
    FT_DRIVE_CURRENT_16MA: number;
    FT_DRIVE_CURRENT_4MA: number;
    FT_DRIVE_CURRENT_8MA: number;
};

export const FT_FLOW_CONTROL: {
    FT_FLOW_DTR_DSR: number;
    FT_FLOW_NONE: number;
    FT_FLOW_RTS_CTS: number;
    FT_FLOW_XON_XOFF: number;
};

export const FT_PARITY: {
    FT_PARITY_EVEN: number;
    FT_PARITY_MARK: number;
    FT_PARITY_NONE: number;
    FT_PARITY_ODD: number;
    FT_PARITY_SPACE: number;
};

export const FT_STOP_BITS: {
    FT_STOP_BITS_1: number;
    FT_STOP_BITS_2: number;
};
