
var window = Titanium.UI.createWindow({
 Ê Ê//backgroundImage:'default.png'
 Ê ÊbackgroundColor:'#7a24db'
});

var button = Titanium.UI.createButton({
 Ê title: 'www.youtube.com',
 Ê //backgroundImage:'KS_nav_ui.png',
 Ê top: 10,
 Ê width: 200,
 Ê height: 50,
 Ê left:60
});

window.add(button);
window.open();
[2/22/13 12:04:07 PM] Lokesh Choudhary: var win2 = Ti.UI.createWindow({
 ÊbackgroundColor: 'yellow',
 Ê//fullscreen: true
 Ê
});

var button = Titanium.UI.createButton({
 Ê title: 'www.youtube.com is calling you',
 Ê //backgroundImage:'blackberry/KS_nav_ui.png',
 Ê top: 10,
 Ê //width:Ti.UI.SIZE,
 Ê //height:Ti.UI.SIZE,
 Ê //left:55
});

win2.add(button);

button.addEventListener('click',function(e){
 Ê Ê//alert('Yoo Hoo');
 Ê Êvar dialog = Ti.UI.createAlertDialog({
 Ê Êmessage: 'The file has been deleted',
 Ê Êok: 'Okay',
 Ê Êtitle: 'File Deleted'
 });
 dialog.show();
});


win2.open();