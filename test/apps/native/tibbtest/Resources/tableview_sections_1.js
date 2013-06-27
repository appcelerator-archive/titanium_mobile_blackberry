var win = Titanium.UI.createWindow({
	backgroundColor: '#ccc'
});


var table = Ti.UI.createTableView({
	width: Ti.UI.FILL,
	height: Ti.UI.FILL,
	data: [
           {title: 'row 1', header: 'section 1', subHeader: 'sub header of section 1'},
           {title: 'row 2'},
           {title: 'row 3'},
           {title: 'row 4'},
           {title: 'row 5'},
           {title: 'row 1', header: 'section 2'},
           {title: 'row 2'},
           {title: 'row 3'},
           {title: 'row 4'},
           {title: 'row 5'},
           {title: 'row 1', header: 'section 3'},
           {title: 'row 2'},
           {title: 'row 3'},
           {title: 'row 4'},
           {title: 'row 5'},
           {title: 'row 1', header: 'section 4', subHeader: 'sub header of section 4'},
           {title: 'row 2'},
           {title: 'row 3'},
           {title: 'row 4'},
           {title: 'row 5'},
           {title: 'row 1', header: 'section 5'},
           {title: 'row 2'},
           {title: 'row 3'},
           {title: 'row 4'},
           {title: 'row 5'}
	       ]
});

win.add(table);



win.open();
