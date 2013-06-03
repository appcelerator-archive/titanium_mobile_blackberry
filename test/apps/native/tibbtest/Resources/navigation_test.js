
function GenericWindow(_windowNumber, _navGroup) {
	var win = Ti.UI.createWindow({
		title: 'Window #' + _windowNumber,
		backgroundColor: "#"+((1<<24)*Math.random()|0).toString(16)
	});
	
	var push = Ti.UI.createButton({
		top: 30,
		title: 'push new window'
	});
	
	var pop = Ti.UI.createButton({
		top: 60,
		title: 'pop this window'
	});
	
	var remove = Ti.UI.createButton({
		top: 90,
		title: 'remove this window'
	});

	var backButton = Ti.UI.createButton({
		top: 120,
		title: 'remove back button'
	});

	var peek = Ti.UI.createButton({
		top: 150,
		title: 'set peek enabled: ' + (_navGroup.getPeekEnabled() ? 'true' : 'false')
	});

	push.addEventListener('click', function(){
		var nextWindow = GenericWindow(_windowNumber + 1, _navGroup);
		_navGroup.push(nextWindow);
	});
	pop.addEventListener('click', function(){
		_navGroup.pop();
	});
	remove.addEventListener('click', function(){
		_navGroup.remove(win);
	});
	var backButtonShowing = false;
	backButton.addEventListener('click', function(){
		_navGroup.setBackButtonsVisible(backButtonShowing);
		backButtonShowing = !backButtonShowing;
	});

	peek.addEventListener('click', function(){
		var isPeekEnaled = !_navGroup.getPeekEnabled();
		_navGroup.setPeekEnabled(isPeekEnaled);
		this.title = 'set peek enabled: ' + (isPeekEnaled ? 'true' : 'false')
	});

	win.add(push);
	if(_windowNumber !== 1) {
		win.add(pop);
		win.add(remove);
		win.add(backButton);
		win.add(peek);
	}
	return win;
}

function NavigationGroup() {
	var nav = Ti.UI.createNavigationGroup();
	var win = GenericWindow(1, nav);
	nav.setRootWindow(win);
	return nav;
}

NavigationGroup().open();