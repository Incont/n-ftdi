/**
 * Status values for FTDI devices
 */
export const enum FT_STATUS {
    /**
     * Status OK
     */
    FT_OK = 0,
    /**
     * The device handle is invalid
     */
    FT_INVALID_HANDLE = 1,
    /**
     * Device not found
     */
    FT_DEVICE_NOT_FOUND = 2,
    /**
     * Device is not open
     */
    FT_DEVICE_NOT_OPENED = 3,
    /**
     * IO error
     */
    FT_IO_ERROR = 4,
    /**
     * Insufficient resources
     */
    FT_INSUFFICIENT_RESOURCES = 5,
    /**
     * A parameter was invalid
     */
    FT_INVALID_PARAMETER = 6,
    /**
     * The requested baud rate is invalid
     */
    FT_INVALID_BAUD_RATE = 7,
    /**
     * Device not opened for erase
     */
    FT_DEVICE_NOT_OPENED_FOR_ERASE = 8,
    /**
     * Device not poened for write
     */
    FT_DEVICE_NOT_OPENED_FOR_WRITE = 9,
    /**
     * Failed to write to device
     */
    FT_FAILED_TO_WRITE_DEVICE = 10,
    /**
     * Failed to read the device EEPROM
     */
    FT_EEPROM_READ_FAILED = 11,
    /**
     * Failed to write the device EEPROM
     */
    FT_EEPROM_WRITE_FAILED = 12,
    /**
     * Failed to erase the device EEPROM
     */
    FT_EEPROM_ERASE_FAILED = 13,
    /**
     * An EEPROM is not fitted to the device
     */
    FT_EEPROM_NOT_PRESENT = 14,
    /**
     * Device EEPROM is blank
     */
    FT_EEPROM_NOT_PROGRAMMED = 15,
    /**
     * Invalid arguments
     */
    FT_INVALID_ARGS = 16,
    /**
     * An other error has occurred
     */
    FT_OTHER_ERROR = 17,
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
    FT_DEVICE_100AX = 2,
    /**
     * Unknown device
     */
    FT_DEVICE_UNKNOWN = 3,
    /**
     * FT2232 device
     */
    FT_DEVICE_2232 = 4,
    /**
     * FT232R or FT245R device
     */
    FT_DEVICE_232R = 5,
    /**
     * FT2232H device
     */
    FT_DEVICE_2232H = 6,
    /**
     * FT4232H device
     */
    FT_DEVICE_4232H = 7,
    /**
     * FT232H device
     */
    FT_DEVICE_232H = 8,
    /**
     * FT X-Series device
     */
    FT_DEVICE_X_SERIES = 9,
    /**
     * FT4222 hi-speed device Mode 0 - 2 interfaces
     */
    FT_DEVICE_4222H_0 = 10,
    /**
     * FT4222 hi-speed device Mode 1 or 2 - 4 interfacesef
     */
    FT_DEVICE_4222H_1_2 = 11,
    /**
     * FT4222 hi-speed device Mode 3 - 1 interface
     */
    FT_DEVICE_4222H_3 = 12,
    /**
     * OTP programmer board for the FT4222
     */
    FT_DEVICE_4222_PROG = 13,
}

/**
 * Permitted data bits for FTDI devices
 */
export const enum FT_DATA_BITS {
    /**
     * 8 data bits
     */
    FT_BITS_8 = 0x08,
    /**
     * 7 data bits
     */
    FT_BITS_7 = 0x07,
}

/**
 * Permitted stop bits for FTDI devices
 */
export const enum FT_STOP_BITS {
    /**
     * 1 stop bit
     */
    FT_STOP_BITS_1 = 0x00,
    /**
     * 2 stop bits
     */
    FT_STOP_BITS_2 = 0x02,
}

/**
 * Permitted parity values for FTDI devices
 */
export const enum FT_PARITY {
    /**
     * No parity
     */
    FT_PARITY_NONE = 0x00,
    /**
     * Odd parity
     */
    FT_PARITY_ODD = 0x01,
    /**
     * Even parity
     */
    FT_PARITY_EVEN = 0x02,
    /**
     * Mark parity
     */
    FT_PARITY_MARK = 0x03,
    /**
     * Space parity
     */
    FT_PARITY_SPACE = 0x04,
}

/**
 * Permitted flow control values for FTDI devices
 */
export const enum FT_FLOW_CONTROL {
    /**
     * No flow control
     */
    FT_FLOW_NONE = 0x0000,
    /**
     * RTS/CTS flow control
     */
    FT_FLOW_RTS_CTS = 0x0100,
    /**
     * DTR/DSR flow control
     */
    FT_FLOW_DTR_DSR = 0x0200,
    /**
     * Xon/Xoff flow control
     */
    FT_FLOW_XON_XOFF = 0x0400,
}

