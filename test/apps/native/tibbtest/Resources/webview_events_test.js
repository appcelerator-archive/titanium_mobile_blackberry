var win = Titanium.UI.createWindow();

var webView = Ti.UI.createWebView({
    top: 50,
    url: 'web.html'
});

var btn = Ti.UI.createButton({
    top: 0,
    title: 'fire event'
});

btn.addEventListener('click', function(){
    Ti.App.fireEvent('web_view_event', {prop: 'prop_1'});
});

Ti.App.addEventListener('change_title', function(e){
	btn.title = e.title;
});

win.add(btn);

win.add(webView);

win.open();


