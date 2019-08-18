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
 * Common EEPROM elements for all devices. Inherited to specific device type EEPROMs
 * @property {number} vendorID=0x0403 Vendor ID as supplied by the USB Implementers Forum
 * @property {number} productID=0x6001 Product ID
 * @property {string} manufacturer="FTDI" Manufacturer name string
 * @property {string} manufacturerID="FT" Manufacturer name abbreviation to be used as a prefix for automatically generated serial numbers
 * @property {string} description="USB-Serial Converter" Device description string
 * @property {string} serialNumber="" Device serial number string
 * @property {number} maxPower=0x0090 Maximum power the device needs
 * @property {boolean} selfPowered=false Indicates if the device has its own power supply (self-powered) or gets power from the USB port (bus-powered)
 * @property {boolean} remoteWakeup=false Determines if the device can wake the host PC from suspend by toggling the RI line
 */
class FT_EEPROM_DATA {
  constructor () {
    this.vendorID = 0x0403
    this.productID = 0x6001
    this.manufacturer = 'FTDI'
    this.manufacturerID = 'FT'
    this.description = 'USB-Serial Converter'
    this.serialNumber = ''
    this.maxPower = 0x0090
    this.selfPowered = _ftdiAddon
    this.remoteWakeup = false
  }
}

/**
 * EEPROM structure specific to FT232H devices
 * @property {boolean} pullDownEnable=false Determines if IOs are pulled down when the device is in suspend
 * @property {boolean} serNumEnable=true Determines if the serial number is enabled
 * @property {boolean} acSlowSlew=false Determines if AC pins have a slow slew rate
 * @property {boolean} acSchmittInput=false Determines if the AC pins have a Schmitt input
 * @property {FT_DRIVE_CURRENT} acDriveCurrent=FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA Determines the AC pins drive current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or FT_DRIVE_CURRENT_16MA
 * @property {boolean} adSlowSlew=false Determines if AD pins have a slow slew rate
 * @property {boolean} adSchmittInput=false Determines if the AD pins have a Schmitt input
 * @property {FT_DRIVE_CURRENT} adDriveCurrent=FT_DRIVE_CURRENT.FT_DRIVE_CURRENT_4MA Determines the AD pins drive current in mA. Valid values are FT_DRIVE_CURRENT_4MA, FT_DRIVE_CURRENT_8MA, FT_DRIVE_CURRENT_12MA or FT_DRIVE_CURRENT_16MA
 * @property {FT_232H_CBUS_OPTIONS} cbus0=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS0 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus1=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS1 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus2=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS2 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN
 * @property {FT_232H_CBUS_OPTIONS} cbus3=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS3 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN
 * @property {FT_232H_CBUS_OPTIONS} cbus4=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS4 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_TXDEN
 * @property {FT_232H_CBUS_OPTIONS} cbus5=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS5 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus6=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS6 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus7=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS7 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE
 * @property {FT_232H_CBUS_OPTIONS} cbus8=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS8 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {FT_232H_CBUS_OPTIONS} cbus9=FT_232H_CBUS_OPTIONS.FT_CBUS_TRISTATE Sets the function of the CBUS9 pin for FT232H devices. Valid values are FT_CBUS_TRISTATE, FT_CBUS_RXLED, FT_CBUS_TXLED, FT_CBUS_TXRXLED, FT_CBUS_PWREN, FT_CBUS_SLEEP, FT_CBUS_DRIVE_0, FT_CBUS_DRIVE_1, FT_CBUS_IOMODE, FT_CBUS_TXDEN, FT_CBUS_CLK30, FT_CBUS_CLK15, FT_CBUS_CLK7_5
 * @property {boolean} isFifo=false Determines if the device is in FIFO mode
 * @property {boolean} isFifoTar=false Determines if the device is in FIFO target mode
 * @property {boolean} isFastSer=false Determines if the device is in fast serial mode
 * @property {boolean} isFT1248=false Determines if the device is in FT1248 mode
 * @property {boolean} ft1248Cpol=false Determines FT1248 mode clock polarity
 * @property {boolean} ft1248Lsb=false Determines if data is ent MSB (0) or LSB (1) in FT1248 mode
 * @property {boolean} ft1248FlowControl=false Determines if FT1248 mode uses flow control
 * @property {boolean} isVCP=true Determines if the VCP driver is loaded
 * @property {boolean} powerSaveEnable=false For self-powered designs, keeps the FT232H in low power state until ACBUS7 is high
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
    this.ft1248FlowControl = false
    this.isVCP = true
    this.powerSaveEnable = false
  }
}

let ftdiIsBisy = false
class FtdiParallelInvocationError extends Error {}
class FtException extends Error {}

function throwErrorIfBusySync (func) {
  if (!ftdiIsBisy) {
    try {
      ftdiIsBisy = true
      return func()
    } finally {
      ftdiIsBisy = false
    }
  }
  throw new FtdiParallelInvocationError('Another FTDI method already invoked')
}

async function throwErrorIfBusy (func) {
  if (!ftdiIsBisy) {
    try {
      ftdiIsBisy = true
      return await func()
    } finally {
      ftdiIsBisy = false
    }
  }
  throw new FtdiParallelInvocationError('Another FTDI method already invoked')
}

/**
 * Method to check ftStatus and ftErrorCondition values for error conditions and throw exceptions accordingly
 * @param {FT_STATUS} ftStatus
 * @param {FT_ERROR} ftErrorCondition
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
     * @type {FtHandle}
     * @private
     */
    this._ftHandle = null
  }

  _checkFtHandleSync (invokeIfOk) {
    let ftStatus = FT_STATUS.FT_OTHER_ERROR
    if (this._ftHandle != null && this._ftHandle.value !== 0) {
      ftStatus = invokeIfOk()
    }
    return ftStatus
  }

  async _checkFtHandle (invokeIfOk) {
    let ftStatus = FT_STATUS.FT_OTHER_ERROR
    if (this._ftHandle != null && this._ftHandle.value !== 0) {
      ftStatus = await invokeIfOk()
    }
    return ftStatus
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
    if (ftStatus === FT_STATUS.FT_OK || ftHandle.value !== 0) {
      this._ftHandle = ftHandle
      ftStatus = this._setUpFtdiDeviceSync()
    } else {
      this._ftHandle = null
    }
    return ftStatus
  }

  async _openAndSetup (openFunc) {
    let { ftStatus, ftHandle } = await openFunc()
    if (ftStatus === FT_STATUS.FT_OK || ftHandle.value !== 0) {
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
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  static getNumberOfDevicesSync () {
    return throwErrorIfBusySync(_ftdiAddon.createDeviceInfoListSync)
  }

  /**
   * Asynchronously gets the number of FTDI devices available
   * @returns {Promise<GetNumberOfDevicesResult>}
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  static async getNumberOfDevices () {
    return throwErrorIfBusy(_ftdiAddon.createDeviceInfoList)
  }

  /**
   * Contain pointer to a variable of type FT_HANDLE where the handle will be stored. This handle must be used to access the device.
   * @typedef {object} FtHandle
   */
  /**
   * Mark handle as free
   * @function
   * @name FtHandle#free
   */
  /**
   * Type that holds device information for GetDeviceInfoDetail method
   * @typedef {object} DeviceInfoDetail
   * @property {FT_FLAGS} flags Indicates device state. Can be any combination of the following: FT_FLAGS.FT_FLAGS_OPENED, FT_FLAGS.FT_FLAGS_HISPEED
   * @property {FT_DEVICE} type Indicates the device type. Can be one of the following: FT_DEVICE_232R, FT_DEVICE_2232C, FT_DEVICE_BM, FT_DEVICE_AM, FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
   * @property {number} id The Vendor ID and Product ID of the device
   * @property {number} locId The physical location identifier of the device
   * @property {string} serialNumber The device serial number
   * @property {string} description The device description
   * @property {?FtHandle} ftHandle This value is not used externally and is provided for information only. If the device is not open, ftHandle is null
   */
  /**
   * @typedef {object} GetDeviceListResult
   * @property {FT_STATUS} ftStatus Value from FT_GetDeviceInfoDetail
   * @property {Array.<DeviceInfoDetail>} deviceInfoList
   */
  /**
   * Synchronously gets information on all of the FTDI devices available
   * @returns {GetDeviceListResult}
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  static getDeviceListSync () {
    return throwErrorIfBusySync(() => {
      const deviceInfoList = []
      let { ftStatus, devCount } = _ftdiAddon.createDeviceInfoListSync()
      for (let i = 0; i < devCount; ++i) {
        const deviceInfoDetail = _ftdiAddon.getDeviceInfoDetailSync(i)
        ftStatus = deviceInfoDetail.ftStatus
        deviceInfoList[i] = deviceInfoDetail.deviceInfo
      }
      return { ftStatus, deviceInfoList }
    })
  }

  /**
   * Asynchronously gets information on all of the FTDI devices available
   * @returns {Promise<GetDeviceListResult>}
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  static async getDeviceList () {
    return throwErrorIfBusy(async () => {
      const deviceInfoList = []
      let { ftStatus, devCount } = await _ftdiAddon.createDeviceInfoList()
      for (let i = 0; i < devCount; ++i) {
        const deviceInfoDetail = await _ftdiAddon.getDeviceInfoDetail(i)
        ftStatus = deviceInfoDetail.ftStatus
        deviceInfoList[i] = deviceInfoDetail.deviceInfo
      }
      return { ftStatus, deviceInfoList }
    })
  }

  /**
   * Synchronously opens the FTDI device with the specified index.
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} index Index of the device to open,
   * note that this cannot be guaranteed to open a specific device
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  openByIndexSync (index) {
    return throwErrorIfBusySync(() => this._openAndSetupSync(() => _ftdiAddon.openSync(index)))
  }

  /**
   * Asynchronously opens the FTDI device with the specified index.
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} index Index of the device to open,
   * note that this cannot be guaranteed to open a specific device
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async openByIndex (index) {
    return throwErrorIfBusy(() => this._openAndSetup(() => _ftdiAddon.open(index)))
  }

  /**
   * Synchronously opens the FTDI device with the specified serial number
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} serialNumber Serial number of the device to open
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  openBySerialNumberSync (serialNumber) {
    return throwErrorIfBusySync(() => this._openAndSetupSync(() => _ftdiAddon.openExSync(serialNumber, FT_OPEN_BY_SERIAL_NUMBER)))
  }

  /**
   * Asynchronously opens the FTDI device with the specified serial number
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} serialNumber Serial number of the device to open
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async openBySerialNumber (serialNumber) {
    return throwErrorIfBusy(() => this._openAndSetup(() => _ftdiAddon.openEx(serialNumber, FT_OPEN_BY_SERIAL_NUMBER)))
  }

  /**
   * Synchronously opens the FTDI device with the specified description
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} description Description of the device to open
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  openByDescriptionSync (description) {
    return throwErrorIfBusySync(() => this._openAndSetupSync(() => _ftdiAddon.openExSync(description, FT_OPEN_BY_DESCRIPTION)))
  }

  /**
   * Asynchronously opens the FTDI device with the specified description
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {string} description Description of the device to open
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async openByDescription (description) {
    return throwErrorIfBusy(() => this._openAndSetup(() => _ftdiAddon.openEx(description, FT_OPEN_BY_DESCRIPTION)))
  }

  /**
   * Synchronously opens the FTDI device at the specified physical location
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} location Location of the device to open
   * @returns {FT_STATUS} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  openByLocationSync (location) {
    return throwErrorIfBusySync(() => this._openAndSetupSync(() => _ftdiAddon.openExSync(location, FT_OPEN_BY_LOCATION)))
  }

  /**
   * Asynchronously opens the FTDI device at the specified physical location
   * Initialises the device to 8 data bits, 1 stop bit, no parity, no flow control and 9600 Baud
   * @param {number} location Location of the device to open
   * @returns {Promise<FT_STATUS>} ftStatus Status values for FTDI device
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async openByLocation (location) {
    return throwErrorIfBusy(() => this._openAndSetup(() => _ftdiAddon.openEx(location, FT_OPEN_BY_LOCATION)))
  }

  /**
   * Synchronously closes the handle to an open FTDI device
   * @returns {FT_STATUS} ftStatus Value from FT_Close
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  closeSync () {
    return throwErrorIfBusySync(() => {
      const ftStatus = this._checkFtHandleSync(() => _ftdiAddon.closeSync(this._ftHandle))
      if (ftStatus === FT_STATUS.FT_OK) {
        this._ftHandle.free()
        this._ftHandle = null
      }
      return ftStatus
    })
  }

  /**
   * Asynchronously closes the handle to an open FTDI device
   * @returns {Promise<FT_STATUS>} ftStatus Value from FT_Close
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async close () {
    return throwErrorIfBusy(async () => {
      const ftStatus = await this._checkFtHandle(() => _ftdiAddon.close(this._ftHandle))
      if (ftStatus === FT_STATUS.FT_OK) {
        this._ftHandle.free()
        this._ftHandle = null
      }
      return ftStatus
    })
  }

  /**
   * @typedef {object} GetDeviceInfoResult
   * @property {FT_STATUS} ftStatus Value from FT_GetDeviceInfoDetail
   * @property {FT_DEVICE} ftDevice Indicates the device type. Can be one of the following: FT_DEVICE_232R, FT_DEVICE_2232C, FT_DEVICE_BM, FT_DEVICE_AM, FT_DEVICE_100AX or FT_DEVICE_UNKNOWN
   * @property {number} deviceID The device ID (Vendor ID and Product ID) of the current device
   * @property {string} serialNumber The device serial number
   * @property {string} description The device description
   */
  /**
   * Synchronously gets device information for an open device
   * @returns {GetDeviceInfoResult}
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  getDeviceInfoSync () {
    return throwErrorIfBusySync(() => this._checkFtHandleSync(() => _ftdiAddon.getDeviceInfoSync(this._ftHandle)))
  }

  /**
   * Asynchronously gets device information for an open device
   * @returns {GetDeviceInfoResult}
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  getDeviceInfo () {
    return throwErrorIfBusySync(() => this._checkFtHandle(() => _ftdiAddon.getDeviceInfo(this._ftHandle)))
  }

  /**
   * Synchronously sets the data bits, stop bits and parity for the device
   * @param {FT_DATA_BITS} wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or FT_DATA_BITS.FT_BITS_8
   * @param {FT_STOP_BITS} stopBits The number of stop bits for UART data. Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
   * @param {FT_PARITY} parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE, FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
   * @returns {FT_STATUS} ftStatus ftStatus value from FT_SetDataCharacteristics
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  setDataCharacteristicsSync (wordLength, stopBits, parity) {
    return throwErrorIfBusySync(() => this._checkFtHandleSync(() => _ftdiAddon.setDataCharacteristicsSync(this._ftHandle, wordLength, stopBits, parity)))
  }

  /**
   * Asynchronously sets the data bits, stop bits and parity for the device
   * @param {FT_DATA_BITS} wordLength The number of data bits for UART data. Valid values are FT_DATA_BITS.FT_DATA_7 or FT_DATA_BITS.FT_BITS_8
   * @param {FT_STOP_BITS} stopBits The number of stop bits for UART data. Valid values are FT_STOP_BITS.FT_STOP_BITS_1 or FT_STOP_BITS.FT_STOP_BITS_2
   * @param {FT_PARITY} parity The parity of the UART data. Valid values are FT_PARITY.FT_PARITY_NONE, FT_PARITY.FT_PARITY_ODD, FT_PARITY.FT_PARITY_EVEN, FT_PARITY.FT_PARITY_MARK or FT_PARITY.FT_PARITY_SPACE
   * @returns {Promise<FT_STATUS>} ftStatus ftStatus value from FT_SetDataCharacteristics
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async setDataCharacteristics (wordLength, stopBits, parity) {
    return throwErrorIfBusy(() => this._checkFtHandle(() => _ftdiAddon.setDataCharacteristics(this._ftHandle, wordLength, stopBits, parity)))
  }

  /**
   * Synchronously sets the flow control type.
   * @param {FT_FLOW_CONTROL} flowControl The type of flow control for the UART. Valid values are FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
   * @param {number} xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @param {number} xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @returns {FT_STATUS} ftStatus Value from FT_SetFlowControl
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  setFlowControlSync (flowControl, xon, xoff) {
    return throwErrorIfBusySync(() => this._checkFtHandleSync(() => _ftdiAddon.setFlowControlSync(this._ftHandle, flowControl, xon, xoff)))
  }

  /**
   * Asynchronously sets the flow control type.
   * @param {FT_FLOW_CONTROL} flowControl The type of flow control for the UART. Valid values are FT_FLOW_CONTROL.FT_FLOW_NONE, FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, FT_FLOW_CONTROL.FT_FLOW_DTR_DSR or FT_FLOW_CONTROL.FT_FLOW_XON_XOFF
   * @param {number} xon The Xon character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @param {number} xoff The Xoff character for Xon/Xoff flow control. Ignored if not using Xon/XOff flow control
   * @returns {Promise<FT_STATUS>} ftStatus Value from FT_SetFlowControl
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async setFlowControl (flowControl, xon, xoff) {
    return throwErrorIfBusy(() => this._checkFtHandle(() => _ftdiAddon.setFlowControl(this._ftHandle, flowControl, xon, xoff)))
  }

  /**
   * Synchronously sets the current Baud rate.
   * @param {number} baudRate The desired Baud rate for the device
   * @returns {FT_STATUS} ftStatus Value from FT_SetBaudRate
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  setBaudRateSync (baudRate) {
    return throwErrorIfBusySync(() => this._checkFtHandleSync(() => _ftdiAddon.setBaudRateSync(this._ftHandle, baudRate)))
  }

  /**
   * Asynchronously sets the current Baud rate.
   * @param {number} baudRate The desired Baud rate for the device
   * @returns {Promise<FT_STATUS>} ftStatus Value from FT_SetBaudRate
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  async setBaudRate (baudRate) {
    return throwErrorIfBusy(() => this._checkFtHandle(() => _ftdiAddon.setBaudRate(this._ftHandle, baudRate)))
  }

  /**
   * @typedef {object} ReadFT232HEEPROMResult
   * @property {FT_STATUS} ftStatus Value from FT_EE_Read
   * @property {FT232H_EEPROM_STRUCTURE} ee232h An FT232H_EEPROM_STRUCTURE which contains only the relevant information for an FT232H device
   */
  /**
   * Reads the EEPROM contents of an FT232H device
   * @returns {ReadFT232HEEPROMResult}
   * @throws {FtdiParallelInvocationError} FTDI methods can not run parallel
   */
  readFT232HEEPROMSync () {
    return throwErrorIfBusy(() => this._checkFtHandle(() => {
      const { ftStatus, ftDevice } = this.getDeviceInfo()
      if (ftDevice !== FT_DEVICE.FT_DEVICE_232H) {
        errorHandler(ftStatus, FT_ERROR.FT_INCORRECT_DEVICE)
      }
    }))
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