/**
 * Valid values for drive current options on FT2232H, FT4232H and FT232H devices
 */
export const enum FT_DRIVE_CURRENT {
    /**
     * 4mA drive current
     */
    FT_DRIVE_CURRENT_4MA = 4,
    /**
     * 8mA drive current
     */
    FT_DRIVE_CURRENT_8MA = 8,
    /**
     * 12mA drive current
     */
    FT_DRIVE_CURRENT_12MA = 12,
    /**
     * 16mA drive current
     */
    FT_DRIVE_CURRENT_16MA = 16,
}

/**
 * Available functions for the FT232H CBUS pins. Controlled by FT232H EEPROM settings
 */
export const enum FT_232H_CBUS_OPTIONS {
    /**
     * FT232H CBUS EEPROM options - Tristate
     */
    FT_CBUS_TRISTATE = 0x00,
    /**
     * FT232H CBUS EEPROM options - Rx LED
     */
    FT_CBUS_RXLED = 0x01,
    /**
     * FT232H CBUS EEPROM options - Tx LED
     */
    FT_CBUS_TXLED = 0x02,
    /**
     * FT232H CBUS EEPROM options - Tx and Rx LED
     */
    FT_CBUS_TXRXLED = 0x03,
    /**
     * FT232H CBUS EEPROM options - Power Enable#
     */
    FT_CBUS_PWREN = 0x04,
    /**
     * FT232H CBUS EEPROM options - Sleep
     */
    FT_CBUS_SLEEP = 0x05,
    /**
     * FT232H CBUS EEPROM options - Drive pin to logic 0
     */
    FT_CBUS_DRIVE_0 = 0x06,
    /**
     * FT232H CBUS EEPROM options - Drive pin to logic 1
     */
    FT_CBUS_DRIVE_1 = 0x07,
    /**
     * FT232H CBUS EEPROM options - IO Mode
     */
    FT_CBUS_IOMODE = 0x08,
    /**
     * FT232H CBUS EEPROM options - Tx Data Enable
     */
    FT_CBUS_TXDEN = 0x09,
    /**
     * FT232H CBUS EEPROM options - 30MHz clock
     */
    FT_CBUS_CLK30 = 0x0A,
    /**
     * FT232H CBUS EEPROM options - 15MHz clock
     */
    FT_CBUS_CLK15 = 0x0B,
    /**
     * FT232H CBUS EEPROM options - 7.5MHz clock
     */
    FT_CBUS_CLK7_5 = 0x0C,
}

/**
 * Error states not supported by FTD2XX
 */
export const enum FT_ERROR {
    FT_NO_ERROR = 0,
    FT_INCORRECT_DEVICE = 1,
    FT_INVALID_BITMODE = 2,
    FT_BUFFER_SIZE = 3,
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
     * The physical location identifier of the device
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
    readonly devicelist: DeviceInfoNode[];
}
export interface IGetDeviceInfoResult extends IFtResult {
    /**
     * Indicates the device type. Can be one of the following: FT_DEVICE_232R,
     * FT_DEVICE_2232C, FT_DEVICE_BM, FT_DEVICE_AM, FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
     */
    readonly type: FT_DEVICE;
    /**
     * The device ID (Vendor ID and Product ID) of the current device
     */
    readonly id: number;
    /**
     * The device serial number
     */
    readonly serialNumber: string;
    /**
     * The device description
     */
    readonly description: string;
}

export interface IGetQueueStatusResult extends IFtResult {
    /**
     * The number of bytes available to be read
     */
    readonly rxQueue: number;
}

export interface IGetStatusResult extends IGetQueueStatusResult {
    /**
     * The number of bytes waiting to be sent
     */
    readonly txQueue: number;
    /**
     * The type of event that has occurred
     */
    readonly eventStatus: number;
}

export interface IWriteResult extends IFtResult {
    /**
     * The number of bytes actually written to the device
     */
    readonly numBytesWritten: number;
}

export interface IReadResult extends IFtResult {
    /**
     * An array of bytes which was populated with the data read from the device
     */
    readonly rxBuffer: Buffer;
    /**
     * The number of bytes actually read
     */
    readonly numBytesRead: number;
}

export interface IReadFT232HEEPROM extends IFtResult {
    /**
     * An FT232H_EEPROM_STRUCTURE which contains only the relevant information for an FT232H device
     */
    readonly ee232h: FT232H_EEPROM_STRUCTURE;
}

export class FtException extends Error {}

/**
 * Common EEPROM elements for all devices. Inherited to specific device type EEPROMs
 */
