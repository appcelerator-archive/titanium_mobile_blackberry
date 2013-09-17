alert('Please see the console for logs');
 
//Reading a file from the Resources dir
 
Ti.API.info('------------------------');
Ti.API.info('Testing resources directory reading app.js');
var app_js = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'app.js');
var blob = app_js.read();
Ti.API.info('---------');
Ti.API.info(blob.text);
 
//Creating, writing, and reading a file from the data dir
 
Ti.API.info('------------------------');
Ti.API.info('Testing data directory reading writing and reading');
var file = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'hello_world.txt');
if(!file.exists()) {
    Ti.API.info('file does not exist');
    file.write('this is a test');
    Ti.API.info('file exists? ' + file.exists());
}
Ti.API.info('---------');
var blob = file.read();
Ti.API.info(blob.text);
 
//Getting the directory listing from the data dir
 
Ti.API.info('------------------------');
Ti.API.info('Testing data directory get listing');
var directory = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory);
var files = directory.getDirectoryListing();
for(var i = 0; i < files.length; i++) {
    Ti.API.info('=====================');
    var file = files[i];
    Ti.API.info('filename: ' + file);
    var _file = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, file);
    Ti.API.info('isDirectory: ' + _file.isDirectory());
    Ti.API.info('isFile: ' + _file.isFile());
}