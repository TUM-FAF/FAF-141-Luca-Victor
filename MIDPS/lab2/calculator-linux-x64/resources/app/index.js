var app = require('app');
var BrowserWindow = require('browser-window');
var core = require('./core/calculator.js');
const ipcMain = require('electron').ipcMain;

app.on('ready', function() {
  var mainWindow = new BrowserWindow({
    width: 360,
    height: 310
  });
  mainWindow.loadURL('file://' + __dirname + '/frontend/index.html');
  // mainWindow.webContents.openDevTools();
  // calculation process
  ipcMain.on('asynchronous-message', function(event, expression) {
    event.sender.send('asynchronous-reply', core.calculate(expression));
  });
});



