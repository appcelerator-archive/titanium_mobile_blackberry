
// V8 Garbage collector should kick in and natve button destructor called

var window = Titanium.UI.createWindow({});

var myfunc = function (){
	var button = Titanium.UI.createButton({
		title: 'www.youtube.com',
		//backgroundImage:'KS_nav_ui.png',
		top: 10,
		width: 200,
		height: 50,
		left:60
	});
};

myfunc();
Ti.API.info('index = ' + button.title);

window.open();