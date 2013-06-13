var win = Ti.UI.createWindow();

var imageButton = Ti.UI.createImageButton({
	image: 'images/play_button.png',
	imagePressed: 'images/play_button_pressed.png',
	imageDisabled: 'images/appcelerator_small.png'
});

imageButton.addEventListener('click', function(){
	alert('ImageButton Clicked')
});

var btn = Ti.UI.createButton({
	bottom: 10,
	title: 'disable image button'
});

var enabled = true;
btn.addEventListener('click', function(){
	imageButton.enabled = enabled;
	enabled = !enabled;
});

win.add(btn);

win.add(imageButton);
win.open();