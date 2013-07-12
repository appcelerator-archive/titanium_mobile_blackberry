var win = Ti.UI.createWindow({layout: 'vertical'});
 
var button = Ti.UI.createButton({title: 'take picture'});
button.addEventListener('click', function() {
    Ti.Media.showCamera({
        'cancel': function() {
            Ti.API.info('cancel');
        },
        'error': function() {
            Ti.API.info('error');
        },
        'success': function(e) {
            Ti.API.info('success: size=' + e.media.length);
      imageView.image = e.media;
        }
    });
});
win.add(button);
 
var imageView = Ti.UI.createImageView();
win.add(imageView);
 
setTimeout(function() {
    Ti.Media.hideCamera();
}, 3000);
 
win.open();