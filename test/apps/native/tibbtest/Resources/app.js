/*
Ti.API.info('running');
 
var win = Ti.UI.createWindow({backgroundColor: 'red'});
win.open();
 
function showAlert() {
    Ti.API.info('opening alert...');
    var alert = Ti.UI.createAlertDialog({
        title: 'Click a button...'
    });
    alert.addEventListener('click', function(e) {
        Ti.API.info('index = ' + e.index);
    });
    alert.show();
}

 
setTimeout(showAlert, 2000);



var window = Titanium.UI.createWindow({
	//backgroundImage:'default.png'
	backgroundColor:'#7a24db'
});

var button = Titanium.UI.createButton({
	title: 'www.youtube.com',
	//backgroundImage:'KS_nav_ui.png',
	top: 10,
	width: 200,
	height: 50,
	left:60
});

window.add(button);
window.open();
*/

var win2 = Ti.UI.createWindow({
	backgroundColor: 'yellow',
	//fullscreen: true
});

var button = Titanium.UI.createButton({
	title: 'www.youtube.com is calling you',
	//backgroundImage:'blackberry/KS_nav_ui.png',
	top: 10,
	//width:Ti.UI.SIZE,
	//height:Ti.UI.SIZE,
	//left:55
});

win2.add(button);

button.addEventListener('click',function(e){
	//alert('Yoo Hoo');
	var dialog = Ti.UI.createAlertDialog({
		message: 'The file has been deleted',
		ok: 'Okay',
		title: 'File Deleted'
	 });
	
	 dialog.addEventListener('click', function(e) {
	        Ti.API.info('index = ' + e.index);
	    });
		
	dialog.show();
});


win2.open();