/*
 * @Author: lixiaowei
 * @Date: 2021-05-27 11:49:58
 * @LastEditors: lixiaowei
 * @LastEditTime: 2021-05-28 14:41:01
 * @Description: file content
 * @FilePath: /node-qt-napi/run.js
 */

const qt = require("./lib/qt");

console.log(qt);
console.time("screenshort!!!!");
const app = new qt.QApplication();
const qgui = new qt.QGuiApplication();
const displays = qgui.screenshort();
console.timeEnd("screenshort!!!!");
console.dir(displays);