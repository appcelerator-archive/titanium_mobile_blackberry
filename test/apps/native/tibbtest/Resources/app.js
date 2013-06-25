var win1 = Titanium.UI.createWindow({  
   backgroundColor:'#fff'
});
  
var view1 = Titanium.UI.createView({
    backgroundColor:'red',
   width:Ti.UI.SIZE,
   height:Ti.UI.SIZE
});
  
var label1 = Titanium.UI.createLabel({
    backgroundColor:'blue',
   color:'#999',
   text:'Label Test',
   font:{fontSize:20,fontFamily:'Helvetica Neue',fontStyle:'italic'},
   width:Ti.UI.SIZE,
   height:Ti.UI.SIZE
});
  
view1.add(label1);
win1.add(view1);
win1.open();