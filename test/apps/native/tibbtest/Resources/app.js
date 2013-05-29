var win = Ti.UI.createWindow();

var views = [];
for(var i = 0; i < 11; i++) {
	var view = Ti.UI.createView({
		backgroundColor: '#'+((1<<24)*(Math.random()+1)|0).toString(16).substr(1)
	});
	var img = Ti.UI.createView({
		backgroundImage: 'images/hang_gliding/photo_' + (i + 1) + '.jpg'
	});
	view.add(img);
	views.push(view);
}
//
var otherView = Ti.UI.createView({
	backgroundColor: 'red'
});;

views.push(otherView);

var scrollableView = Ti.UI.createScrollableView({
	currentPage: 4,
	views: views,
	top: 0,
	width: 200,
	height: 112
});

var scrollToAnimated = Ti.UI.createButton({
	title: 'scroll animated',
	bottom: 40,
	right: 0
});

var scrollToNotAnimated = Ti.UI.createButton({
	title: 'scroll',
	bottom: 40,
	left: 0
});

var prev = Ti.UI.createButton({
	bottom: 0,
	left:0,
	title: 'prev'
});
var next = Ti.UI.createButton({
	bottom: 0,
	right:0,
	title: 'next'
});
var x = 0;

prev.addEventListener('click', function(){
	scrollableView.movePrevious();
});
next.addEventListener('click', function(){
	scrollableView.moveNext();
});

scrollToAnimated.addEventListener('click', function(){
	scrollableView.scrollToView(otherView, true);
});

scrollToNotAnimated.addEventListener('click', function(){
	scrollableView.scrollToView(2, false);
});
win.add(prev);
win.add(next);
win.add(scrollToAnimated);
win.add(scrollToNotAnimated);
win.add(scrollableView);

win.open();

