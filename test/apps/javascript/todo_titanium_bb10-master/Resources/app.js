// ACS credentials.
Ti.App.Properties.setString('acs-api-key', 'e7CM7iBA76JMzMCNI2XcM13SjcBmuy6h');
Ti.App.deployType = 'development';

// Require all dependencies here to avoid
// running modules more than once. BB currently
// doesn't cache modules, so every require() runs it again.
Cloud = require('lib/ti.cloud');
AddWindow = require('views/add_window');
LoginWindow = require('views/login_window');
Todo = require('models/todo');
TodoListWindow = require('views/todo_list_window');

LoginWindow(function() {
  TodoListWindow().open();
}).open();
