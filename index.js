'use strict'
const _ftdiAddon = require('bindings')('N-FTD2XX')

// Flags for FT_OpenEx
const FT_OPEN_BY_SERIAL_NUMBER = 0x00000001
const FT_OPEN_BY_DESCRIPTION = 0x00000002
const FT_OPEN_BY_LOCATION = 0x00000004

/**
 * Status values for FTDI devices
 * @enum {number}
 */
const FT_STATUS = {
  /**
   * Status OK
   */
  FT_OK: 0,
  /**
   * The device handle is invalid
   */
  FT_INVALID_HANDLE: 1,
  /**
   * Device not found
   */
  FT_DEVICE_NOT_FOUND: 2,
  /**
   * Device is not open
   */
  FT_DEVICE_NOT_OPENED: 3,
  /**
   * IO error
   */
  FT_IO_ERROR: 4,
  /**
   * Insufficient resources
   */
  FT_INSUFFICIENT_RESOURCES: 5,
  /**
   * A parameter was invalid
   */
  FT_INVALID_PARAMETER: 6,
  /**
   * The requested baud rate is invalid
   */
  FT_INVALID_BAUD_RATE: 7,
  /**
   * Device not opened for erase
   */
  FT_DEVICE_NOT_OPENED_FOR_ERASE: 8,
  /**
   * Device not poened for write
   */
  FT_DEVICE_NOT_OPENED_FOR_WRITE: 9,
  /**
   * Failed to write to device
   */
  FT_FAILED_TO_WRITE_DEVICE: 10,
  /**
   * Failed to read the device EEPROM
   */
  FT_EEPROM_READ_FAILED: 11,
  /**
   * Failed to write the device EEPROM
   */
  FT_EEPROM_WRITE_FAILED: 12,
  /**
   * Failed to erase the device EEPROM
   */
  FT_EEPROM_ERASE_FAILED: 13,
  /**
   * An EEPROM is not fitted to the device
   */
  FT_EEPROM_NOT_PRESENT: 14,
  /**
   * Device EEPROM is blank
   */
  FT_EEPROM_NOT_PROGRAMMED: 15,
  /**
   * Invalid arguments
   */
  FT_INVALID_ARGS: 16,
  /**
   * An other error has occurred
   */
  FT_OTHER_ERROR: 17
}
Object.freeze(FT_STATUS)

/**
 * Device type identifiers for FT_GetDeviceInfoDetail and FT_GetDeviceInfo
 * @enum {number}
 */
const FT_DEVICE = {
  /**
   * FT232B or FT245B device
   */
  FT_DEVICE_BM: 0,
  /**
   * FT8U232AM or FT8U245AM device
   */
  FT_DEVICE_AM: 1,
  /**
   * FT8U100AX device
   */
  FT_DEVICE_100AX: 2,
  /**
   * Unknown device
   */
  FT_DEVICE_UNKNOWN: 3,
  /**
   * FT2232 device
   */
  FT_DEVICE_2232: 4,
  /**
   * FT232R or FT245R device
   */
  FT_DEVICE_232R: 5,
  /**
   * FT2232H device
   */
  FT_DEVICE_2232H: 6,
  /**
   * FT4232H device
   */
  FT_DEVICE_4232H: 7,
  /**
   * FT232H device
   */
  FT_DEVICE_232H: 8,
  /**
   * FT X-Series device
   */
  FT_DEVICE_X_SERIES: 9,
  /**
   * FT4222 hi-speed device Mode 0 - 2 interfaces
   */
  FT_DEVICE_4222H_0: 10,
  /**
   * FT4222 hi-speed device Mode 1 or 2 - 4 interfaces
   */
  FT_DEVICE_4222H_1_2: 11,
  /**
   * FT4222 hi-speed device Mode 3 - 1 interface
   */
  FT_DEVICE_4222H_3: 12,
  /**
   * OTP programmer board for the FT4222
   */
  FT_DEVICE_4222_PROG: 13
}
Object.freeze(FT_STATUS)

/**
 * Flags that provide information on the FTDI device state
 * @enum {number}
 */
const FT_FLAGS = {
  /**
   * Indicates that the device is open
   */
  FT_FLAGS_OPENED: 0x00000001,
  /**
   * Indicates that the device is enumerated as a hi-speed USB device
   */
  FT_FLAGS_HISPEED: 0x00000002
}
Object.freeze(FT_FLAGS)

/**
 * Permitted data bits for FTDI devices
 * @enum {number}
 */
const FT_DATA_BITS = {
  /**
   * 8 data bits
   */
  FT_BITS_8: 0x08,
  /**
   * 7 data bits
   */
  FT_BITS_7: 0x07
}
Object.freeze(FT_FLAGS)

/**
 * Permitted stop bits for FTDI devices
 * @enum {number}
 */
const FT_STOP_BITS = {
  /**
   * 1 stop bit
   */
  FT_STOP_BITS_1: 0x00,
  /**
   * 2 stop bits
   */
  FT_STOP_BITS_2: 0x02
}
Object.freeze(FT_STOP_BITS)

/**
 * Permitted parity values for FTDI devices
 * @enum {number}
 */
const FT_PARITY = {
  /**
   * No parity
   */
  FT_PARITY_NONE: 0x00,
  /**
   * Odd parity
   */
  FT_PARITY_ODD: 0x01,
  /**
   * Even parity
   */
  FT_PARITY_EVEN: 0x02,
  /**
   * Mark parity
   */
  FT_PARITY_MARK: 0x03,
  /**
   * Space parity
   */
  FT_PARITY_SPACE: 0x04
}
Object.freeze(FT_PARITY)

