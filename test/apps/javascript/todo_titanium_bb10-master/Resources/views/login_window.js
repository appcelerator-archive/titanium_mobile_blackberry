Cloud.debug = true;

function LoginWindow(cb) {
	var self = Ti.UI.createWindow();

	var usernameField = Ti.UI.createTextField({
		width: '75%',
		hintText: 'Username',
		top: 10, left: 100
	});
	self.add(usernameField);

	var passwordField = Ti.UI.createTextField({
		width: '75%',
		hintText: 'Password',
		passwordMask: true,
		top: 100, left: 100
	});
	self.add(passwordField);

	var loginButton = Ti.UI.createButton({
		title: 'Login',
		top: 200, left: 200
	});
	self.add(loginButton);

	loginButton.addEventListener('click', function() {
		Ti.API.info('username: ' + usernameField.value + ' password: ' + passwordField.value);
		Cloud.Users.login({
			login: usernameField.value,
			password: passwordField.value
		}, function(e) {
			if (e.success) {
				cb();
				self.close();
			} else {
				alert('Login failed.');
			}
		});
	});

	return self;
}

module.exports = LoginWindow;
