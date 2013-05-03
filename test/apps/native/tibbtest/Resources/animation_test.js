// Global variable for device width
var viewWidth = 200;
// Main Window
var win = Ti.UI.createWindow({
	title : 'Main Window',
	backgroundColor : '#28292c',
	barColor : '#28292c'
});
win.open();
Ti.API.info(viewWidth);
// View for Menu items
var menuView = Ti.UI.createView({
	top : 0,
	left : viewWidth,
	width : 150,
	backgroundColor : 'red',

});
var menuTitles = [{
	title : 'Menu 1'
}, {
	title : 'Menu 2'
}, {
	title : 'Menu 3'
}, {
	title : 'Menu 4'
}, {
	title : 'Menu 5'
}, {
	title : 'Menu 6'
}];
// Tableview
var tableView = Ti.UI.createTableView({
	data : menuTitles
});
menuView.add(tableView);

//Another view
var View = Ti.UI.createView({
	top : 0,
	right : 0,
	backgroundColor : 'white',

});
win.add(View);
var menuButton = Ti.UI.createButton({
	title : 'Menu',
	toggle : false // Custom property for menu toggle
});
View.add(menuButton);
win.add(menuView);
menuButton.addEventListener('click', function(e) {
	// If the menu is opened
	if (e.source.toggle == true) {
		Ti.API.info('----> ' + viewWidth);
		menuView.animate({
			left : viewWidth,
			duration : 200,

		});
		e.source.toggle = false;

	}
	// If the menu isn't opened
	else {
		Ti.API.info('<---- ' + (viewWidth - 150));
		menuView.animate({
			left : 100,
			duration : 200,

		});
		e.source.toggle = true;

	}
}); 