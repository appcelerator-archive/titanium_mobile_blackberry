var win1 = Titanium.UI.createWindow({  
    backgroundColor:'green'
});
  
var lbl = Ti.UI.createLabel({
	backgroundColor: 'red',
	text:'This is a label test',
	font:{fontSize:15},
	height:'auto',
	width:'auto',
	color:'#000'
});


win1.add(lbl);

win1.open()
