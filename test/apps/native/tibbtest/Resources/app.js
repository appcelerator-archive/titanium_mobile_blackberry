

// Tab Group sample


// this sets the background color of the master UIView (when there are no windows/tab groups on it)
Titanium.UI.setBackgroundColor('#000');

// create tab group
var tabGroup = Titanium.UI.createTabGroup();


//
// create base UI tab and root window
//
var win1 = Titanium.UI.createWindow({  
    title:'Tab 1',
    backgroundColor:'#fff'
});
var tab1 = Titanium.UI.createTab({  
    icon:'KS_nav_views.png',
    title:'Tab 1',
    window:win1
});

var scrollview = Titanium.UI.createScrollView({

	layout: 'horizontal',
	contentWidth: '600',
	//contentWidth: Ti.UI.SIZE

});

var label1 = Titanium.UI.createLabel({

	color:'#999',
	text:'I\'m not sure about the backdraws of using the old debugger but did not make a noticable difference for me yet...',
	font:{fontSize:20,fontFamily:'Helvetica Neue'},
	textAlign:'center',
	wordWrap: false,
	width: Ti.UI.SIZE

});

scrollview.add(label1);
win1.add(scrollview);

var x = 0;
var end = 500;
var intervalHandle = null;

var animate = function(){
	
	if(x + 10 < end){
		//scrollview.scrollTo(x,0);
		scrollview.setContentOffset({x:x,y:0}, {animated:true});
		x+=10;
	}else{

		//reset 0
		x=0;
		clearInterval(intervalHandle);
	
		//fade out
		label1.animate({opacity:0, duration:500}, function(){
			//scroller.scrollTo(x,0);
			scrollview.setContentOffset({x:0,y:0}, {animated:false});					
			label1.animate({opacity:1, duration:200}, function(){
				intervalHandle = setInterval(animate,100);
			});
		});
		
	}

};

//scrollerPlaceHolderView.addEventListener('postlayout', function(){
	intervalHandle = setInterval(animate,100);
//});


//win1.addEventListener('postlayout', function(){
//	scrollview.setContentOffset({x:50,y:0}, {animated:false});
//});

	label1.addEventListener('click', function(){
	meh();
});
//
// create controls tab and root window
//
var win2 = Titanium.UI.createWindow({  
    title:'Tab 2',
    backgroundColor:'#fff'
});
var tab2 = Titanium.UI.createTab({  
    icon:'KS_nav_ui.png',
    title:'Tab 2',
    window:win2
});

var label2 = Titanium.UI.createLabel({
	color:'#999',
	text:'I am Window 2',
	font:{fontSize:20,fontFamily:'Helvetica Neue'},
	textAlign:'center',
	width:'auto'
});

win2.add(label2);



//
//  add tabs
//
tabGroup.addTab(tab1);  
tabGroup.addTab(tab2);  


// open tab group
tabGroup.open();
