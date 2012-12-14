function AddWindow(cb) {
  var self = Ti.UI.createWindow({
    backgroundColor: 'black',
    top: 200, left: 50,
    width: 550, height: 250
  });

  var titleField = Ti.UI.createTextField({
    top: 20, left: 25,
    width: 500
  });
  self.add(titleField);

  var saveButton = Ti.UI.createButton({
    title: 'Save',
    width: 250,
    top: 125, left: 25
  });
  self.add(saveButton);

  var cancelButton = Ti.UI.createButton({
    title: 'Cancel',
    width: 250,
    top: 125, left: 270
  });
  self.add(cancelButton);

  saveButton.addEventListener('click', function() {
    cb(titleField.value);
    self.close();
  });

  cancelButton.addEventListener('click', function() {
    self.close();
  });

  return self;
}

module.exports = AddWindow;
