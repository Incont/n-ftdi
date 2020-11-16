type Enum<T> = T[keyof T];
/**
 * Status values for FTDI devices
 */
export const FT_STATUS: {
    /**
     * Status OK
     */
    readonly FT_OK: 0,
    /**
     * The device handle is invalid
     */
    readonly FT_INVALID_HANDLE: 1,
    /**
     * Device not found
     */
    readonly FT_DEVICE_NOT_FOUND: 2,
    /**
     * Device is not open
     */
    readonly FT_DEVICE_NOT_OPENED: 3,
    /**
     * IO error
     */
    readonly FT_IO_ERROR: 4,
    /**
     * Insufficient resources
     */
    readonly FT_INSUFFICIENT_RESOURCES: 5,
    /**
     * A parameter was invalid
     */
    readonly FT_INVALID_PARAMETER: 6,
    /**
     * The requested baud rate is invalid
     */
    readonly FT_INVALID_BAUD_RATE: 7,
    /**
     * Device not opened for erase
     */
    readonly FT_DEVICE_NOT_OPENED_FOR_ERASE: 8,
    /**
     * Device not poened for write
     */
    readonly FT_DEVICE_NOT_OPENED_FOR_WRITE: 9,
    /**
     * Failed to write to device
     */
    readonly FT_FAILED_TO_WRITE_DEVICE: 10,
    /**
     * Failed to read the device EEPROM
     */
    readonly FT_EEPROM_READ_FAILED: 11,
    /**
     * Failed to write the device EEPROM
     */
    readonly FT_EEPROM_WRITE_FAILED: 12,
    /**
     * Failed to erase the device EEPROM
     */
    readonly FT_EEPROM_ERASE_FAILED: 13,
    /**
     * An EEPROM is not fitted to the device
     */
    readonly FT_EEPROM_NOT_PRESENT: 14,
    /**
     * Device EEPROM is blank
     */
    readonly FT_EEPROM_NOT_PROGRAMMED: 15,
    /**
     * Invalid arguments
     */
    readonly FT_INVALID_ARGS: 16,
    /**
     * An other error has occurred
     */
    readonly FT_OTHER_ERROR: 17
};
export type FT_STATUS = Enum<typeof FT_STATUS>;

/**
 * Flags that provide information on the FTDI device state
 */
export const FT_FLAGS: {
    /**
     * Indicates that the device is open
     */
    readonly FT_FLAGS_OPENED: 0x00000001,
    /**
     * Indicates that the device is enumerated as a hi-speed USB device
     */
    readonly FT_FLAGS_HISPEED: 0x00000002,
}
export type FT_FLAGS = Enum<typeof FT_FLAGS>;

/**
 * Device type identifiers for FT_GetDeviceInfoDetail and FT_GetDeviceInfo
 */
export const FT_DEVICE: {
    /**
     * FT232B or FT245B device
     */
    readonly FT_DEVICE_BM: 0,
    /**
     * FT8U232AM or FT8U245AM device
     */
    readonly FT_DEVICE_AM: 1,
    /**
     * FT8U100AX device
     */
    readonly FT_DEVICE_100AX: 2,
    /**
     * Unknown device
     */
    readonly FT_DEVICE_UNKNOWN: 3,
    /**
     * FT2232 device
     */
    readonly FT_DEVICE_2232: 4,
    /**
     * FT232R or FT245R device
     */
    readonly FT_DEVICE_232R: 5,
    /**
     * FT2232H device
     */
    readonly FT_DEVICE_2232H: 6,
    /**
     * FT4232H device
     */
    readonly FT_DEVICE_4232H: 7,
    /**
     * FT232H device
     */
    readonly FT_DEVICE_232H: 8,
    /**
     * FT X-Series device
     */
    readonly FT_DEVICE_X_SERIES: 9,
    /**
     * FT4222 hi-speed device Mode 0 - 2 interfaces
     */
    readonly FT_DEVICE_4222H_0: 10,
    /**
     * FT4222 hi-speed device Mode 1 or 2 - 4 interfacesef
     */
    readonly FT_DEVICE_4222H_1_2: 11,
    /**
     * FT4222 hi-speed device Mode 3 - 1 interface
     */
    readonly FT_DEVICE_4222H_3: 12,
    /**
     * OTP programmer board for the FT4222
     */
    readonly FT_DEVICE_4222_PROG: 13,
}
export type FT_DEVICE = Enum<typeof FT_DEVICE>;

