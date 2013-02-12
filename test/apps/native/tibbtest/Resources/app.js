var win = Ti.UI.createWindow({
});

var view = Ti.UI.createView({
	backgroundColor: 'green',
    width: Ti.UI.FILL,
    height:Ti.UI.FILL
});

win.add(view);

var label = Ti.UI.createLabel({
	backgroundColor: 'red',   
    text: 'My First App'
});

var btn = Ti.UI.createButton({
	backgroundColor: 'red',   
    title: 'My First App'
});

var view2 = Ti.UI.createView({
	backgroundColor: 'red',   
    width: 100,
    height: '100'
});

var toggle = Ti.UI.createSwitch({
    value:true
});

//view.add(view2);
//view.add(label);
//view.add(btn);
view.add(toggle);

win.open();