/**
 * Permitted flow control values for FTDI devices
 * @enum {number}
 */
const FT_FLOW_CONTROL = {
  /**
   * No flow control
   */
  FT_FLOW_NONE: 0x0000,
  /**
   * RTS/CTS flow control
   */
  FT_FLOW_RTS_CTS: 0x0100,
  /**
   * DTR/DSR flow control
   */
  FT_FLOW_DTR_DSR: 0x0200,
  /**
   * Xon/Xoff flow control
   */
  FT_FLOW_XON_XOFF: 0x0400
}
Object.freeze(FT_FLOW_CONTROL)

/**
 * Valid values for drive current options on FT2232H, FT4232H and FT232H devices
 * @enum {number}
 */
const FT_DRIVE_CURRENT = {
  /**
   * 4mA drive current
   */
  FT_DRIVE_CURRENT_4MA: 4,
  /**
   * 8mA drive current
   */
  FT_DRIVE_CURRENT_8MA: 8,
  /**
   * 12mA drive current
   */
  FT_DRIVE_CURRENT_12MA: 12,
  /**
   * 16mA drive current
   */
  FT_DRIVE_CURRENT_16MA: 16
}
Object.freeze(FT_DRIVE_CURRENT)

/**
 * Available functions for the FT232H CBUS pins. Controlled by FT232H EEPROM settings
 * @enum {number}
 */
const FT_232H_CBUS_OPTIONS = {
  /**
   * FT232H CBUS EEPROM options - Tristate
   */
  FT_CBUS_TRISTATE: 0x00,
  /**
   * FT232H CBUS EEPROM options - Rx LED
   */
  FT_CBUS_RXLED: 0x01,
  /**
   * FT232H CBUS EEPROM options - Tx LED
   */
  FT_CBUS_TXLED: 0x02,
  /**
   * FT232H CBUS EEPROM options - Tx and Rx LED
   */
  FT_CBUS_TXRXLED: 0x03,
  /**
   * FT232H CBUS EEPROM options - Power Enable#
   */
  FT_CBUS_PWREN: 0x04,
  /**
   * FT232H CBUS EEPROM options - Sleep
   */
  FT_CBUS_SLEEP: 0x05,
  /**
   * FT232H CBUS EEPROM options - Drive pin to logic 0
   */
  FT_CBUS_DRIVE_0: 0x06,
  /**
   * FT232H CBUS EEPROM options - Drive pin to logic 1
   */
  FT_CBUS_DRIVE_1: 0x07,
  /**
   * FT232H CBUS EEPROM options - IO Mode
   */
  FT_CBUS_IOMODE: 0x08,
  /**
   * FT232H CBUS EEPROM options - Tx Data Enable
   */
  FT_CBUS_TXDEN: 0x09,
  /**
   * FT232H CBUS EEPROM options - 30MHz clock
   */
  FT_CBUS_CLK30: 0x0A,
  /**
   * FT232H CBUS EEPROM options - 15MHz clock
   */
  FT_CBUS_CLK15: 0x0B,
  /**
   * FT232H CBUS EEPROM options - 7.5MHz clock
   */
  FT_CBUS_CLK7_5: 0x0C
}
Object.freeze(FT_232H_CBUS_OPTIONS)

/**
 * Error states not supported by FTD2XX
 * @enum {number}
 */
const FT_ERROR = {
  FT_NO_ERROR: 0,
  FT_INCORRECT_DEVICE: 1,
  FT_INVALID_BITMODE: 2,
  FT_BUFFER_SIZE: 3
}
Object.freeze(FT_232H_CBUS_OPTIONS)

/**
 * Permitted bit mode values for FTDI devices. For use with SetBitMode
 * @enum {number}
 */
const FT_BIT_MODES = {
  /**
   * Reset bit mode
   */
  FT_BIT_MODE_RESET: 0x00,
  /**
   * Asynchronous bit-bang mode
   */
  FT_BIT_MODE_ASYNC_BITBANG: 0x01,
  /**
   * MPSSE bit mode - only available on FT2232, FT2232H, FT4232H and FT232H
   */
  FT_BIT_MODE_MPSSE: 0x02,
  /**
   * Synchronous bit-bang mode
   */
  FT_BIT_MODE_SYNC_BITBANG: 0x04,
  /**
   * MCU host bus emulation mode - only available on FT2232, FT2232H, FT4232H and FT232H
   */
  FT_BIT_MODE_MCU_HOST: 0x08,
  /**
   * Fast opto-isolated serial mode - only available on FT2232, FT2232H, FT4232H and FT232H
   */
  FT_BIT_MODE_FAST_SERIAL: 0x10,
  /**
   * CBUS bit-bang mode - only available on FT232R and FT232H
   */
  FT_BIT_MODE_CBUS_BITBANG: 0x20,
  /**
   * Single channel synchronous 245 FIFO mode - only available on FT2232H channel A and FT232H
   */
  FT_BIT_MODE_SYNC_FIFO: 0x40
}
Object.freeze(FT_BIT_MODES)