/**
 * Permitted data bits for FTDI devices
 */
export const FT_DATA_BITS: {
    /**
     * 8 data bits
     */
    readonly FT_BITS_8: 0x08,
    /**
     * 7 data bits
     */
    readonly FT_BITS_7: 0x07,
}
export type FT_DATA_BITS = Enum<typeof FT_DATA_BITS>;

/**
 * Permitted stop bits for FTDI devices
 */
export const FT_STOP_BITS: {
    /**
     * 1 stop bit
     */
    readonly FT_STOP_BITS_1: 0x00,
    /**
     * 2 stop bits
     */
    readonly FT_STOP_BITS_2: 0x02,
}
export type FT_STOP_BITS = Enum<typeof FT_STOP_BITS>;

/**
 * Permitted parity values for FTDI devices
 */
export const FT_PARITY: {
    /**
     * No parity
     */
    readonly FT_PARITY_NONE: 0x00,
    /**
     * Odd parity
     */
    readonly FT_PARITY_ODD: 0x01,
    /**
     * Even parity
     */
    readonly FT_PARITY_EVEN: 0x02,
    /**
     * Mark parity
     */
    readonly FT_PARITY_MARK: 0x03,
    /**
     * Space parity
     */
    readonly FT_PARITY_SPACE: 0x04,
}
export type FT_PARITY = Enum<typeof FT_PARITY>;

/**
 * Permitted flow control values for FTDI devices
 */
export const FT_FLOW_CONTROL: {
    /**
     * No flow control
     */
    readonly FT_FLOW_NONE: 0x0000,
    /**
     * RTS/CTS flow control
     */
    readonly FT_FLOW_RTS_CTS: 0x0100,
    /**
     * DTR/DSR flow control
     */
    readonly FT_FLOW_DTR_DSR: 0x0200,
    /**
     * Xon/Xoff flow control
     */
    readonly FT_FLOW_XON_XOFF: 0x0400,
}
export type FT_FLOW_CONTROL = Enum<typeof FT_FLOW_CONTROL>;

/**
 * Valid values for drive current options on FT2232H, FT4232H and FT232H devices
 */
export const FT_DRIVE_CURRENT: {
    /**
     * 4mA drive current
     */
    readonly FT_DRIVE_CURRENT_4MA: 4,
    /**
     * 8mA drive current
     */
    readonly FT_DRIVE_CURRENT_8MA: 8,
    /**
     * 12mA drive current
     */
    readonly FT_DRIVE_CURRENT_12MA: 12,
    /**
     * 16mA drive current
     */
    readonly FT_DRIVE_CURRENT_16MA: 16,
};
export type FT_DRIVE_CURRENT = Enum<typeof FT_DRIVE_CURRENT>;

/**
 * Available functions for the FT232H CBUS pins. Controlled by FT232H EEPROM settings
 */
export const FT_232H_CBUS_OPTIONS: {
    /**
     * FT232H CBUS EEPROM options - Tristate
     */
    readonly FT_CBUS_TRISTATE: 0x00,
    /**
     * FT232H CBUS EEPROM options - Rx LED
     */
    readonly FT_CBUS_RXLED: 0x01,
    /**
     * FT232H CBUS EEPROM options - Tx LED
     */
    readonly FT_CBUS_TXLED: 0x02,
    /**
     * FT232H CBUS EEPROM options - Tx and Rx LED
     */
    readonly FT_CBUS_TXRXLED: 0x03,
    /**
     * FT232H CBUS EEPROM options - Power Enable#
     */
    readonly FT_CBUS_PWREN: 0x04,
    /**
     * FT232H CBUS EEPROM options - Sleep
     */
    readonly FT_CBUS_SLEEP: 0x05,
    /**
     * FT232H CBUS EEPROM options - Drive pin to logic 0
     */
    readonly FT_CBUS_DRIVE_0: 0x06,
    /**
     * FT232H CBUS EEPROM options - Drive pin to logic 1
     */
    readonly FT_CBUS_DRIVE_1: 0x07,
    /**
     * FT232H CBUS EEPROM options - IO Mode
     */
    readonly FT_CBUS_IOMODE: 0x08,
    /**
     * FT232H CBUS EEPROM options - Tx Data Enable
     */
    readonly FT_CBUS_TXDEN: 0x09,
    /**
     * FT232H CBUS EEPROM options - 30MHz clock
     */
    readonly FT_CBUS_CLK30: 0x0A,
    /**
     * FT232H CBUS EEPROM options - 15MHz clock
     */
    readonly FT_CBUS_CLK15: 0x0B,
    /**
     * FT232H CBUS EEPROM options - 7.5MHz clock
     */
    readonly FT_CBUS_CLK7_5: 0x0C,
}
export type FT_232H_CBUS_OPTIONS = Enum<typeof FT_232H_CBUS_OPTIONS>;

