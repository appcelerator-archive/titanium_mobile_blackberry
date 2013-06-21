var win = Titanium.UI.createWindow({
	backgroundColor: '#ccc'
});

var d = [];
for(var i = 0; i < 10; i++) {
	var section = Ti.UI.createTableViewSection({
		title: 'Hello section number ' + i,
		subTitle: 'This is a subtitle for section #' + i
	});
	
	for(var a = 0; a < 10; a++) {
		section.add(Ti.UI.createTableViewRow({
			title: 'Section #' + i + ' Row #' + a
		}));
	}
	d.push(section);
}

var table = Ti.UI.createTableView({
	width: Ti.UI.FILL,
	height: Ti.UI.FILL,
	data: d
});

win.add(table);



win.open();