/**
 * @typedef {object} FT_PROGRAM_DATA
 * @property {number} signature1 Header - must be 0x0000000
 * @property {number} signature2 Header - must be 0xffffffff
 * @property {number} version Header - FT_PROGRAM_DATA version: 0 = original (FT232B), 1 = FT2232 extensions,
 * 2 = FT232R extensions, 3 = FT2232H extensions, 4 = FT4232H extensions, 5 = FT232H extensions
 * @property {number} vendorId
 * @property {number} productId
 * @property {string} manufacturer
 * @property {string} manufacturerId
 * @property {string} description
 * @property {string} serialNumber
 * @property {number} maxPower 0 < MaxPower <= 500
 * @property {number} pnp 0 = disabled, 1 = enabled
 * @property {boolean} selfPowered 0 = bus powered, 1 = self powered
 * @property {boolean} remoteWakeup 0 = not capable, 1 = capable
 * @property {boolean} pullDownEnableH non-zero if pull down enabled
 * @property {boolean} serNumEnableH non-zero if serial number to be used
 * @property {boolean} acSlowSlewH  non-zero if AC pins have slow slew
 * @property {boolean} acSchmittInputH non-zero if AC pins are Schmitt input
 * @property {FT_DRIVE_CURRENT} acDriveCurrentH valid values are 4mA, 8mA, 12mA, 16mA
 * @property {boolean} adSlowSlewH non-zero if AD pins have slow slew
 * @property {boolean} adSchmittInputH non-zero if AD pins are Schmitt input
 * @property {FT_DRIVE_CURRENT} adDriveCurrentH valid values are 4mA, 8mA, 12mA, 16mA
 * @property {number} cbus0H Cbus Mux control
 * @property {number} cbus1H Cbus Mux control
 * @property {number} cbus2H Cbus Mux control
 * @property {number} cbus3H Cbus Mux control
 * @property {number} cbus4H Cbus Mux control
 * @property {number} cbus5H Cbus Mux control
 * @property {number} cbus6H Cbus Mux control
 * @property {number} cbus7H Cbus Mux control
 * @property {number} cbus8H Cbus Mux control
 * @property {number} cbus9H Cbus Mux control
 * @property {boolean} isFifoH non-zero if interface is 245 FIFO
 * @property {boolean} isFifoTarH non-zero if interface is 245 FIFO CPU target
 * @property {boolean} isFastSerH  non-zero if interface is Fast serial
 * @property {boolean} isFT1248H non-zero if interface is FT1248
 * @property {boolean} ft1248CpolH FT1248 clock polarity - clock idle high (1) or clock idle low (0)
 * @property {boolean} ft1248LsbH FT1248 data is LSB (1) or MSB (0)
 * @property {boolean} ft1248FlowControlH FT1248 flow control enable
 * @property {boolean} isVCPH if interface is to use VCP drivers
 * @property {boolean} powerSaveEnableH non-zero if using ACBUS7 to save power for self-powered
 */

/**
 * Common EEPROM elements for all devices. Inherited to specific device type EEPROMs
 * @property {number} vendorId=0x0403 Vendor ID as supplied by the USB Implementers Forum
 * @property {number} productId=0x6001 Product ID
 * @property {string} manufacturer="FTDI" Manufacturer name string
 * @property {string} manufacturerId="FT" Manufacturer name abbreviation to be used as a prefix for automatically
 * generated serial numbers
 * @property {string} description="USB-Serial Converter" Device description string
 * @property {string} serialNumber="" Device serial number string
 * @property {number} maxPower=0x0090 Maximum power the device needs
 * @property {boolean} selfPowered=false Indicates if the device has its own power supply (self-powered) or
 * gets power from the USB port (bus-powered)
 * @property {boolean} remoteWakeup=false Determines if the device can wake the host PC from
 * suspend by toggling the RI line
 */
class FT_EEPROM_DATA {
  constructor () {
    this.vendorId = 0x0403
    this.productId = 0x6001
    this.manufacturer = 'FTDI'
    this.manufacturerId = 'FT'
    this.description = 'USB-Serial Converter'
    this.serialNumber = ''
    this.maxPower = 0x0090
    this.selfPowered = false
    this.remoteWakeup = false
  }
}

/**
 * EEPROM structure specific to FT232H devices
 * @property {boolean} pullDownEnable=false Determines if IOs are pulled down when the device is in suspend
 * @property {boolean} serNumEnable=true Determines if the serial number is enabled
 * @property {boolean} acSlowSlew=false Determines if AC pins have a slow slew rate
 * @property {boolean} acSchmittInput=false Determines if the AC pins have a Schmitt input
 * @property {FT_DRIVE_CURRENT} acDriveCurrent=FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA Determines the AC pins drive
 * current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or
 * FT_DRIVE_CURRENT_16MA
 * @property {boolean} adSlowSlew=false Determines if AD pins have a slow slew rate
 * @property {boolean} adSchmittInput=false Determines if the AD pins have a Schmitt input
 * @property {FT_DRIVE_CURRENT} adDriveCurrent=FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA Determines the AD pins drive
 * current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or
 * FT_DRIVE_CURRENT_16MA
 * @property {FT_232H_CBUS_OPTIONS} cbus0=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS0 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus1=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS1 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus2=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS2 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN
 * @property {FT_232H_CBUS_OPTIONS} cbus3=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS3 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN
 * @property {FT_232H_CBUS_OPTIONS} cbus4=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS4 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN
 * @property {FT_232H_CBUS_OPTIONS} cbus5=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS5 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
 * FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus6=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS6 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
 * FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus7=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS7 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE
 * @property {FT_232H_CBUS_OPTIONS} cbus8=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS8 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
 * FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus9=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS9 pin for
 * FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN,
 * FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15,
 * FT_CBUS_CLK7_5
 * @property {boolean} isFifo=false Determines if the device is in FIFO mode
 * @property {boolean} isFifoTar=false Determines if the device is in FIFO target mode
 * @property {boolean} isFastSer=false Determines if the device is in fast serial mode
 * @property {boolean} isFT1248=false Determines if the device is in FT1248 mode
 * @property {boolean} ft1248Cpol=false Determines FT1248 mode clock polarity
 * @property {boolean} ft1248Lsb=false Determines if data is ent MSB (0) or LSB (1) in FT1248 mode
 * @property {boolean} ft1248FlowControl=false Determines if FT1248 mode uses flow control
 * @property {boolean} isVCP=true Determines if the VCP driver is loaded
 * @property {boolean} powerSaveEnable=false For self-powered designs, keeps the FT232H in low power state until
 * ACBUS7 is high
 */