/**
 * Error states not supported by FTD2XX
 */
export const FT_ERROR: {
    readonly FT_NO_ERROR: 0,
    readonly FT_INCORRECT_DEVICE: 1,
    readonly FT_INVALID_BITMODE: 2,
    readonly FT_BUFFER_SIZE: 3,
}
export type FT_ERROR = Enum<typeof FT_ERROR>;

/**
 * Available functions for the FT232R CBUS pins.  Controlled by FT232R EEPROM settings
 */
export const FT_CBUS_OPTIONS: {
    /**
     * FT232R CBUS EEPROM options - Tx Data Enable
     */
    readonly FT_CBUS_TXDEN: 0x00,
      /**
     * FT232R CBUS EEPROM options - Power On
     */
    readonly FT_CBUS_PWRON: 0x01,
      /**
     * FT232R CBUS EEPROM options - Rx LED
     */
    readonly FT_CBUS_RXLED: 0x02,
      /**
     * FT232R CBUS EEPROM options - Tx LED
     */
    readonly FT_CBUS_TXLED: 0x03,
      /**
     * FT232R CBUS EEPROM options - Tx and Rx LED
     */
    readonly FT_CBUS_TXRXLED: 0x04,
      /**
     * FT232R CBUS EEPROM options - Sleep
     */
    readonly FT_CBUS_SLEEP: 0x05,
      /**
     * FT232R CBUS EEPROM options - 48MHz clock
     */
    readonly FT_CBUS_CLK48: 0x06,
      /**
     * FT232R CBUS EEPROM options - 24MHz clock
     */
    readonly FT_CBUS_CLK24: 0x07,
      /**
     * FT232R CBUS EEPROM options - 12MHz clock
     */
    readonly FT_CBUS_CLK12: 0x08,
      /**
     * FT232R CBUS EEPROM options - 6MHz clock
     */
    readonly FT_CBUS_CLK6: 0x09,
      /**
     * FT232R CBUS EEPROM options - IO mode
     */
    readonly FT_CBUS_IOMODE: 0x0A,
      /**
     * FT232R CBUS EEPROM options - Bit-bang write strobe
     */
    readonly FT_CBUS_BITBANG_WR: 0x0B,
    /**
     * FT232R CBUS EEPROM options - Bit-bang read strobe
     */
    readonly FT_CBUS_BITBANG_RD: 0x0C
  }
export type FT_CBUS_OPTIONS = Enum<typeof FT_CBUS_OPTIONS>;

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

export type FtResult = {
    /**
     * Value from FTDI native call
     */
    readonly ftStatus: FT_STATUS;
}

export type GetNumberOfDevicesResult = {
    /**
     * The number of FTDI devices available
     */
    readonly devCount: number
} & FtResult;

export type GetDeviceListResult = {
    readonly deviceList: DeviceInfoNode[];
} & FtResult;

export type GetDeviceInfoResult = {
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
} & FtResult;

export type GetQueueStatusResult = {
    /**
     * The number of bytes available to be read
     */
    readonly rxQueue: number
} & FtResult;

export type IGetStatusResult = {
    /**
     * The number of bytes waiting to be sent
     */
    readonly txQueue: number;
    /**
     * The type of event that has occurred
     */
    readonly eventStatus: number;
} & FtResult;

