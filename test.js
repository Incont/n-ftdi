let FTDI = require('./index');
let ftdi = new FTDI.FTDI();
let { ftStatus, devCount } = ftdi.getNumberOfDevices();
console.log(ftStatus, devCount);
for (let ftStatusName in FTDI.FT_STATUS) {
    if(FTDI.FT_STATUS[ftStatusName] === ftStatus) {
        console.log(ftStatusName);
    }
}
console.log(Object.keys(FTDI.FT_STATUS)[ftStatus]);