class FT232H_EEPROM_STRUCTURE extends FT_EEPROM_DATA {
  constructor () {
    super()
    this.pullDownEnable = false
    this.serNumEnable = true
    this.acSlowSlew = false
    this.acSchmittInput = false
    this.acDriveCurrent = FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA
    this.adSlowSlew = false
    this.adSchmittInput = false
    this.adDriveCurrent = FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA
    this.cbus0 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus1 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus2 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus3 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus4 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus5 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus6 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus7 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus8 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.cbus9 = FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE
    this.isFifo = false
    this.isFifoTar = false
    this.isFastSer = false
    this.isFT1248 = false
    this.ft1248Cpol = false
    this.ft1248Lsb = false
    this.ft1248FlowControl = false
    this.isVCP = true
    this.powerSaveEnable = false
  }
}

class FtEeUtils {
  /**
   * @param {FT_PROGRAM_DATA} eeData
   * @returns {FT232H_EEPROM_STRUCTURE}
   */
  static CreateEe232h (eeData) {
    const ee232h = new FT232H_EEPROM_STRUCTURE()
    ee232h.manufacturer = eeData.manufacturer
    ee232h.manufacturerId = eeData.manufacturerId
    ee232h.description = eeData.description
    ee232h.serialNumber = eeData.serialNumber
    ee232h.vendorId = eeData.vendorId
    ee232h.productId = eeData.productId
    ee232h.maxPower = eeData.maxPower
    ee232h.selfPowered = eeData.selfPowered
    ee232h.remoteWakeup = eeData.remoteWakeup
    ee232h.pullDownEnable = eeData.pullDownEnableH
    ee232h.serNumEnable = eeData.serNumEnableH
    ee232h.acSlowSlew = eeData.acSlowSlewH
    ee232h.acSchmittInput = eeData.acSchmittInputH
    ee232h.acDriveCurrent = eeData.acDriveCurrentH
    ee232h.adSlowSlew = eeData.adSlowSlewH
    ee232h.adSchmittInput = eeData.adSchmittInputH
    ee232h.adDriveCurrent = eeData.adDriveCurrentH
    ee232h.cbus0 = eeData.cbus0H
    ee232h.cbus1 = eeData.cbus1H
    ee232h.cbus2 = eeData.cbus2H
    ee232h.cbus3 = eeData.cbus3H
    ee232h.cbus4 = eeData.cbus4H
    ee232h.cbus5 = eeData.cbus5H
    ee232h.cbus6 = eeData.cbus6H
    ee232h.cbus7 = eeData.cbus7H
    ee232h.cbus8 = eeData.cbus8H
    ee232h.cbus9 = eeData.cbus9H
    ee232h.isFifo = eeData.isFifoH
    ee232h.isFifoTar = eeData.isFifoTarH
    ee232h.isFastSer = eeData.isFastSerH
    ee232h.ft1248Cpol = eeData.ft1248CpolH
    ee232h.ft1248Lsb = eeData.ft1248LsbH
    ee232h.ft1248FlowControl = eeData.ft1248FlowControlH
    ee232h.isVCP = eeData.isVCPH
    ee232h.powerSaveEnable = eeData.powerSaveEnableH
    return ee232h
  }
}

class FtException extends Error {
}

/**
 * Method to check ftStatus and ftErrorCondition values for error conditions and throw exceptions accordingly
 * @param {FT_STATUS} ftStatus
 * @param {FT_ERROR} ftErrorCondition
 * @ignore
 */
function errorHandler (ftStatus, ftErrorCondition) {
  if (ftStatus !== FT_STATUS.FT_OK) {
    // Check FT_STATUS values returned from FTD2XX DLL calls
    switch (ftStatus) {
      case FT_STATUS.FT_DEVICE_NOT_FOUND:
        throw new FtException('FTDI device not found')
      case FT_STATUS.FT_DEVICE_NOT_OPENED:
        throw new FtException('FTDI device not opened')
      case FT_STATUS.FT_DEVICE_NOT_OPENED_FOR_ERASE:
        throw new FtException('FTDI device not opened for erase')
      case FT_STATUS.FT_DEVICE_NOT_OPENED_FOR_WRITE:
        throw new FtException('FTDI device not opened for write')
      case FT_STATUS.FT_EEPROM_ERASE_FAILED:
        throw new FtException('Failed to erase FTDI device EEPROM')
      case FT_STATUS.FT_EEPROM_NOT_PRESENT:
        throw new FtException('No EEPROM fitted to FTDI device')
      case FT_STATUS.FT_EEPROM_NOT_PROGRAMMED:
        throw new FtException('FTDI device EEPROM not programmed')
      case FT_STATUS.FT_EEPROM_READ_FAILED:
        throw new FtException('Failed to read FTDI device EEPROM')
      case FT_STATUS.FT_EEPROM_WRITE_FAILED:
        throw new FtException('Failed to write FTDI device EEPROM')
      case FT_STATUS.FT_FAILED_TO_WRITE_DEVICE:
        throw new FtException('Failed to write to FTDI device')
      case FT_STATUS.FT_INSUFFICIENT_RESOURCES:
        throw new FtException('Insufficient resources')
      case FT_STATUS.FT_INVALID_ARGS:
        throw new FtException('Invalid arguments for FTD2XX function call')
      case FT_STATUS.FT_INVALID_BAUD_RATE:
        throw new FtException('Invalid Baud rate for FTDI device')
      case FT_STATUS.FT_INVALID_HANDLE:
        throw new FtException('Invalid handle for FTDI device')
      case FT_STATUS.FT_INVALID_PARAMETER:
        throw new FtException('Invalid parameter for FTD2XX function call')
      case FT_STATUS.FT_IO_ERROR:
        throw new FtException('FTDI device IO error')
      case FT_STATUS.FT_OTHER_ERROR:
        throw new FtException('An unexpected error has occurred when trying to communicate with the FTDI device')
    }
  } else if (ftErrorCondition !== FT_ERROR.FT_NO_ERROR) {
    // Check for other error conditions not handled by FTD2XX DLL
    switch (ftErrorCondition) {
      case FT_ERROR.FT_INCORRECT_DEVICE:
        throw new FtException('The current device type does not match the EEPROM structure')
      case FT_ERROR.FT_INVALID_BITMODE:
        throw new FtException('The requested bit mode is not valid for the current device')
      case FT_ERROR.FT_BUFFER_SIZE:
        throw new FtException('The supplied buffer is not big enough')
    }
  }
}

