var win = Titanium.UI.createWindow();
   
var view = Ti.UI.createView({
    backgroundColor: 'red',
    width: Ti.UI.SIZE,
    height: Ti.UI.SIZE,
    layout: 'vertical'
});
   
function MyLabel(title) {
    return Ti.UI.createLabel({
        text: title,
        top: 10
    });
}
   
for(var i = 0; i < 100; i++) {
    view.add(MyLabel('Label #' + (i + 1))); 
}
   
win.add(view);
win.open();