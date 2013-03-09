var win = Ti.UI.createWindow({
  backgroundColor: 'green'
});


var textArea = Ti.UI.createTextArea({
  color: '#888',
  font: {fontSize:10, fontWeight:'bold'},
  keyboardType: Ti.UI.KEYBOARD_NUMBER_PAD,
  returnKeyType: Ti.UI.RETURNKEY_GO,
  textAlign: 'left',
  value: 'I am a textarea',
  top: 60,
  width: 200, height : 70
});

win.add(textArea);
win.open();