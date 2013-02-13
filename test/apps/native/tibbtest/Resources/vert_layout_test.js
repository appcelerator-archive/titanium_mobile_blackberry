var win = Ti.UI.createWindow({layout:'vertical'});
 
var label = Ti.UI.createLabel({
    text: 'Type some stuff...',
    width: '75%', height: 50
});
win.add(label);
 
var textField = Ti.UI.createTextField({
    width: '75%', height: 75
});
win.add(textField);
 
var button = Ti.UI.createButton({
    title: 'Click, me!',
    width: '75%', height: 100
});
win.add(button);
 
var view = Ti.UI.createView({
    backgroundColor: 'red'
});
win.add(view);
 
win.open();