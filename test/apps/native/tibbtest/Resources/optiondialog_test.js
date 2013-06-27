var win = Ti.UI.createWindow({
  layout:'vertical'
});

var button = Ti.UI.createButton({
  title:'Option Dialog',
  top: 50,
  width:Ti.UI.SIZE,
  height:Ti.UI.SIZE

});

button.addEventListener('click',function(e){

  var dialog = Ti.UI.createOptionDialog({
    cancel: 2,
    title: 'Delete File?',
    options: ['Confirm', 'Help', 'Cancel'],
    destructive: 0
  });

  
  
  dialog.addEventListener('click', function(e){
	  alert(JSON.stringify(e));
  });
  dialog.show();
});



win.add(button);
win.open();
