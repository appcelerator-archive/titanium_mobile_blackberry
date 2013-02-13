// this sets the background color of the master UIView (when there are no windows/tab groups on it)
//Titanium.UI.setBackgroundColor('#000');

var win = Ti.UI.createWindow({});

var view = Ti.UI.createView({
	top: 0,
	left:0,
	height: 120
});

var btn1 = Ti.UI.createButton({
	left: 20,
	width: 300,
	height: 100,
	title: 'google.com'
});

var btn2 = Ti.UI.createButton({
	left: 400,
	width: 300,
	height: 100,
	title: 'javascript.crockford.com'
});

view.add(btn1);
view.add(btn2)

win.add(view);

var webview = Ti.UI.createWebView({
	top: 120,
	left:0,
	right:0,
	bottom:0,
	url:'http://appcelerator.com'
});

webview.addEventListener('load', function(e){
	Ti.API.info('-------------------load');
	Ti.API.info(e);
});
webview.addEventListener('beforeload', function(e){
	Ti.API.info('-------------------beforeload');
	Ti.API.info(e);
});
webview.addEventListener('error', function(e){
	Ti.API.info('-------------------error');
	Ti.API.info(e);
});
win.add(webview)
win.open();

btn1.addEventListener('click', function(){
	webview.url = 'http://google.com';
});
btn2.addEventListener('click', function(){
	webview.setUrl('http://javascript.crockford.com');
});