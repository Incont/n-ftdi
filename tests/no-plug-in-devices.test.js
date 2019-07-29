'use strict';
const assert = require('assert');
let FTD2XX = require('./../index');

describe('Tests getNumberOfDevices', () => {
    let numberOfDevices;
    before(() => {
        numberOfDevices = FTD2XX.FTDI.getNumberOfDevices();
    });
    it('FTDI.getNumberOfDevices() should retern object', () => {
        assert.strictEqual(typeof numberOfDevices, 'object');
    });
    it('FTDI.getNumberOfDevices().ftStatus should equal FTD2XX.FT_STATUS.FT_OK', () => {
        assert.strictEqual(numberOfDevices.ftStatus, FTD2XX.FT_STATUS.FT_OK);
    });
    it('FTDI.getNumberOfDevices().devCount should equal 0', () => {
        assert.strictEqual(numberOfDevices.devCount, 0);
    });
});