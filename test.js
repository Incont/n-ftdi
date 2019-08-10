'use strict';

(function() {
    let FTD2XX = require('./index');
    let ftdi = new FTD2XX.FTDI();
    let { ftStatus, devCount } = FTD2XX.FTDI.getNumberOfDevices();
    console.log(ftStatus, devCount);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftStatus]);
    console.log(FTD2XX.FTDI.getDeviceList());
    console.log("!!!");
    console.log(FTD2XX.FTDI.getDeviceList().deviceInfoList[0]);
    let t = ftdi.openByIndex(0);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftdi.openByLocation(5136)]);
    console.log(FTD2XX.FTDI.getDeviceList().deviceInfoList[0]);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftdi.close()]);
    console.log(FTD2XX.FTDI.getDeviceList().deviceInfoList[0]);
})();


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

function resolveAfter2Seconds(x) {
    return new Promise(resolve => {
      setTimeout(() => {
        resolve(x);
      }, 2000);
    });
  }
  
  async function add1(x) {
    const a = await resolveAfter2Seconds(20);
    const b = await resolveAfter2Seconds(30);
    return x + a + b;
  }
  
  add1(10).then(v => {
    console.log(v);  // prints 60 after 4 seconds.
  });
  
  async function add2(x) {
    const a = resolveAfter2Seconds(20);
    const b = resolveAfter2Seconds(30);
    return x + await a + await b;
  }
  
  add2(10).then(v => {
    console.log(v);  // prints 60 after 2 seconds.
  });