/**
 * Class wrapper for FTD2XX.DLL
 */
class FTDI {
  constructor () {
    /**
     * @type {object}
     * @private
     */
    this._ftHandle = null
  }

  _setUpFtdiDeviceSync () {
    // Initialise port data characteristics
    const wordLength = FT_DATA_BITS.FT_BITS_8
    const stopBits = FT_STOP_BITS.FT_STOP_BITS_1
    const parity = FT_PARITY.FT_PARITY_NONE
    let ftStatus = _ftdiAddon.setDataCharacteristicsSync(this._ftHandle, wordLength, stopBits, parity)
    if (ftStatus !== FT_STATUS.FT_OK) return ftStatus
    const flowControl = FT_FLOW_CONTROL.FT_FLOW_NONE
    const xon = 0x11
    const xoff = 0x13
    ftStatus = _ftdiAddon.setFlowControlSync(this._ftHandle, flowControl, xon, xoff)
    if (ftStatus !== FT_STATUS.FT_OK) return ftStatus
    // Initialise Baud rate
    const baudRate = 9600
    return _ftdiAddon.setBaudRateSync(this._ftHandle, baudRate)
  }

  async _setUpFtdiDevice () {
    // Initialise port data characteristics
    const wordLength = FT_DATA_BITS.FT_BITS_8
    const stopBits = FT_STOP_BITS.FT_STOP_BITS_1
    const parity = FT_PARITY.FT_PARITY_NONE
    let ftStatus = await _ftdiAddon.setDataCharacteristics(this._ftHandle, wordLength, stopBits, parity)
    if (ftStatus !== FT_STATUS.FT_OK) return ftStatus
    const flowControl = FT_FLOW_CONTROL.FT_FLOW_NONE
    const xon = 0x11
    const xoff = 0x13
    ftStatus = await _ftdiAddon.setFlowControl(this._ftHandle, flowControl, xon, xoff)
    if (ftStatus !== FT_STATUS.FT_OK) return ftStatus
    // Initialise Baud rate
    const baudRate = 9600
    return _ftdiAddon.setBaudRate(this._ftHandle, baudRate)
  }

  _openAndSetupSync (openFuncSync) {
    let { ftStatus, ftHandle } = openFuncSync()
    if (ftStatus === FT_STATUS.FT_OK && ftHandle) {
      this._ftHandle = ftHandle
      ftStatus = this._setUpFtdiDeviceSync()
    } else {
      this._ftHandle = null
    }
    return ftStatus
  }

  async _openAndSetup (openFunc) {
    let { ftStatus, ftHandle } = await openFunc()
    if (ftStatus === FT_STATUS.FT_OK && ftHandle) {
      this._ftHandle = ftHandle
      ftStatus = await this._setUpFtdiDevice()
    } else {
      this._ftHandle = null
    }
    return ftStatus
  }

  /**
   * @typedef {object} GetNumberOfDevicesResult
   * @property {FT_STATUS} ftStatus Value from FT_CreateDeviceInfoList
   * @property {number} devCount The number of FTDI devices available
   */
  /**
   * Synchronously gets the number of FTDI devices available
   * @returns {GetNumberOfDevicesResult}
   */
  static getNumberOfDevicesSync () {
    return _ftdiAddon.createDeviceInfoListSync()
  }

  /**
   * Asynchronously gets the number of FTDI devices available
   * @returns {Promise<GetNumberOfDevicesResult>}
   */
  static getNumberOfDevices () {
    return _ftdiAddon.createDeviceInfoList()
  }

  /**
   * Type that holds device information for GetDeviceInfoDetail method
   * @typedef {object} DeviceInfoNode
   * @property {FT_FLAGS} flags Indicates device state. Can be any combination of the following:
   * FT_FLAGS.FT_FLAGS_OPENED, FT_FLAGS.FT_FLAGS_HISPEED
   * @property {FT_DEVICE} type Indicates the device type. Can be one of the following: FT_DEVICE_232R, FT_DEVICE_2232C,
   * FT_DEVICE_BM, FT_DEVICE_AM, FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
   * @property {number} id The Vendor ID and Product ID of the device
   * @property {number} locId The physical location identifier of the device
   * @property {string} serialNumber The device serial number
   * @property {string} description The device description
   * @property {object} [ftHandle] This value is not used externally and is provided for information only.
   * If the device is not open, ftHandle is undefined
   */

