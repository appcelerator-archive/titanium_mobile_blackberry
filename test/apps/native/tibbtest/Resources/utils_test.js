var win = Ti.UI.createWindow({
	layout: 'vertical'
});

function Button(_title, _callback) {
	var btn = Ti.UI.createButton({
		title: _title,
		top: 10
	});
	
	btn.addEventListener('click', _callback);
	return btn
}

win.add(Button('base64encode', base64encode));
win.add(Button('base64decode', base64decode));
win.add(Button('md5', md5));
win.add(Button('sha1', sha1));
win.add(Button('sha256', sha256));

win.open();

function base64encode() {
	var result = Ti.Utils.base64encode('Titanium Rocks!').text;
	Ti.API.info('base64encode');
	Ti.API.info(result);
}
function base64decode() {
	var result = Ti.Utils.base64decode('VGl0YW5pdW0gUm9ja3Mh').text;
	Ti.API.info('base64decode');
	Ti.API.info(result);
}
function md5() {
	var result = Ti.Utils.md5HexDigest('Titanium Rocks!');
	Ti.API.info('md5');
	Ti.API.info(result);
}
function sha1() {
	var result = Ti.Utils.sha1('Titanium Rocks!');
	Ti.API.info('sha1');
	Ti.API.info(result);
}
function sha256() {
	var result = Ti.Utils.sha256('Titanium Rocks!');
	Ti.API.info('sha256');
	Ti.API.info(result);
}