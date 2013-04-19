

/*
var win = Ti.UI.createWindow({});
//Horizontal Layout behavior. Green child centered vertically (No positioning pins)
var parent = Ti.UI.createView({backgroundColor:'red',layout:'horizontal',width:100, height:100});
var child1 =Ti.UI.createView({backgroundColor:'green',height:20,width:50});
var child2 =Ti.UI.createView({backgroundColor:'blue',height:40,width:50});
parent.add(child1);
parent.add(child2);
win.add(parent);
win.open();
*/


var win = Ti.UI.createWindow({});
     
    var view = Ti.UI.createView({
        height:300,
        width:320,
        layout:'horizontal'
         
    });
    win.add(view);
     
    var l1 = Ti.UI.createLabel({
        text:'I am the first label',
        left:5,
        width:'auto',
        height:20
    });
     
    view.add(l1);
     
    var l2 = Ti.UI.createLabel({
        text:'I am the second label',
        left:2,
        width:'auto',
        height:20
    });
     
    view.add(l2);
     
    var l3 = Ti.UI.createLabel({
        text:'I am the third label',
        left:2,
        width:'auto',
        height:20
    });
     
    view.add(l3);
 
win.open();
