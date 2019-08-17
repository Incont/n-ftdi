'use strict';
let FTD2XX = require('./index');
(function() {
    let ftdi = new FTD2XX.FTDI();
    let { ftStatus, devCount } = FTD2XX.FTDI.getNumberOfDevicesSync();
    console.log(ftStatus, devCount);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftStatus]);
    console.log(FTD2XX.FTDI.getDeviceListSync());
    console.log("!!!");
  //  console.log(FTD2XX.FTDI.getDeviceList().deviceInfoList[0].ftHandle.free());
    let t = ftdi.openByIndexSync(0);
    console.log(FTD2XX.FTDI.getDeviceListSync().deviceInfoList[0]);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftdi.closeSync()]);
    console.log(FTD2XX.FTDI.getDeviceListSync().deviceInfoList[0]);
})();
/*

function myFunc(arg) {
    console.log(`arg was => ${arg}`);
  }
//setTimeout(myFunc, 1500, 'funky');
const _ftdi = require('bindings')('N-FTD2XX');
let t0 = Date.now();
_ftdi.createDeviceInfoListAsync(function(err, result) {
    let t10 = Date.now();
    console.log("Asinc " + (t10 - t0));
    console.log("result " + result.devCount);
});
let t1 = Date.now();
let ts0 = t1 - t0;
_ftdi.getDeviceInfoDetail(0);
let t2 = Date.now();
let ts1 = t2 - t1;
_ftdi.getDeviceInfoDetailAsync(0, function(error, result){
    let t4 = Date.now();
    let ts3 = t4 - t2;
    console.log("Ts3 " + ts3);
});
let t3 = Date.now();
let ts2 = t3 - t2;
console.log("Ts0 " + ts0);
console.log("Ts1 " + ts1);
console.log("Ts2 " + ts2);
*/
FTD2XX.FTDI.getDeviceList().then(result => {
    console.log(result);
    (() => console.log(this))();
});

function F() {
  //  this.f = () => console.log(this);
}
F.prototype.f = () => console.log(this);
(new F).f();

function resolveAfter2Seconds(x) {
    return new Promise(resolve => {
        setTimeout(() => {
            resolve(x);
        }, 2000);
    });
}

async function add1(x) {
    return 0;
}
console.log("!!!!");
add1(1).then(r => console.log("result" + r));
console.log("++++");
