
var win = Ti.UI.createWindow();

var view = Ti.UI.createView({
    backgroundColor: 'green',
    width: Ti.UI.SIZE,
    height: Ti.UI.SIZE
});


var lbl = Ti.UI.createLabel({
    text: 'Hello World',
    backgroundColor: 'red',
    left: 10,
    width: '50%',
    height: 200
});

view.add(lbl);
win.add(view);
win.open();

/*
var win = Ti.UI.createWindow();
var view = Ti.UI.createLabel({
    text: 'Hello World',
    backgroundColor: 'red',
   // height:100,
    left: '50%',
    right: '10',
    //height: 100
    top:30,
    bottom: 30
    //top: 10,
    //bottom: 10
   // width:100,
   // height:100,
    //width: Ti.UI.SIZE,
    //height: Ti.UI.SIZE
   // width: Ti.UI.FILL,
    //height: Ti.UI.FILL
});
win.add(view);
win.open();
*/