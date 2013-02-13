
var db = Ti.Database.open('mydb1Installed');

db.execute('CREATE TABLE IF NOT EXISTS people (name TEXT, phone_number TEXT, city TEXT)');
db.execute('DELETE FROM people');

var thisName = 'Arthur';
var thisPhoneNo = '1-617-000-0000';
var thisCity = 'Mountain View';
var rows = db.execute('INSERT INTO people (name, phone_number, city) VALUES (?, ?, ?)', thisName, thisPhoneNo, thisCity);

var personArray = ['Paul',300, 'London'];
db.execute('INSERT INTO people (name, phone_number, city) VALUES (?, ?, ?)', personArray);

rows = db.execute('SELECT rowid,name,phone_number,city FROM people');

Ti.API.info('Row count: ' + rows.rowCount);

var fieldCount;
fieldCount = rows.fieldCount;

Ti.API.info('Field count: ' + fieldCount);

while (rows.isValidRow()){
    Ti.API.info('Person ---> ROWID: ' + rows.fieldByName('rowid') + ', name:' + rows.field(1) + ', phone_number: ' + rows.fieldByName('phone_number') + ', city: ' + rows.field(3));
  rows.next();
}

rows.close();

