//'use strict';
let FTD2XX = require('./index');

/*
(function() {
    let ftdi = new FTD2XX.FTDI();
    let { ftStatus, devCount } = FTD2XX.FTDI.getNumberOfDevicesSync();
    console.log(ftStatus, devCount);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftStatus]);
    console.log(FTD2XX.FTDI.getDeviceListSync());
    console.log("!!!");
  //  console.log(FTD2XX.FTDI.getDeviceList().deviceInfoList[0].ftHandle.free());
    let t = ftdi.openByIndexSync(0);
    let r = FTD2XX.FTDI.getDeviceListSync().deviceInfoList[0]F
  r.f
    console.log(r.type)
    console.log(r);
    console.log(Object.keys(FTD2XX.FT_STATUS)[ftdi.closeSync()]);
    console.log(FTD2XX.FTDI.getDeviceListSync().deviceInfoList[0]);
})();
*/

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
/*
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
console.log("++++");*/
//let f = new FTD2XX.FTDI()
//console.log('!!!!!!!!!!!!!!!!')
//console.log(f.openByIndexSync(0))
//console.log(f.getDeviceInfoSync())
//f.readFT232HEEPROM().then(r => console.log(r))

/*
const _ftdiAddon = require('bindings')('N-FTD2XX')
let t = new _ftdiAddon.FT_PROGRAM_DATA()
t.signature1 = 10
t.manufacturerID = '12345678901234567'
console.log(t.manufacturerID)
*/
/*
const _ftdiAddon = require('bindings')('N-FTD2XX')
_ftdiAddon.createDeviceInfoList().then(r =>console.log(r))
_ftdiAddon.getDeviceInfoDetail(0).then(r =>console.log(r))
_ftdiAddon.createDeviceInfoList().then(r =>console.log(r))
_ftdiAddon.getDeviceInfoDetail(0).then(r =>console.log(r))
_ftdiAddon.createDeviceInfoList().then(r =>console.log(r))
_ftdiAddon.getDeviceInfoDetail(0).then(r =>console.log(r))
*/

console.log(FTD2XX.FTDI.getDeviceListSync())
let d = new FTD2XX.FTDI();
d.openByIndexSync(0);
console.log(d.getDeviceInfoSync());
console.log(d.programDeviceDescriptionSync("cccc"));
console.log(d.cyclePortSync());
d.closeSync();
d = new FTD2XX.FTDI();
d.openByIndexSync(0);
console.log(d.getDeviceInfoSync());

//d.programDeviceDescription("TEST").then(v => console.log(v))
//FTD2XX.FTDI.getVIDPID().then(v => console.log(v))
//console.log(FTD2XX.FTDI.getVIDPIDSync())
/*
console.log(FTD2XX.FTDI.getVIDPIDSync());
FTD2XX.FTDI.getVIDPID().then(v => console.log(v));
*/
/*
TEMP_1WIRE
function delay(ms) {
  return new Promise((resolve, reject) => {
    setTimeout(resolve, ms);
  });
}
const _ftdiAddon = require('bindings')('N-FTD2XX')
var util = require('util');
let rxB = Buffer.alloc(256);
let str = String.fromCharCode.call(null, new Uint8Array(rxB));
console.log(str);
console.log();
let p = new util.TextEncoder("utf-8").encode("aaaaaaaa");
let h;
let ftdi = new FTD2XX.FTDI()
async function Test() {
  console.log(await FTD2XX.FTDI.getDeviceList())
  console.log(await ftdi.openByDescription('FT232R USB UART'))
  await ftdi.setBaudRate(38400)
  console.log( await ftdi.getDeviceInfo())
  console.log( await ftdi.write(Buffer.from("aaaaaaaa"), 1))

  let qqq = await ftdi.getQueueStatus()
  while(qqq.rxQueue == 0) {
    qqq =  await ftdi.getQueueStatus()
  }
  console.log(qqq);
  console.log(await ftdi.read(rxB, qqq.rxQueue))
  str = rxB.toString();
  console.log(str)
  console.log(str.length)
}
Test()
*/
