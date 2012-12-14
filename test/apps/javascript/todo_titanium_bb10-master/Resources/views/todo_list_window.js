function TodoListWindow(todos) {
  var self = Ti.UI.createWindow({
    backgroundImage: 'images/background.png'
  });

  self.addEventListener('open', function() {
    self.addAction('Add', 'images/add.png', function() {
      AddWindow(function(title) {
        var todo = new Todo(title);
        todo.save(function(err) {
          if (err) {
            alert('Failed to save todo item to cloud.');
            Ti.API.error('Error saving todo: ' + err);
            return;
          }
          reload();
        });
      }).open();
    });
  });

  var tableview = Ti.UI.createTableView();
  self.add(tableview);

  function reload() {
    Todo.fetch(function(err, todos) {
      if (err) {
        alert('Error fetching todos: ' + err);
        return;
      }

      tableview.setData(getTableData(todos, false));
    });
  }
  reload();

  tableview.addEventListener('click', function(e) {
    // TODO: show action items to complete, edit, or delete.
    Ti.API.debug('clicked item: ' + e.rowData.id);
  });

  return self;
}

var getTableData = function(todoItems, done) {
	var data = [];
	var row = null;
	
	for (var i = 0; i < todoItems.length; i++) {
		var item = todoItems[i];
		data.push({
			id: item.id,
			title: item.title,
			color: '#000',
			font: {
				fontWeight: 'bold',
				fontSize: 14
			}
		});
	}
	return data;
};

var createConfirmDialog = function(todoItem) {
	var buttons, doneIndex, clickHandler;
	
	if (todoItem.isCompleted()) {
		buttons = ['Delete', 'Cancel'];	
		clickHandler = function(e) {
			if (e.index === 0) {
				todoItem.remove();
				Ti.App.fireEvent('app:updateTables');
			}
		};
	} else {
		buttons = ['Done', 'Delete', 'Cancel'];
		clickHandler = function(e) {
			Ti.API.info("button selected: index = " + e.index);
			if (e.index === 0) {
				todoItem.markCompleted();
				Ti.App.fireEvent('app:updateTables');
			} else if (e.index === 1) {
				todoItem.remove();
				Ti.App.fireEvent('app:updateTables');
			}
		};
	}
	
	var confirm = Ti.UI.createAlertDialog({
		title: 'Change Task Status',
		message: todoItem.title,
		buttonNames: buttons
	});
	confirm.addEventListener('click', clickHandler);
	
	return confirm;
};

module.exports = TodoListWindow;