export type WriteResult = {
    /**
     * The number of bytes actually written to the device
     */
    readonly numBytesWritten: number;
} & FtResult;

export type ReadResult = {
    /**
     * An array of bytes which was populated with the data read from the device
     */
    readonly rxBuffer: Buffer;
    /**
     * The number of bytes actually read
     */
    readonly numBytesRead: number;
} & FtResult;

export type ReadFT232HEEPROMResult = {
    /**
     * An FT232H_EEPROM_STRUCTURE which contains only the relevant information for an FT232H device
     */
    readonly ee232h: FT232H_EEPROM_STRUCTURE;
} & FtResult;

export type ReadFT232REEPROMResult = {
    /**
     * An FT232R_EEPROM_STRUCTURE which contains only the relevant information for an FT232R and FT245R devices
     */
    readonly ee232r: FT232R_EEPROM_STRUCTURE;
} & FtResult;

export type GetVIDPIDResult = {
    /**
     * Device Vendor ID (VID)
     */
    readonly dwVID: number;
    /**
     * Device Product ID (PID)
     */
    readonly dwPID: number;
} & FtResult;

export class FtException extends Error { }

/**
 * Common EEPROM elements for all devices. Inherited to specific device type EEPROMs
 */
export class FT_EEPROM_DATA {
    /**
     * Vendor ID as supplied by the USB Implementers Forum. Default: 0x0403
     */
    vendorId: number;
    /**
     * Product ID. Default: 0x6001
     */
    productId: number;
    /**
     * Manufacturer name string. Default: 'FTDI'
     */
    manufacturer: string;
    /**
     * Manufacturer name abbreviation to be used as a prefix for automatically
     * generated serial numbers. Default: 'FT'
     */
    manufacturerId: string;
    /**
     * Device description string. Default: 'USB-Serial Converter'
     */
    description: string;
    /**
     * Device serial number string. Default: ''
     */
    serialNumber: string;
    /**
     * Maximum power the device needs. Default: 0x0090
     */
    maxPower: number;
    /**
     * Indicates if the device has its own power supply (self-powered) or
     * gets power from the USB port (bus-powered). Default: false
     */
    selfPowered: boolean;
    /**
     * Determines if the device can wake the host PC from
     * suspend by toggling the RI line. Default: false
     */
    remoteWakeup: boolean;
}

/**
 * EEPROM structure specific to FT232H devices
 */
export class FT232H_EEPROM_STRUCTURE extends FT_EEPROM_DATA {
    /**
     * Determines if IOs are pulled down when the device is in suspend. Default: false
     */
    pullDownEnable: boolean;
    /**
     * Determines if the serial number is enabled. Default: true
     */
    serNumEnable: boolean;
    /**
     * Determines if AC pins have a slow slew rate. Default: false
     */
    acSlowSlew: boolean;
    /**
     *  Determines if the AC pins have a Schmitt input. Default: false
     */
    acSchmittInput: boolean;
    /**
     * Determines the AC pins drive
     * current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or
     * FT_DRIVE_CURRENT_16MA. Default: FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA
     */
    acDriveCurrent: FT_DRIVE_CURRENT;
    /**
     * Determines if AD pins have a slow slew rate. Default: false
     */
    adSlowSlew: boolean;
    /**
     * Determines if the AD pins have a Schmitt input. Default: false
     */
    adSchmittInput: boolean;
    /**
     * Determines the AD pins drive
     * current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or
     * FT_DRIVE_CURRENT_16MA. Default: FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA
     */
    adDriveCurrent: FT_DRIVE_CURRENT;
    /**
     * Sets the function of the CBUS0 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5.
     * Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus0: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS1 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5.
     * Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus1: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS2 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus2: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS3 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus3: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS4 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus4: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS5 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus5: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS6 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus6: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS7 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus7: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS8 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus8: FT_232H_CBUS_OPTIONS;
    /**
     * Sets the function of the CBUS9 pin for
     * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
     * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
     * FT_CBUS_CLK7_5. Default: FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
     */
    cbus9: FT_232H_CBUS_OPTIONS;
    /**
     * Determines if the device is in FIFO mode. Default: false
     */
    isFifo: boolean;
    /**
     * Determines if the device is in FIFO target mode. Default: false
     */
    isFifoTar: boolean;
    /**
     * Determines if the device is in fast serial mode. Default: false
     */
    isFastSer: boolean;
    /**
     * Determines if the device is in FT1248 mode. Default: false
     */
    isFT1248: boolean;
    /**
     * Determines FT1248 mode clock polarity. Default: false
     */
    ft1248Cpol: boolean;
    /**
     * Determines if data is ent MSB (0) or LSB (1) in FT1248 mode. Default: false
     */
    ft1248Lsb: boolean;
    /**
     * Determines if FT1248 mode uses flow control. Default: false
     */
    ft1248FlowControl: boolean;
    /**
     * Determines if the VCP driver is loaded. Default: true
     */
    isVCP: boolean;
    /**
     * For self-powered designs, keeps the FT232H in low power state until ACBUS7 is high. Default: false
     */
    powerSaveEnable: boolean;
}

