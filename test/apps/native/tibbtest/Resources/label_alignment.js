var win = Ti.UI.createWindow({
    backgroundColor:'#f00'
});
  
win.open();
 
 
var lbll = Ti.UI.createLabel({
    text:'left',
    top:0,
    width:'100%',
    backgroundColor:'#fff',
    textAlign:'left'
});// 
win.add(lbll);
 
  
var lblr = Ti.UI.createLabel({
    text:'right',
    top:50,
    width:'100%',
    backgroundColor:'#fff',
    textAlign:'right'
});// 
win.add(lblr);
  
  
  
var lblc = Ti.UI.createLabel({
    text:'center',
    top:100,
    width:'100%',
    backgroundColor:'#fff',
    textAlign:Ti.UI.TEXT_ALIGNMENT_CENTER
});// 
win.add(lblc);
 
var tf = Ti.UI.createTextField({
    top: 150,
    value: 'hello world!',
    textAlign:'center'
});
win.add(tf);
