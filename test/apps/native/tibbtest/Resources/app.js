var win = Ti.UI.createWindow({
	backgroundColor: 'green'});
	
	win.orientationModes = [
		Titanium.UI.PORTRAIT,
		Titanium.UI.UPSIDE_PORTRAIT,
		Titanium.UI.LANDSCAPE_LEFT,
		Titanium.UI.LANDSCAPE_RIGHT,
		Titanium.UI.FACE_UP,
		Titanium.UI.FACE_DOWN
	]; 
	
var lbl = Ti.UI.createLabel({
	text:'Orientation modes',
	color:'white',
	font:{fontSize:15}
});
	
win.add(lbl);
win.open();
