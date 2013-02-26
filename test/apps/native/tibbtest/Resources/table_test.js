var win1 = Titanium.UI.createWindow({  
   backgroundColor:'green'
});
  
  
  var self = Ti.UI.createView({
       backgroundColor:'red'
   });
   
var tableData = [
   {title:'Apples', color: '#000'},
   {title:'Grapes', color: '#000'},
   {title:'Oranges',color: '#000'},
   {title:'Bananas',color: '#000'},
   {title:'Pears',  color: '#000'},
   {title:'Kiwis',  color: '#000'}
];
   
var table = Ti.UI.createTableView({
   data:tableData
});
self.add(table);
win1.add(self);
win1.open();