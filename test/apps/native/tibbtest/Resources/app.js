var win1 = Titanium.UI.createWindow({  
    backgroundColor:'#fff'
});
  
var lbl = Ti.UI.createLabel({
text:'Please select an item',
//font:{fontSize:15},
height:'auto',
width:'auto',
color:'#000'
});


/*
var lbl = Ti.UI.createButton({
	title:'Button',
	});
*/

win1.add(lbl);

win1.open()
