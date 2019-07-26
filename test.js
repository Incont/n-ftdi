'use strict';
let FTD2XX = require('./index');
let ftdi = new FTD2XX.FTDI();
let { ftStatus, devCount } = FTD2XX.FTDI.getNumberOfDevices();
console.log(ftStatus, devCount);
for (let ftStatusName in FTD2XX.FTDI.FT_STATUS) {
    if(FTD2XX.FT_STATUS[ftStatusName] === ftStatus) {
        console.log(ftStatusName);
    }
}
console.log(Object.keys(FTD2XX.FT_STATUS)[ftStatus]);
console.log(FTD2XX.FTDI.getDeviceList());
console.log(typeof(FTD2XX.FTDI.getDeviceList().deviceInfoList[0]));
console.log(FTD2XX.FTDI.getDeviceList().deviceInfoList[0]);