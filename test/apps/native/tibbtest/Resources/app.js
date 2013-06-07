var win = Ti.UI.createWindow();

var view = Ti.UI.createView({
	backgroundColor: 'blue',
	height: Ti.UI.SIZE
});

var label = Ti.UI.createLabel({
	text: 'hello world',
	backgroundColor: 'red',
	height: Ti.UI.SIZE
});

view.add(label);
win.add(view);
win.open()


/*
var win = Ti.UI.createWindow({});
 
var view = Ti.UI.createView({
    backgroundColor: 'green',
    width: 200,
    height: 200
});


var label = Ti.UI.createLabel({
    top: 50,
	backgroundColor: 'red',
    text: 'kkkkkkkk',
    width: Ti.UI.SIZE,
    height: Ti.UI.SIZE
});

view.add(label);
win.add(view);
//win.add(label);
win.open();
*/