/**
 * EEPROM structure specific to FT232R and FT245R devices
 */
export class FT232R_EEPROM_STRUCTURE extends FT_EEPROM_DATA {
    /**
     * Disables the FT232R internal clock source.
     * If the device has external oscillator enabled it must have an external oscillator fitted to function
     */
    useExtOsc: boolean;
    /**
     * Enables high current IOs
     */
    highDriveIOs: boolean;
    /**
     * Sets the endpoint size. This should always be set to 64
     */
    endpointSize: number;
    /**
     * Determines if IOs are pulled down when the device is in suspend
     */
    pullDownEnable: boolean;
    /**
     * Determines if the serial number is enabled
     */
    serNumEnable: boolean;
    /**
     * Inverts the sense of the TXD line
     */
    invertTXD: boolean;
    /**
     * Inverts the sense of the RXD line
     */
    invertRXD: boolean;
    /**
     * Inverts the sense of the RTS line
     */
    invertRTS: boolean;
    /**
     * Inverts the sense of the CTS line
     */
    invertCTS: boolean;
    /**
     * Inverts the sense of the DTR line
     */
    invertDTR: boolean;
    /**
     * Inverts the sense of the DSR line
     */
    invertDSR: boolean;
    /**
     * Inverts the sense of the DCD line
     */
    invertDCD: boolean;
    /**
     * Inverts the sense of the RI line
     */
    invertRI: boolean;
    /**
     * Sets the function of the CBUS0 pin for FT232R devices.
     * Valid values are FT_CBUS_TXDEN, FT_CBUS_PWRON , FT_CBUS_RXLED, FT_CBUS_TXLED,
     * FT_CBUS_TXRXLED, FT_CBUS_SLEEP, FT_CBUS_CLK48, FT_CBUS_CLK24, FT_CBUS_CLK12,
     * FT_CBUS_CLK6, FT_CBUS_IOMODE, FT_CBUS_BITBANG_WR, FT_CBUS_BITBANG_RD
     */
    cbus0: number;
    /**
     * Sets the function of the CBUS1 pin for FT232R devices.
     * Valid values are FT_CBUS_TXDEN, FT_CBUS_PWRON , FT_CBUS_RXLED, FT_CBUS_TXLED,
     * FT_CBUS_TXRXLED, FT_CBUS_SLEEP, FT_CBUS_CLK48, FT_CBUS_CLK24, FT_CBUS_CLK12,
     * FT_CBUS_CLK6, FT_CBUS_IOMODE, FT_CBUS_BITBANG_WR, FT_CBUS_BITBANG_RD
     */
    cbus1: number;
    /**
     * Sets the function of the CBUS2 pin for FT232R devices.
     * Valid values are FT_CBUS_TXDEN, FT_CBUS_PWRON , FT_CBUS_RXLED, FT_CBUS_TXLED,
     * FT_CBUS_TXRXLED, FT_CBUS_SLEEP, FT_CBUS_CLK48, FT_CBUS_CLK24, FT_CBUS_CLK12,
     * FT_CBUS_CLK6, FT_CBUS_IOMODE, FT_CBUS_BITBANG_WR, FT_CBUS_BITBANG_RD
     */
    cbus2: number;
    /**
     * Sets the function of the CBUS3 pin for FT232R devices.
     * Valid values are FT_CBUS_TXDEN, FT_CBUS_PWRON , FT_CBUS_RXLED, FT_CBUS_TXLED,
     * FT_CBUS_TXRXLED, FT_CBUS_SLEEP, FT_CBUS_CLK48, FT_CBUS_CLK24, FT_CBUS_CLK12,
     * FT_CBUS_CLK6, FT_CBUS_IOMODE, FT_CBUS_BITBANG_WR, FT_CBUS_BITBANG_RD
     */
    cbus3: number;
    /**
     * Sets the function of the CBUS4 pin for FT232R devices.
     * Valid values are FT_CBUS_TXDEN, FT_CBUS_PWRON , FT_CBUS_RXLED, FT_CBUS_TXLED,
     * FT_CBUS_TXRXLED, FT_CBUS_SLEEP, FT_CBUS_CLK48, FT_CBUS_CLK24, FT_CBUS_CLK12,
     * FT_CBUS_CLK6
     */
    cbus4: number;
    /**
     * Determines if the VCP driver is loaded
     */
    rIsD2XX: boolean;
}