  /**
   * @typedef {object} GetDeviceListResult
   * @property {FT_STATUS} ftStatus Value from FT_GetDeviceInfoDetail
   * @property {DeviceInfoNode[]} deviceList
   */
  /**
   * Synchronously gets information on all of the FTDI devices available
   * @returns {GetDeviceListResult}
   */
  static getDeviceListSync () {
    const deviceList = []
    let { ftStatus, devCount } = _ftdiAddon.createDeviceInfoListSync()
    for (let i = 0; i < devCount; ++i) {
      const obj = _ftdiAddon.getDeviceInfoDetailSync(i)
      ftStatus = obj.ftStatus
      deviceList[i] = obj.deviceInfoNode
    }
    return { ftStatus, deviceList }
  }

  /**
   * Asynchronously gets information on all of the FTDI devices available
   * @returns {Promise<GetDeviceListResult>}
   */
  static async getDeviceList () {
    const deviceList = []
    let { ftStatus, devCount } = await _ftdiAddon.createDeviceInfoList()
    for (let i = 0; i < devCount; ++i) {
      const obj = await _ftdiAddon.getDeviceInfoDetail(i)
      ftStatus = obj.ftStatus
      deviceList[i] = obj.deviceInfoNode
    }
    return { ftStatus, deviceList }
  }

  /**
   * Synchronously opens the FTDI device with the specified index.
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} index Index of the device to open,
   * note that this cannot be guaranteed to open a specific device
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   */
  openByIndexSync (index) {
    return this._openAndSetupSync(() => _ftdiAddon.openSync(index))
  }

  /**
   * Asynchronously opens the FTDI device with the specified index.
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} index Index of the device to open,
   * note that this cannot be guaranteed to open a specific device
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   */
  openByIndex (index) {
    return this._openAndSetup(() => _ftdiAddon.open(index))
  }

  /**
   * Synchronously opens the FTDI device with the specified serial number
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} serialNumber Serial number of the device to open
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   */
  openBySerialNumberSync (serialNumber) {
    return this._openAndSetupSync(() => _ftdiAddon.openExSync(serialNumber, FT_OPEN_BY_SERIAL_NUMBER))
  }

  /**
   * Asynchronously opens the FTDI device with the specified serial number
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} serialNumber Serial number of the device to open
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   */
  openBySerialNumber (serialNumber) {
    return this._openAndSetup(() => _ftdiAddon.openEx(serialNumber, FT_OPEN_BY_SERIAL_NUMBER))
  }

  /**
   * Synchronously opens the FTDI device with the specified description
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} description Description of the device to open
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   */
  openByDescriptionSync (description) {
    return this._openAndSetupSync(() => _ftdiAddon.openExSync(description, FT_OPEN_BY_DESCRIPTION))
  }

  /**
   * Asynchronously opens the FTDI device with the specified description
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} description Description of the device to open
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   */
  openByDescription (description) {
    return this._openAndSetup(() => _ftdiAddon.openEx(description, FT_OPEN_BY_DESCRIPTION))
  }

  /**
   * Synchronously opens the FTDI device at the specified physical location
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} location Location of the device to open
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   */
  openByLocationSync (location) {
    return this._openAndSetupSync(() => _ftdiAddon.openExSync(location, FT_OPEN_BY_LOCATION))
  }

  /**
   * Asynchronously opens the FTDI device at the specified physical location
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} location Location of the device to open
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   */
  openByLocation (location) {
    return this._openAndSetup(() => _ftdiAddon.openEx(location, FT_OPEN_BY_LOCATION))
  }

  /**
   * Synchronously closes the handle to an open FTDI device
   * @returns {FT_STATUS} ftStatus Value from FT_Close
   */
  closeSync () {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    const ftStatus = _ftdiAddon.closeSync(this._ftHandle)
    return ftStatus
  }

  /**
   * Asynchronously closes the handle to an open FTDI device
   * @returns {Promise<FT_STATUS>} ftStatus Value from FT_Close
   */
  close () {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.close(this._ftHandle)
  }

