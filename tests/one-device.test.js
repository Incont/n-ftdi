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
        assert.strictEqual(deviceList.deviceInfoList[0].ftHandle, null);
    });
});
var t = [];
describe('Tests ftdi open', () => {
    let ftdi// = new FTD2XX.FTDI();
    t.push(ftdi);
    afterEach(() => {
      //  ftdi.close();
    });
    beforeEach(() =>{
      //  t.push(ftdi);
        ftdi = new FTD2XX.FTDI()
        global.gc();
    });
    let s = "";
    it('FTDI.openByIndex(0) should return object', () => {
        assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openByIndex(0) should return object 1', () => {
        assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openByIndex(0) should return object 2', () => {
        assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openByIndex(0) should return object 3', () => {
        assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.openByIndex(0) should return object 4', () => {
        assert.strictEqual(ftdi.openByIndex(0), FTD2XX.FT_STATUS.FT_OK);
    });
});