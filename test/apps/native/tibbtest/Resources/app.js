

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
//Ti.API.info('index = ' + button.title);

var window = Titanium.UI.createWindow({});

/*
var button = Titanium.UI.createButton({
	title: 'www.youtube.com',
	//backgroundImage:'KS_nav_ui.png',
	top: 10,
	width: 200,
	height: 50,
	left:60
});

var button2 = Titanium.UI.createButton({
	title: 'www.youtube.com',
	//backgroundImage:'KS_nav_ui.png',
	top: 50,
	width: 200,
	height: 50,
	left:60
});

var button3 = Titanium.UI.createButton({
	title: 'www.youtube.com',
	//backgroundImage:'KS_nav_ui.png',
	top: 100,
	width: 200,
	height: 50,
	left:60
});
 
function showAlert() {
     Ti.API.info('index = ' + button2.title);
}

 
setTimeout(showAlert, 2000);
*/

window.open();

