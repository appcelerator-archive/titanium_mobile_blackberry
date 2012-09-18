// this sets the background color of the master UIView (when there are no windows/tab groups on it)
//Titanium.UI.setBackgroundColor('#000');

//
// create root window
//
var win1 = Titanium.UI.createWindow({  
    backgroundColor:'#F00'
});

var label1 = Ti.UI.createLabel({
	textAlign : 'center',
	font: {fontSize:12},
	color:'green',
	top: 200
});

var label2 = Ti.UI.createLabel({
	textAlign : 'center',
	font: {fontSize:20},
	color:'blue',
	top: 0,
	text: 'ZIndex',
});

win1.add(label1);
win1.add(label2);

var mybutton=Ti.UI.createButton
(
	{top: 100,title: 'Push Me'}
);

mybutton.addEventListener
(
	'click',
	function(e)
	{
		e.source.title='Pushed!';
		testbutton1.zIndex=15;
	}
);

win1.add(mybutton);

var slider1=Ti.UI.createSlider
(
	{
		top: 200,
		min: 0,
		max: 100,
		value: 50,
	}
);

var sliderListener=function(e)
{
	progress1.value=100-e.value;
	label1.text='Slider value: '+e.value;
	label1.top=e.value;
	mybutton.opacity=e.value/100.0;
	mybutton.left=e.value;
	mybutton.top=e.value;
};

slider1.addEventListener('change',sliderListener);
label1.addEventListener('click',function(e)
	{
		label1.text='Label was clicked';
	}
	);


win1.add(slider1);

var progress1=Ti.UI.createProgressBar({
	value:0,
	min: 0,
	max: 100,
	top: 300,
});

win1.add(progress1);

var testbutton1=Ti.UI.createButton
(
	{top: 500,left:0,title: 'Button 1',zIndex:0}
);
win1.add(testbutton1);

var testbutton2=Ti.UI.createButton
(
	{top: 550,left:50,title: 'Button 2',zIndex:20}
);
win1.add(testbutton2);

var testbutton3=Ti.UI.createButton
(
	{top: 600,left:100,title: 'Button 3',zIndex:25}
);
win1.add(testbutton3);

var testbutton4=Ti.UI.createButton
(
	{top: 650,left:150,title: 'Button 4',zIndex:10}
);
win1.add(testbutton4);

// open window
win1.open();

var timer=setInterval(function()
{
	label2.text='ZIndex of button1='+testbutton1.zIndex+', Zindex of button2='+testbutton2.zIndex;
	testbutton1.top=500+Math.floor(Math.random()*500);
	testbutton1.left=Math.floor(Math.random()*500);
	testbutton2.top=500+Math.floor(Math.random()*500);
	testbutton2.left=Math.floor(Math.random()*500);
	testbutton3.top=500+Math.floor(Math.random()*500);
	testbutton3.left=Math.floor(Math.random()*500);
	testbutton4.top=500+Math.floor(Math.random()*500);
	testbutton4.left=Math.floor(Math.random()*500);
},5000
);