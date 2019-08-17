'use strict'
const assert = require('assert')
const FTD2XX = require('./../index')

describe('Tests getNumberOfDevices', () => {
  const numberOfDevices = FTD2XX.FTDI.getNumberOfDevices()
  it('FTDI.getNumberOfDevices().ftStatus should equal FTD2XX.FT_STATUS.FT_OK', () => {
    assert.strictEqual(numberOfDevices.ftStatus, FTD2XX.FT_STATUS.FT_OK)
  })
  it('FTDI.getNumberOfDevices().devCount should equal 0', () => {
    assert.strictEqual(numberOfDevices.devCount, 0)
  })
})

describe('Tests getDeviceList', () => {
  it('FTDI.getDeviceList().ftStatus should equal FTD2XX.FT_STATUS.FT_OK', () => {
    assert.strictEqual(deviceList.ftStatus, FTD2XX.FT_STATUS.FT_OK)
  })
  it('FTDI.getDeviceList().deviceInfoList.length should equal 0', () => {
    assert.strictEqual(deviceList.deviceInfoList.length, 0)
  })
})

describe('Tests ftdi open', () => {
  const ftdi = new FTD2XX.FTDI()
  ftdi.close()
  it('FTDI.openByIndex(0) should return object', () => {
    assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_INVALID_HANDLE)
  })
  it('FTDI.openByDescription(\'test\') should return object', () => {
    assert.strictEqual(ftdi.openByDescription('test'), FTD2XX.FT_STATUS.FT_INVALID_HANDLE)
  })
  it('FTDI.openBySerialNumber(\'test\') should return object', () => {
    assert.strictEqual(ftdi.openBySerialNumber('test'), FTD2XX.FT_STATUS.FT_INVALID_HANDLE)
  })
  it('FTDI.openByLocation(0x01) should return object', () => {
    assert.strictEqual(ftdi.openByLocation(0x01), FTD2XX.FT_STATUS.FT_INVALID_HANDLE)
  })
})
