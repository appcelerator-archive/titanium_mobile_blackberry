var win = Titanium.UI.createWindow();
  
var scroll = Ti.UI.createScrollView({
    backgroundColor: '#ccc',
    width: Ti.UI.FILL,
    height: Ti.UI.FILL,
    layout: 'vertical',
    contentHeight: Ti.UI.SIZE,
    contentWidth: Ti.UI.FILL
});
  
function MyButton(title) {
    return Ti.UI.createLabel({
        //title: title,
    	text: 'kkkkkkk',
        top: 10
    });
}
  
for(var i = 0; i < 100; i++) {
    scroll.add(MyButton('Button #' + (i + 1))); 
}
  
win.add(scroll);
win.open();