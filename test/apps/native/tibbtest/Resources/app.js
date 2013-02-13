var win1 = Titanium.UI.createWindow({  
   backgroundColor:'#000'
});
  
var usernameField = Ti.UI.createTextField({
       width:'auto',
       height:'auto',
       hintText: 'Username',
       top: 10, 
       left: 10
});
win1.add(usernameField);
win1.open();