var win = Ti.UI.createWindow();

var btn = Ti.UI.createButton({
	title: 'Install todo.sqlite'
});

// item text
// done int

btn.addEventListener('click', function(){

	var db = Ti.Database.open("todo.sqlite" /*, "otherName" */);

    var sSQL = "select * from todo";
    var rows = db.execute(sSQL);
    
	Ti.API.info('Row count: ' + rows.rowCount);

    while(rows.isValidRow())
    {
        Ti.API.info(rows.fieldByName('item'));
        rows.next();
    }

    alert('completed!');
    rows.close();
    db.close();
});

win.add(btn);

win.open();