export class FTDI {
    /**
     * Synchronously gets the number of FTDI devices available
     */
    static getNumberOfDevicesSync(): GetNumberOfDevicesResult;
    /**
     * Asynchronously gets the number of FTDI devices available
     */
    static getNumberOfDevices(): Promise<GetNumberOfDevicesResult>;
    /**
     * Synchronously gets information on all of the FTDI devices available
     */
    static getDeviceListSync(): GetDeviceListResult;
    /**
     * Asynchronously gets information on all of the FTDI devices available
     */
    static getDeviceList(): Promise<GetDeviceListResult>;
    /**
     * Synchronously opens the FTDI device with the specified index.
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param index Index of the device to open,
     * note that this cannot be guaranteed to open a specific device
     */
    openByIndexSync(index: number): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified index.
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param index Index of the device to open,
     * note that this cannot be guaranteed to open a specific device
     */
    openByIndex(index: number): Promise<FT_STATUS>;
    /**
     * Synchronously opens the FTDI device with the specified serial number
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param serialNumber Serial number of the device to open
     */
    openBySerialNumberSync(serialNumber: string): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified serial number
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param serialNumber Serial number of the device to open
     */
    openBySerialNumber(serialNumber: string): Promise<FT_STATUS>;
    /**
     * Synchronously opens the FTDI device with the specified description
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param description Description of the device to open
     */
    openByDescriptionSync(description: string): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device with the specified description
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param description Description of the device to open
     */
    openByDescription(description: string): Promise<FT_STATUS>;
    /**
     * Synchronously opens the FTDI device at the specified physical location
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param location Location of the device to open
     */
    openByLocationSync(location: number): FT_STATUS;
    /**
     * Asynchronously opens the FTDI device at the specified physical location
     * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
     * @param location Location of the device to open
     */
    openByLocation(location: number): Promise<FT_STATUS>;
    /**
     * Synchronously closes the handle to an open FTDI device
     */
    closeSync(): FT_STATUS;
    /**
     * Asynchronously closes the handle to an open FTDI device
     */
    close(): Promise<FT_STATUS>;
    /**
     * Synchronously gets device information for an open device
     */
    getDeviceInfoSync(): GetDeviceInfoResult;
    /**
     * Asynchronously gets device information for an open device
     */
    getDeviceInfo(): Promise<GetDeviceInfoResult>;
    /**
     * Synchronously sets the data bits, stop bits and parity for the device
     * @param wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or
     * FT_DATA_BITS.FT_BITS_8
     * @param stopBits The number of stop bits for UART data.
     * Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
     * @param parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE,
     * FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
     */
    setDataCharacteristicsSync(wordLength: FT_DATA_BITS, stopBits: FT_STOP_BITS, parity: FT_PARITY): FT_STATUS;
    /**
     * Asynchronously sets the data bits, stop bits and parity for the device
     * @param wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or
     * FT_DATA_BITS.FT_BITS_8
     * @param stopBits The number of stop bits for UART data.
     * Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
     * @param parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE,
     * FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
     */
    setDataCharacteristics(
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
    setFlowControlSync(flowControl: FT_FLOW_CONTROL, xon: number, xoff: number): FT_STATUS;
    /**
     * Asynchronously sets the flow control type
     * @param flowControl The type of flow control for the UART. Valid values are
     * FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or
     * FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
     * @param xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow contro
     * @param xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
     */
    setFlowControl(flowControl: FT_FLOW_CONTROL, xon: number, xoff: number): Promise<FT_STATUS>;
    /**
     * Synchronously sets the current Baud rate
     * @param baudRate The desired Baud rate for the device
     */
    setBaudRateSync(baudRate: number): FT_STATUS;
    /**
     * Asynchronously sets the current Baud rate
     * @param baudRate The desired Baud rate for the device
     */
    setBaudRate(baudRate: number): Promise<FT_STATUS>;
    /**
     * Synchronously gets the number of bytes available in the receive buffer
     */
    getQueueStatusSync(): GetQueueStatusResult;
    /**
     * Asynchronously gets the number of bytes available in the receive buffer
     */
    getQueueStatus(): Promise<GetQueueStatusResult>;
    /**
     * Synchronously gets the device status including number of characters in the receive queue,
     * number of characters in the transmit queue, and the current event status
     */
    getStatusSync(): IGetStatusResult;
    /**
     * Asynchronously gets the device status including number of characters in the receive queue,
     * number of characters in the transmit queue, and the current event status
     */
    getStatus(): Promise<IGetStatusResult>;
    /**
     * Synchronously write data to an open FTDI device
     * @param txBuffer An array of bytes which contains the data to be written to the device
     * @param numBytesToWrite The number of bytes to be written to the device. Default: txBuffer.Length
     */
    writeSync(txBuffer: Buffer, numBytesToWrite?: number): WriteResult;
    /**
     * Asynchronously write data to an open FTDI device
     * @param txBuffer An array of bytes which contains the data to be written to the device
     * @param numBytesToWrite The number of bytes to be written to the device. Default: txBuffer.Length
     */
    write(txBuffer: Buffer, numBytesToWrite?: number): Promise<WriteResult>;
    /**
     * Synchronously read data from an open FTDI device
     * @param rxBuffer An array of bytes which will be populated with the data read from the device
     * @param numBytesToRead The number of bytes requested from the device. Default: rxBuffer.Length
     */
    readSync(rxBuffer: Buffer, numBytesToRead?: number): ReadResult;
    /**
     * Asynchronously read data from an open FTDI device
     * @param rxBuffer An array of bytes which will be populated with the data read from the device
     * @param numBytesToRead The number of bytes requested from the device. Default: rxBuffer.Length
     */
    read(rxBuffer: Buffer, numBytesToRead?: number): Promise<ReadResult>;
    /**
     * Synchronously reads the EEPROM contents of an FT232H device
     */
    readFT232HEEPROMSync(): ReadFT232HEEPROMResult;
    /**
     * Asynchronously reads the EEPROM contents of an FT232H device
     */
    readFT232HEEPROM(): Promise<ReadFT232HEEPROMResult>;

    /**
     * Synchronously writes the specified values to the EEPROM of an FT232H device
     * @param  ee232h The EEPROM settings to be written to the device
     */
    writeFT232HEEPROMSync(ee232h: FT232H_EEPROM_STRUCTURE): FT_STATUS;

    /**
     * Asynchronously writes the specified values to the EEPROM of an FT232H device
     * @param ee232h The EEPROM settings to be written to the device
     */
    writeFT232HEEPROM(ee232h: FT232H_EEPROM_STRUCTURE): Promise<FT_STATUS>;

    /**
     * Synchronously reads the EEPROM contents of an FT232R or FT245R device
     */
    readFT232REEPROMSync(): ReadFT232REEPROMResult;

    /**
     * Asynchronously reads the EEPROM contents of an FT232R or FT245R device
     */
    readFT232REEPROM(): Promise<ReadFT232REEPROMResult>;

    /**
     * Synchronously writes the specified values to the EEPROM of an FT232R or FT245R device
     * @param {FT232R_EEPROM_STRUCTURE} ee232r The EEPROM settings to be written to the device
     */
    writeFT232REEPROMSync(ee232r: FT232R_EEPROM_STRUCTURE): FT_STATUS;

    /**
     * Asynchronously writes the specified values to the EEPROM of an FT232R or FT245R device
     * @param {FT232R_EEPROM_STRUCTURE} ee232r The EEPROM settings to be written to the device
     */
    writeFT232REEPROM(ee232r: FT232R_EEPROM_STRUCTURE): Promise<FT_STATUS>;

    /**
     * Synchronously puts the device in a mode other than the default UART or FIFO mode
     * @param {number} mask Sets up which bits are inputs and which are outputs. A bit value of 0 sets the corresponding
     * pin to an input, a bit value of 1 sets the corresponding pin to an output. In the case of CBUS Bit Bang,
     * the upper nibble of this value controls which pins are inputs and outputs, while the lower nibble controls
     * which of the outputs are high and low
     * @param {number} bitMode For FT232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG,
     * FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG, FT_BIT_MODE_MCU_HOST,
     * FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO. For FT2232H devices, valid values are FT_BIT_MODE_RESET,
     * FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST,
     * FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO. For FT4232H devices, valid values are FT_BIT_MODE_RESET,
     * FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG. For FT232R devices,
     * valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG.
     * For FT245R devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG.
     * For FT2232 devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE,
     * FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL. For FT232B and FT245B devices,
     * valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG
     */
    setBitModeSync(mask: number, bitMode: number): FT_STATUS;

    /**
     * Asynchronously puts the device in a mode other than the default UART or FIFO mode
     * @param {number} mask Sets up which bits are inputs and which are outputs. A bit value of 0 sets the corresponding
     * pin to an input, a bit value of 1 sets the corresponding pin to an output. In the case of CBUS Bit Bang,
     * the upper nibble of this value controls which pins are inputs and outputs, while the lower nibble controls
     * which of the outputs are high and low
     * @param {number} bitMode For FT232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG,
     * FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG, FT_BIT_MODE_MCU_HOST,
     * FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO. For FT2232H devices, valid values are FT_BIT_MODE_RESET,
     * FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST,
     * FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO. For FT4232H devices, valid values are FT_BIT_MODE_RESET,
     * FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG. For FT232R devices,
     * valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG.
     * For FT245R devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG.
     * For FT2232 devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE,
     * FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL. For FT232B and FT245B devices,
     * valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG
     */
    setBitMode(mask: number, bitMode: number): Promise<FT_STATUS>;

    /**
   * @param {string} description
   * Synchronously programm device description in EEPROM
   * @returns {FT_STATUS}
   */
    programDeviceDescriptionSync(description: string): FT_STATUS;

    /**
     * @param {string} description
     * Asynchronously programm device description in EEPROM
     * @returns {Promise<FT_STATUS>}
     */
    programDeviceDescription(description: string): Promise<FT_STATUS>;
    /**
       * @typedef {object} GetVIDPODResult
       * @property {FT_STATUS} ftStatus Value from FT_Read
       * @property {number} VID Pointer to DWORD that will contain the internal VID
       * @property {number} PID Pointer to DWORD that will contain the internal PID
       */
    /**
     * Synchronously retrieve the current VID and PID combination from within the internal device list table
     * @returns {GetVIDPIDResult}
     */
    static getVIDPIDSync(): GetVIDPIDResult;

    /**
     * Asynchronously  retrieve the current VID and PID combination from within the internal device list table
     * @returns {Promise<GetVIDPIDResult>}
     */
    static getVIDPID(): Promise<GetVIDPIDResult>;

    /**
   * Synchronously send a reset command to the port
   * @returns {FT_STATUS} ftStatus Value from FT_CyclePort
   */
    cyclePortSync(): FT_STATUS;

    /**
     * Asynchronously send a reset command to the port
     * @returns {Promise<FT_STATUS>} ftStatus Value from FT_CyclePort
     */
    cyclePort(): Promise<FT_STATUS>;
}
