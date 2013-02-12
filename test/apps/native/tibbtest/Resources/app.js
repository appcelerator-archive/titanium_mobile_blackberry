var win1 = Titanium.UI.createWindow({  
    backgroundColor:'#fff'
});
   
var lbl = Ti.UI.createLabel({
text:'Please select an item',
font:{fontSize:15},
height:'auto',
width:'auto',
color:'#000'
});

win1.add(lbl);

win1.open()
