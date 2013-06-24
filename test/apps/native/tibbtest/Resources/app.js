var win = Ti.UI.createWindow({});
      
var view = Ti.UI.createView({
    backgroundColor:'green',
       // height:200,
        width:200,
        layout:'horizontal'
          
});
 
win.add(view);
      
var v1 = Ti.UI.createButton({
        //backgroundColor:'blue',
        title:'button 1',
        //height:30,
        left:5,
        width:Ti.UI.SIZE,
        top:80
});
     
view.add(v1);
     
var v2 = Ti.UI.createButton({
        //backgroundColor:'red',
        title:'button 2',
        //height:30,
        left:5,
        width:Ti.UI.SIZE,
        top:80
});
     
view.add(v2);
     
var v3 = Ti.UI.createButton({
        //backgroundColor:'black',
        title:'button 3',
        //height:30,
        left:5,
        width:Ti.UI.SIZE,
        top:80
});
     
view.add(v3);
     
  
win.open();
