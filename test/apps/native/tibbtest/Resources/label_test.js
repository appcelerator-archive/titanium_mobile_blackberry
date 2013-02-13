var win1 = Titanium.UI.createWindow({  
   backgroundColor:'#000'
});

var label1 = Titanium.UI.createLabel({
   color:'#999',
   text:'Label Test',
   font:{fontSize:20,fontFamily:'Helvetica Neue',fontStyle:'italic'},
   width:'auto'
});

win1.add(label1);
win1.open();