export class FT_EEPROM_DATA {
    /**
     * Vendor ID as supplied by the USB Implementers Forum. Default: 0x0403
     */
    public vendorId: number;
    /**
     * Product ID. Default: 0x6001
     */
    public productId: number;
    /**
     * Manufacturer name string. Default: 'FTDI'
     */
    public manufacturer: string;
    /**
     * Manufacturer name abbreviation to be used as a prefix for automatically
     * generated serial numbers. Default: 'FT'
     */
    public manufacturerId: string;
    /**
     * Device description string. Default: 'USB-Serial Converter'
     */
    public description: string;
    /**
     * Device serial number string. Default: ''
     */
    public serialNumber: string;
    /**
     * Maximum power the device needs. Default: 0x0090
     */
    public maxPower: number;
    /**
     * Indicates if the device has its own power supply (self-powered) or
     * gets power from the USB port (bus-powered). Default: false
     */
    public selfPowered: boolean;
    /**
     * Determines if the device can wake the host PC from
     * suspend by toggling the RI line. Default: false
     */
    public remoteWakeup: boolean;
}

/**
 * EEPROM structure specific to FT232H devices
 */
export class FT232H_EEPROM_STRUCTURE extends FT_EEPROM_DATA {
    /**
     * Determines if IOs are pulled down when the device is in suspend. Default: false
     */
    public pullDownEnable: boolean;
    /**
     * Determines if the serial number is enabled. Default: true
     */
    public serNumEnable: boolean;
    /**
     * Determines if AC pins have a slow slew rate. Default: false
     */
    public acSlowSlew: boolean;
    /**
     *  Determines if the AC pins have a Schmitt input. Default: false
     */
    public acSchmittInput: boolean;
    /**
     * Determines the AC pins drive
     * current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or
     * FT_DRIVE_CURRENT_16MA. Default: FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA
     */
    public acDriveCurrent: FT_DRIVE_CURRENT;
    /**
     * Determines if AD pins have a slow slew rate. Default: false
     */
    public adSlowSlew: boolean;
    /**
     * Determines if the AD pins have a Schmitt input. Default: false
     */
    public adSchmittInput: boolean;
    /**
     * Determines the AD pins drive
     * current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or
     * FT_DRIVE_CURRENT_16MA. Default: FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA
     */
    public adDriveCurrent: FT_DRIVE_CURRENT;
    /**
     * Sets the function of the CBUS0 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5.
     * Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus0: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS1 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5.
     * Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus1: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS2 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus2: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS3 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus3: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS4 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus4: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS5 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus5: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS6 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus6: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS7 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus7: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS8 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus8: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS9 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    public cbus9: FT_232H_CBUS_OPTIONS;
    /**
     * Determines if the device is in FIFO mode. Default: false
     */
    public isFifo: boolean;
    /**
     * Determines if the device is in FIFO target mode. Default: false
     */
    public isFifoTar: boolean;
    /**
     * Determines if the device is in fast serial mode. Default: false
     */
    public isFastSer: boolean;
    /**
     * Determines if the device is in FT1248 mode. Default: false
     */
    public isFT1248: boolean;
    /**
     * Determines FT1248 mode clock polarity. Default: false
     */
    public ft1248Cpol: boolean;
    /**
     * Determines if data is ent MSB (0) or LSB (1) in FT1248 mode. Default: false
     */
    public ft1248Lsb: boolean;
    /**
     * Determines if FT1248 mode uses flow control. Default: false
     */
    public ft1248FlowControl: boolean;
    /**
     * Determines if the VCP driver is loaded. Default: true
     */
    public isVCP: boolean;
    /**
     * For self-powered designs, keeps the FT232H in low power state until ACBUS7 is high. Default: false
     */
    public powerSaveEnable: boolean;
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
     * @param index Index of the device to open,
     * note that this cannot be guaranteed to open a specific device
     */
    public openByIndexSync(index: number): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified index.
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param index Index of the device to open,
     * note that this cannot be guaranteed to open a specific device
     */
    public openByIndex(index: number): Promise<FT_STATUS>;
    /**
     * Synchronously opens the FTDI device with the specified serial number
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param serialNumber Serial number of the device to open
     */
    public openBySerialNumberSync(serialNumber: string): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified serial number
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param serialNumber Serial number of the device to open
     */
    public openBySerialNumber(serialNumber: string): Promise<FT_STATUS>;
    /**
     * Synchronously opens the FTDI device with the specified description
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param description Description of the device to open
     */
    public openByDescriptionSync(description: string): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified description
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param description Description of the device to open
     */
    public openByDescription(description: string): Promise<FT_STATUS>;
    /**
     * Synchronously opens the FTDI device at the specified physical location
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param location Location of the device to open
     */
    public openByLocationSync(location: number): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device at the specified physical location
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param location Location of the device to open
     */
    public openByLocation(location: number): Promise<FT_STATUS>;
    /**
     * Synchronously closes the handle to an open FTDI device
     */
    public closeSync(): FT_STATUS;
    /**
     * Asynchronously closes the handle to an open FTDI device
     */
    public close(): Promise<FT_STATUS>;
    /**
     * Synchronously gets device information for an open device
     */
    public getDeviceInfoSync(): IGetDeviceListResult;
    /**
     * Asynchronously gets device information for an open device
     */
    public getDeviceInfo(): Promise<IGetDeviceListResult>;
    /**
     * Synchronously sets the data bits, stop bits and parity for the device
     * @param wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or
     * FT_DATA_BITS.FT_BITS_8
     * @param stopBits The number of stop bits for UART data.
     * Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
     * @param parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE,
     * FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
     */
    public setDataCharacteristicsSync(wordLength: FT_DATA_BITS, stopBits: FT_STOP_BITS, parity: FT_PARITY): FT_STATUS;
    /**
     * Asynchronously sets the data bits, stop bits and parity for the device
     * @param wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or
     * FT_DATA_BITS.FT_BITS_8
     * @param stopBits The number of stop bits for UART data.
     * Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
     * @param parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE,
     * FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
     */
    public setDataCharacteristics(
        wordLength: FT_DATA_BITS,
        stopBits: FT_STOP_BITS,
        parity: FT_PARITY): Promise<FT_STATUS>;
    /**
     * Synchronously sets the flow control type
     * @param flowControl The type of flow control for the UART. Valid values are
     * FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or
     * FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
     * @param xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow contro
     * @param xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
     */
    public setFlowControlSync(flowControl: FT_FLOW_CONTROL, xon: number, xoff: number): FT_STATUS;
    /**
     * Asynchronously sets the flow control type
     * @param flowControl The type of flow control for the UART. Valid values are
     * FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or
     * FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
     * @param xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow contro
     * @param xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
     */
    public setFlowControl(flowControl: FT_FLOW_CONTROL, xon: number, xoff: number): Promise<FT_STATUS>;
    /**
     * Synchronously sets the current Baud rate
     * @param baudRate The desired Baud rate for the device
     */
    public setBaudRateSync(baudRate: number): FT_STATUS;
    /**
     * Asynchronously sets the current Baud rate
     * @param baudRate The desired Baud rate for the device
     */
    public setBaudRate(baudRate: number): Promise<FT_STATUS>;
    /**
     * Synchronously gets the number of bytes available in the receive buffer
     */
    public getQueueStatusSync(): IGetQueueStatusResult;
    /**
     * Asynchronously gets the number of bytes available in the receive buffer
     */
    public getQueueStatus(): Promise<IGetQueueStatusResult>;
    /**
     * Synchronously gets the device status including number of characters in the receive queue,
     * number of characters in the transmit queue, and the current event status
     */
    public getStatusSync(): IGetStatusResult;
    /**
     * Asynchronously gets the device status including number of characters in the receive queue,
     * number of characters in the transmit queue, and the current event status
     */
    public getStatus(): Promise<IGetStatusResult>;
    /**
     * Synchronously write data to an open FTDI device
     * @param txBuffer An array of bytes which contains the data to be written to the device
     * @param numBytesToWrite The number of bytes to be written to the device. Default: txBuffer.Length
     */
    public writeSync(txBuffer: Buffer, numBytesToWrite?: number): IWriteResult;
    /**
     * Asynchronously write data to an open FTDI device
     * @param txBuffer An array of bytes which contains the data to be written to the device
     * @param numBytesToWrite The number of bytes to be written to the device. Default: txBuffer.Length
     */
    public write(txBuffer: Buffer, numBytesToWrite?: number): Promise<IWriteResult>;
    /**
     * Synchronously read data from an open FTDI device
     * @param rxBuffer An array of bytes which will be populated with the data read from the device
     * @param numBytesToRead The number of bytes requested from the device. Default: rxBuffer.Length
     */
    public readSync(rxBuffer: Buffer, numBytesToRead?: number): IReadResult;
    /**
     * Asynchronously read data from an open FTDI device
     * @param rxBuffer An array of bytes which will be populated with the data read from the device
     * @param numBytesToRead The number of bytes requested from the device. Default: rxBuffer.Length
     */
    public read(rxBuffer: Buffer, numBytesToRead?: number): Promise<IReadResult>;
    /**
     * Synchronously reads the EEPROM contents of an FT232H device
     */
    public readFT232HEEPROMSync(): IReadFT232HEEPROM;
    /**
     * Asynchronously reads the EEPROM contents of an FT232H device
     */
    public readFT232HEEPROM(): Promise<IReadFT232HEEPROM>;
}
