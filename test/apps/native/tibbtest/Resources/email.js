var win = Titanium.UI.createWindow({});

var btn = Ti.UI.createButton({
	title: 'open'
});

win.add(btn);

btn.addEventListener('click', function(){
	var email = Ti.UI.createEmailDialog({
		toRecipients: ['email@domain.com', 'email@domain.com'],
		ccRecipients: ['email@domain.com'],
		bccRecipients: ['email@domain.com'],
		messageBody: 'This is the message body',
		subject: 'this is a title',
		html: true // this doesn't work
	});
	email.open();
});

win.open();

