
var win1 = Titanium.UI.createWindow({  
   backgroundColor:'#000'
});

var label1 = Titanium.UI.createLabel({
   color:'#999',
   backgroundColor:'red',
   text:'/n/n    Label Test',
   font:{fontSize:20,fontFamily:'Helvetica Neue',fontStyle:'italic'},
   width: 'Ti.UI.SIZE',
   height: 'Ti.UI.SIZE'
});

win1.add(label1);
win1.open();


/*

var window = Titanium.UI.createWindow({});

Ti.Analytics.featureEvent('jjj.ppp.lll', '{hhh:{pppp:jjj}}');

window.open();

*/