Ti.UI.backgroundColor = 'white';

var win1 = Ti.UI.createWindow({
  backgroundColor: 'blue'
});

var win2 = Ti.UI.createWindow({
  backgroundColor: 'yellow',
  fullscreen: true
});

/*
var style;
if (Ti.Platform.name === 'iPhone OS'){
  style = Ti.UI.iPhone.ActivityIndicatorStyle.DARK;
}
else {
  style = Ti.UI.ActivityIndicatorStyle.DARK;
}
*/

var activityIndicator = Ti.UI.createActivityIndicator({
  color: 'green',
  font: {fontFamily:'Helvetica Neue', fontSize:26, fontWeight:'bold'},
  message: 'Loading...',
 // style:style,
 // top:10,
 // left:10,
 // height:200, //Ti.UI.SIZE,
  //width:200
});

// The activity indicator must be added to a window or view for it to appear
win2.add(activityIndicator);

// eventListeners must always be loaded before the event is likely to fire
// hence, the open() method must be positioned before the window is opened


win2.addEventListener('open', function (e) {
  activityIndicator.show();
  // do some work that takes 6 seconds
  // ie. replace the following setTimeout block with your code
  setTimeout(function(){
    e.source.close();
    activityIndicator.hide();
  }, 6000);
});


win1.open();
win2.open();