  /**
   * @typedef {object} GetDeviceInfoResulte
   * @property {FT_STATUS} ftStatus Value from FT_GetDeviceInfoDetail
   * @property {FT_DEVICE} type Indicates the device type. Can be one of the following: FT_DEVICE_232R,
   * FT_DEVICE_2232C, FT_DEVICE_BM, FT_DEVICE_AM, FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
   * @property {number} id The device ID (Vendor ID and Product ID) of the current device
   * @property {string} serialNumber The device serial number
   * @property {string} description The device description
   */
  /**
   * Synchronously gets device information for an open device
   * @returns {GetDeviceInfoResult}
   */
  getDeviceInfoSync () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.getDeviceInfoSync(this._ftHandle)
  }

  /**
   * Asynchronously gets device information for an open device
   * @returns {GetDeviceInfoResult}
   */
  getDeviceInfo () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.getDeviceInfo(this._ftHandle)
  }

  /**
   * Synchronously sets the data bits, stop bits and parity for the device
   * @param {FT_DATA_BITS} wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or
   * FT_DATA_BITS.FT_BITS_8
   * @param {FT_STOP_BITS} stopBits The number of stop bits for UART data.
   * Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
   * @param {FT_PARITY} parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE,
   * FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
   * @returns {FT_STATUS} ftStatus ftStatus value from FT_SetDataCharacteristics
   */
  setDataCharacteristicsSync (wordLength, stopBits, parity) {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.setDataCharacteristicsSync(this._ftHandle, wordLength, stopBits, parity)
  }

  /**
   * Asynchronously sets the data bits, stop bits and parity for the device
   * @param {FT_DATA_BITS} wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or
   * FT_DATA_BITS.FT_BITS_8
   * @param {FT_STOP_BITS} stopBits The number of stop bits for UART data. Valid values are FT_STOP_BITS.FT_STOP_BITS_1
   * or FT_STOP_BITS.FT_STOP_BITS_2
   * @param {FT_PARITY} parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE,
   * FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
   * @returns {Promise<FT_STATUS>} ftStatus ftStatus value from FT_SetDataCharacteristics
   */
  setDataCharacteristics (wordLength, stopBits, parity) {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.setDataCharacteristics(this._ftHandle, wordLength, stopBits, parity)
  }

  /**
   * Synchronously sets the flow control type
   * @param {FT_FLOW_CONTROL} flowControl The type of flow control for the UART. Valid values are
   * FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or
   * FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
   * @param {number} xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @param {number} xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @returns {FT_STATUS} ftStatus Value from FT_SetFlowControl
   */
  setFlowControlSync (flowControl, xon, xoff) {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.setFlowControlSync(this._ftHandle, flowControl, xon, xoff)
  }

  /**
   * Asynchronously sets the flow control type
   * @param {FT_FLOW_CONTROL} flowControl The type of flow control for the UART. Valid values are
   * FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or
   * FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
   * @param {number} xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @param {number} xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @returns {Promise<FT_STATUS>} ftStatus Value from FT_SetFlowControl
   */
  setFlowControl (flowControl, xon, xoff) {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.setFlowControl(this._ftHandle, flowControl, xon, xoff)
  }

  /**
   * Synchronously sets the current Baud rate
   * @param {number} baudRate The desired Baud rate for the device
   * @returns {FT_STATUS} ftStatus Value from FT_SetBaudRate
   */
  setBaudRateSync (baudRate) {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.setBaudRateSync(this._ftHandle, baudRate)
  }

  /**
   * Asynchronously sets the current Baud rate
   * @param {number} baudRate The desired Baud rate for the device
   * @returns {Promise<FT_STATUS>} ftStatus Value from FT_SetBaudRate
   */
  setBaudRate (baudRate) {
    if (!this._ftHandle) return FT_STATUS.FT_OTHER_ERROR
    return _ftdiAddon.setBaudRate(this._ftHandle, baudRate)
  }

  /**
   * @typedef {object} GetQueueStatusResult
   * @property {FT_STATUS} ftStatus Value from FT_GetQueueStatus
   * @property {number} [rxQueue] The number of bytes available to be read
   */
  /**
   * Synchronously gets the number of bytes available in the receive buffer
   * @returns {GetQueueStatusResult}
   */
  getQueueStatusSync () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.getQueueStatusSync(this._ftHandle)
  }

  /**
   * Asynchronously gets the number of bytes available in the receive buffer
   * @returns {Promise<GetQueueStatusResult>}
   */
  getQueueStatus () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.getQueueStatus(this._ftHandle)
  }

  /**
   * @typedef {object} GetStatusResult
   * @property {FT_STATUS} ftStatus Value from FT_GetStatus
   * @property {number} rxQueue The number of bytes available to be read
   * @property {number} txQueue The number of bytes waiting to be sent
   * @property {number} eventStatus The type of event that has occurred
   */
  /**
   * Synchronously gets the device status including number of characters in the receive queue,
   * number of characters in the transmit queue, and the current event status
   * @returns {GetStatusResult}
   */
  getStatusSync () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.getStatusSync(this._ftHandle)
  }

  /**
   * Asynchronously gets the device status including number of characters in the receive queue,
   * number of characters in the transmit queue, and the current event status
   * @returns {Promise<GetStatusResult>}
   */
  getStatus () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.getStatus(this._ftHandle)
  }

  /**
   * @typedef {object} WriteResult
   * @property {FT_STATUS} ftStatus Value from FT_Write
   * @property {number} numBytesWritten The number of bytes actually written to the device
   */
  /**
   * Synchronously write data to an open FTDI device
   * @param {Buffer} txBuffer An array of bytes which contains the data to be written to the device
   * @param {number} [numBytesToWrite] The number of bytes to be written to the device
   * @returns {WriteResult}
   */
  writeSync (txBuffer, numBytesToWrite) {
    numBytesToWrite = numBytesToWrite || txBuffer.byteLength
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.writeSync(this._ftHandle, txBuffer, numBytesToWrite)
  }

  /**
   * Asynchronously write data to an open FTDI device
   * @param {Buffer} txBuffer An array of bytes which contains the data to be written to the device
   * @param {number} [numBytesToWrite] The number of bytes to be written to the device
   * @returns {Promise<WriteResult>}
   */
  write (txBuffer, numBytesToWrite) {
    numBytesToWrite = numBytesToWrite || txBuffer.byteLength
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.write(this._ftHandle, txBuffer, numBytesToWrite)
  }

  /**
   * @typedef {object} ReadResult
   * @property {FT_STATUS} ftStatus Value from FT_Read
   * @property {Buffer} rxBuffer An array of bytes which was populated with the data read from the device
   * @property {number} numBytesRead The number of bytes actually read
   */
  /**
   * Synchronously read data from an open FTDI device
   * @param {Buffer} rxBuffer An array of bytes which will be populated with the data read from the device
   * @param {number} [numBytesToRead] The number of bytes requested from the device
   * @returns {ReadResult}
   */
  readSync (rxBuffer, numBytesToRead) {
    numBytesToRead = numBytesToRead || rxBuffer.byteLength
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.readSync(this._ftHandle, rxBuffer, numBytesToRead)
  }

  /**
   * Asynchronously read data from an open FTDI device
   * @param {Buffer} rxBuffer An array of bytes which will be populated with the data read from the device
   * @param {number} [numBytesToRead] The number of bytes requested from the device
   * @returns {Promise<ReadResult>}
   */
  read (rxBuffer, numBytesToRead) {
    numBytesToRead = numBytesToRead || rxBuffer.byteLength
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    return _ftdiAddon.read(this._ftHandle, rxBuffer, numBytesToRead)
  }

  /**
   * @typedef {object} ReadFT232HEEPROMResult
   * @property {FT_STATUS} ftStatus Value from FT_EE_Read
   * @property {FT232H_EEPROM_STRUCTURE} [ee232h] An FT232H_EEPROM_STRUCTURE which contains only the relevant
   * information for an FT232H device
   */
  /**
   * Synchronously reads the EEPROM contents of an FT232H device
   * @returns {ReadFT232HEEPROMResult}
   * @throws {FtException} Thrown when the current device does not match the type required by this method
   */
  readFT232HEEPROMSync () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    let { ftStatus, ftDevice } = _ftdiAddon.getDeviceInfoSync(this._ftHandle)
    if (ftDevice !== FT_DEVICE.FT_DEVICE_232H) {
      errorHandler(ftStatus, FT_ERROR.FT_INCORRECT_DEVICE)
    }
    /** * @type {FT_PROGRAM_DATA} */
    const eeData = new _ftdiAddon.FT_PROGRAM_DATA()
    eeData.signature1 = 0x00000000
    eeData.signature2 = 0xFFFFFFFF
    eeData.version = 5
    ftStatus = _ftdiAddon.eeReadSync(this._ftHandle, eeData)
    const ee232h = FtEeUtils.CreateEe232h(eeData)
    return { ftStatus, ee232h }
  }

  /**
   * Asynchronously reads the EEPROM contents of an FT232H device
   * @returns {Promise<ReadFT232HEEPROMResult>}
   * @throws {FtException} Thrown when the current device does not match the type required by this method
   */
  async readFT232HEEPROM () {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    let { ftStatus, ftDevice } = await _ftdiAddon.getDeviceInfo(this._ftHandle)
    if (ftDevice !== FT_DEVICE.FT_DEVICE_232H) {
      errorHandler(ftStatus, FT_ERROR.FT_INCORRECT_DEVICE)
    }
    /** * @type {FT_PROGRAM_DATA} */
    const eeData = new _ftdiAddon.FT_PROGRAM_DATA()
    eeData.signature1 = 0x00000000
    eeData.signature2 = 0xFFFFFFFF
    eeData.version = 5
    ftStatus = await _ftdiAddon.eeReadSync(this._ftHandle, eeData)
    const ee232h = FtEeUtils.CreateEe232h(eeData)
    return { ftStatus, ee232h }
  }

  /**
   *
   * @param {FT_DEVICE} ftDevice
   * @param {number} bitMode
   * @returns {boolean}
   * @private
   */
  _canSetBitMode (ftDevice, bitMode) {
    switch (ftDevice) {
      case FT_DEVICE.FT_DEVICE_AM:
      case FT_DEVICE.FT_DEVICE_100AX:
        return false
      case FT_DEVICE.FT_DEVICE_BM:
        if (bitMode !== FT_BIT_MODES.FT_BIT_MODE_RESET &&
          (bitMode & (FT_BIT_MODES.FT_BIT_MODE_ASYNC_BITBANG)) === 0) {
          return false
        }
        break
    }
    return true
  }

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
   * @returns {FT_STATUS}
   * @throws {FtException} Thrown when the current device does not support the requested bit mode
   */
  setBitModeSync (mask, bitMode) {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    const { ftStatus, ftDevice } = _ftdiAddon.getDeviceInfoSync(this._ftHandle)
    if (ftStatus !== FT_STATUS.FT_OK) {
      return ftStatus
    }
    if (!this._canSetBitMode(ftDevice, bitMode)) errorHandler(ftStatus, FT_ERROR.FT_INVALID_BITMODE)
    return _ftdiAddon.setBitModeSync(this._ftHandle, mask, bitMode)
  }

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
   * @returns {Promise<FT_STATUS>}
   * @throws {FtException} Thrown when the current device does not support the requested bit mode
   */
  async setBitMode (mask, bitMode) {
    if (!this._ftHandle) return { ftStatus: FT_STATUS.FT_OTHER_ERROR }
    const { ftStatus, ftDevice } = await _ftdiAddon.getDeviceInfo(this._ftHandle)
    if (ftStatus !== FT_STATUS.FT_OK) {
      return ftStatus
    }
    if (!this._canSetBitMode(ftDevice, bitMode)) errorHandler(ftStatus, FT_ERROR.FT_INVALID_BITMODE)
    return _ftdiAddon.setBitMode(this._ftHandle, mask, bitMode)
  }
}

module.exports = {
  FT_STATUS,
  FT_DEVICE,
  FT_FLAGS,
  FT_DATA_BITS,
  FT_STOP_BITS,
  FT_PARITY,
  FT_FLOW_CONTROL,
  FT_DRIVE_CURRENT,
  FT_232H_CBUS_OPTIONS,
  FTDI
}
