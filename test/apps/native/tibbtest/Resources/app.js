var win = Titanium.UI.createWindow();
 

var scroll = Ti.UI.createScrollView({
   backgroundColor: '#ccc',
   width: Ti.UI.FILL,
   height: Ti.UI.FILL,
   layout: 'vertical',
      
});


function MyButton(title) {
   return Ti.UI.createButton({
       title: title,
       top: 10
   });
}
  
for(var i = 0; i < 500; i++) {
   scroll.add(MyButton('Button #' + (i + 1))); 
}
  
win.add(scroll);
win.open();