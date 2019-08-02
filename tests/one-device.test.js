'use strict';
const assert = require('assert');
let FTD2XX = require('./../index');

describe('Tests getNumberOfDevices', () => {
    let numberOfDevices = FTD2XX.FTDI.getNumberOfDevices();
    it('FTDI.getNumberOfDevices().ftStatus should equal FTD2XX.FT_STATUS.FT_OK', () => {
        assert.strictEqual(numberOfDevices.ftStatus, FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.getNumberOfDevices().devCount should equal 1', () => {
        assert.strictEqual(numberOfDevices.devCount, 1);
    });
});

describe('Tests getDeviceList', () => {
    let deviceList = FTD2XX.FTDI.getDeviceList();
    it('FTDI.getDeviceList().ftStatus should equal FTD2XX.FT_STATUS.FT_OK', () => {
        assert.strictEqual(deviceList.ftStatus, FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.getDeviceList().deviceInfoList.length should equal 1', () => {
        assert.strictEqual(deviceList.deviceInfoList.length, 1);
    });
    it('FTDI.getDeviceList().deviceInfoList.deviceInfo[0] is correct', () => {
        assert.strictEqual(typeof deviceList.deviceInfoList[0].id, 'number');
        assert.strictEqual(typeof deviceList.deviceInfoList[0].description, 'string');
        assert.strictEqual(typeof deviceList.deviceInfoList[0].serialNumber, 'string');
        assert.strictEqual(typeof deviceList.deviceInfoList[0].flags, 'number');
        assert.strictEqual(typeof deviceList.deviceInfoList[0].locId, 'number');
        assert.strictEqual(typeof deviceList.deviceInfoList[0].type, 'number');
        assert.notStrictEqual(deviceList.deviceInfoList[0].ftHandle, null);
    });
});

describe('Tests ftdi open', () => {
    /** @type {FTDI} */
    let ftdi;
    let deviceInfo = FTD2XX.FTDI.getDeviceList().deviceInfoList[0];
    afterEach(() => {
        assert.strictEqual(ftdi.close(), FTD2XX.FT_STATUS.FT_OK);
    });
    beforeEach(() => {
        ftdi = new FTD2XX.FTDI();
        //global.gc();
    });
    it('FTDI.openByIndex(index) should return FT_OK', () => {
        assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openByDescription(description) should return FT_OK', () => {
        assert.strictEqual(ftdi.openByDescription(deviceInfo.description), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openBySerialNumber(serialNumber) should return FT_OK', () => {
        assert.strictEqual(ftdi.openBySerialNumber(deviceInfo.serialNumber), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openByLocation(LocId) should return FT_OK', () => {
        assert.strictEqual(ftdi.openByLocation(deviceInfo.locId), FTD2XX.FT_STATUS.FT_OK);
    });
});