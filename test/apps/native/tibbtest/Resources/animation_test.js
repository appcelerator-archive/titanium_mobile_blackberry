var win = Ti.UI.createWindow({
	title : 'Window',
	backgroundColor : '#28292c',
	barColor : '#28292c'
});

var view = Ti.UI.createView({
	top: 10,
	left: 10,
	width: 100,
	height: 100,
	backgroundColor: 'red'
});

var btn1 = Ti.UI.createButton({
	title: 'left 10, top: 10, opacity: 0.3',
	bottom: 60
});

var btn2 = Ti.UI.createButton({
	title: 'left: 200, top: 100, duration: 2000, opacity: 1',
	bottom: 0,
});

win.add(btn1);
win.add(btn2);
win.add(view);

btn1.addEventListener('click', function(){
	var animation = Ti.UI.createAnimation({
		left: 10,
		top: 10,
		opacity: 0.3,
		duration: 1000
	});
	view.animate(animation);
});

btn2.addEventListener('click', function(){
	view.animate({
		left: 200,
		top: 100,
		duration: 2000,
		opacity: 1
	}, function(e){
		alert('end');
		Ti.API.info(this);
		Ti.API.info(JSON.stringify(this));
	});
});

win.open();