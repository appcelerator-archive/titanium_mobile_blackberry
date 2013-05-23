var win1 = Titanium.UI.createWindow({  
   backgroundColor:'#000'
});

var view1 = Titanium.UI.createView({
	backgroundColor:'red',
	width: "100px",
	height: "100px"
});

var view2 = Titanium.UI.createView({
	backgroundColor:'blue',
    top:"25px",
    bottom:"25px",
    left:"25px",
    right:"25px"
});

view1.add(view2);
win1.add(view1);
win1.open();