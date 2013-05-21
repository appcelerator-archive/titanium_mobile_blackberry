var win = Titanium.UI.createWindow({  
   backgroundColor:'#000'
});

var toolbar = Ti.UI.createView({
	bottom: 0,
	height: 35,
	backgroundColor: '#ccc'
});

var back = Ti.UI.createButton({
	left: 0,
	width: 50,
	title: 'back'
});

var reload = Ti.UI.createButton({
	width: 50,
	title: 'reload'
});

var fwd = Ti.UI.createButton({
	right: 0,
	width: 50,
	title:'fwd'
})

toolbar.add(back);
toolbar.add(reload);
toolbar.add(fwd);

var webview = Ti.UI.createWebView({
	url: 'http://javascript.crockford.com',
	bottom: 35
});

back.addEventListener('click', function(){
	if(webview.canGoBack()) {
		webview.goBack();
	}
});

reload.addEventListener('click', function(){
	webview.reload();
});

fwd.addEventListener('click', function(){
	if(webview.canGoForward()) {
		webview.goForward();
	}
});

win.add(webview);
win.add(toolbar);
win.open();